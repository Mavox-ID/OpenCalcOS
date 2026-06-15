/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/select.h>
#include <getopt.h>

#define VERSION "0.9.1"
#define M 32768

const char* sets[10][16] = {
    {"┃","┏"," ","┓","┛","━","┓"," "," ","┗","┃","┛","┗"," ","┏","━"},
    {"│","╭"," ","╮","╯","─","╮"," "," ","╰","│","╯","╰"," ","╭","─"},
    {"│","┌"," ","┐","┘","─","┐"," "," ","└","│","┘","└"," ","┌","─"},
    {"║","╔"," ","╗","╝","═","╗"," "," ","╚","║","╝","╚"," ","╔","═"},
    {"|","+"," ","+","+","-","+"," "," ","+","|","+","+"," ","+","-"},
    {"|","/"," ","\\","/","-","\\"," "," ","\\","|","/","\\"," ","/","-"},
    {".","."," ",".",".",".","."," "," ",".",".",".","."," ",".", "."},
    {".","o"," ","o","o",".","o"," "," ","o",".","o","o"," ","o","."},
    {"-","\\"," ","/","\\","|","/"," "," ","/","-","\\","/"," ","\\","|"},
    {"╿","┍"," ","┑","┚","╼","┒"," "," ","┕","╽","┙","┖"," ","┎","╾"}
};

struct termios orig_termios;
int terminal_configured = 0;

int p = 1;
int f = 75;
int s = 13;
int r = 2000;
int w = 80;
int h = 24;

int rndstart = 0;
int bold = 1;
int nocolor = 0;
int keepct = 0;

int* pipe_x = NULL;
int* pipe_y = NULL;
int* pipe_l = NULL;
int* pipe_v = NULL;
char** pipe_c = NULL;

int custom_types_count = 0;
char custom_sets[10][16][4];

int colors_allowed = 256; 
int selected_colors[256];
int selected_colors_cnt = 0;
int selected_types[256];
int selected_types_cnt = 0;
char color_escapes[256][32];

void cleanup(int sig) {
    (void)sig;
    
    printf("\033[2J\033[H\033[?25h\033[0m");
    fflush(stdout);
    
    if (terminal_configured) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }
    
    if (pipe_x) free(pipe_x);
    if (pipe_y) free(pipe_y);
    if (pipe_l) free(pipe_l);
    if (pipe_v) free(pipe_v);
    if (pipe_c) free(pipe_c);

    exit(0);
}

void resize_handler(int sig) {
    (void)sig;
    struct winsize wsize;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize) == 0) {
        w = wsize.ws_col;
        h = wsize.ws_row;
    }
}

void print_help(const char* progname) {
    printf("Usage: %s [OPTION]...\n", progname);
    printf("Animated pipes terminal screensaver for OpenCalcOS.\n\n");
    printf("  -p [1-]         number of pipes (D=1)\n");
    printf("  -t [0-9]        pipe type (D=0)\n");
    printf("  -t c[16 chars]  custom pipe type\n");
    printf("  -c [0-255]      pipe color INDEX, can be hex with # prefix\n");
    printf("  -f [20-100]     framerate (D=75)\n");
    printf("  -s [5-15]       going straight probability, 1 in (D=13)\n");
    printf("  -r [0-]         reset after (D=2000) characters, 0 if no reset\n");
    printf("  -R              randomize starting position and direction\n");
    printf("  -B              no bold effect\n");
    printf("  -C              no color\n");
    printf("  -K              keep pipe color and type when crossing edges\n");
    printf("  -h              print this help message\n");
    printf("  -v              print version number\n");
}

void generate_color_escapes() {
    for (int i = 0; i < selected_colors_cnt; i++) {
        char color_str[16] = "";
        if (!nocolor) {
            sprintf(color_str, "\033[38;5;%dm", selected_colors[i]);
        }
        sprintf(color_escapes[i], "\033[0m%s%s", bold ? "\033[1m" : "", color_str);
    }
}

int parse_args(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "p:t:c:f:s:r:RBCKhv")) != -1) {
        switch (opt) {
            case 'p':
                p = atoi(optarg);
                if (p <= 0) return -1;
                break;
            case 't':
                if (optarg[0] == 'c') {
                    if (strlen(optarg) < 17 || custom_types_count >= 10) return -1;
                    for (int j = 0; j < 16; j++) {
                        custom_sets[custom_types_count][j][0] = optarg[1 + j];
                        custom_sets[custom_types_count][j][1] = '\0';
                    }
                    selected_types[selected_types_cnt++] = 10 + custom_types_count;
                    custom_types_count++;
                } else {
                    int val = atoi(optarg);
                    if (val < 0 || val > 9) return -1;
                    selected_types[selected_types_cnt++] = val;
                }
                break;
            case 'c':
                if (optarg[0] == '#') {
                    int hex_val = (int)strtol(&optarg[1], NULL, 16);
                    selected_colors[selected_colors_cnt++] = hex_val % colors_allowed;
                } else {
                    selected_colors[selected_colors_cnt++] = atoi(optarg) % colors_allowed;
                }
                break;
            case 'f':
                f = atoi(optarg);
                if (f < 20 || f > 100) return -1;
                break;
            case 's':
                s = atoi(optarg);
                if (s < 5 || s > 15) return -1;
                break;
            case 'r':
                r = atoi(optarg);
                if (r < 0) return -1;
                break;
            case 'R': rndstart = 1; break;
            case 'B': bold = 0; break;
            case 'C': nocolor = 1; break;
            case 'K': keepct = 1; break;
            case 'h': print_help(argv[0]); exit(0);
            case 'v': printf("pipes %s\n", VERSION); exit(0);
            default: return -1;
        }
    }
    return 0;
}

void init_screen() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == 0) {
        struct termios raw = orig_termios;
        raw.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        terminal_configured = 1;
    }

    printf("\033[?1049h\033[?25l\033[2J");
    fflush(stdout);

    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);
    signal(SIGWINCH, resize_handler);
    resize_handler(0);
}

void init_pipes() {
    pipe_x = malloc(p * sizeof(int));
    pipe_y = malloc(p * sizeof(int));
    pipe_l = malloc(p * sizeof(int));
    pipe_v = malloc(p * sizeof(int));
    pipe_c = malloc(p * sizeof(char*));

    int ci = 0;
    int vi = 0;

    for (int i = 0; i < p; i++) {
        pipe_l[i] = rndstart ? rand() % 4 : 0;
        pipe_x[i] = rndstart ? (rand() % w) : (w / 2);
        pipe_y[i] = rndstart ? (rand() % h) : (h / 2);
        
        int type_idx = selected_types[vi];
        pipe_v[i] = type_idx;
        pipe_c[i] = color_escapes[ci];

        ci = (ci + 1) % selected_colors_cnt;
        vi = (vi + 1) % selected_types_cnt;
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (parse_args(argc, argv) != 0) {
        fprintf(stderr, "Invalid arguments. Use -h for help.\n");
        return 1;
    }

    if (selected_types_cnt == 0) {
        selected_types[0] = 0;
        selected_types_cnt = 1;
    }
    if (selected_colors_cnt == 0) {
        int def_cols[] = {1, 2, 3, 4, 5, 6, 7, 0};
        for (int i = 0; i < 8; i++) selected_colors[i] = def_cols[i];
        selected_colors_cnt = 8;
    }

    generate_color_escapes();
    init_screen();
    init_pipes();

    int t_counter = 0;
    struct timeval tv;
    fd_set fds;

    while (1) {
        tv.tv_sec = 0;
        tv.tv_usec = 1000000 / f;

        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        int ready = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
        if (ready > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
            char ch;
            if (read(STDIN_FILENO, &ch, 1) > 0) {
                switch (ch) {
                    case 'P': if (s < 15) s++; break;
                    case 'O': if (s > 3)  s--; break;
                    case 'F': if (f < 100) f++; break;
                    case 'D': if (f > 20)  f--; break;
                    case 'B': bold = !bold; generate_color_escapes(); break;
                    case 'C': nocolor = !nocolor; generate_color_escapes(); break;
                    case 'K': keepct = !keepct; break;
                    default: cleanup(0);
                }
            }
        }

        for (int i = 0; i < p; i++) {
            if (pipe_l[i] % 2) {
                pipe_x[i] += (-pipe_l[i] + 2);
            } else {
                pipe_y[i] += (pipe_l[i] - 1);
            }

            if (!keepct && (pipe_x[i] >= w || pipe_x[i] < 0 || pipe_y[i] >= h || pipe_y[i] < 0)) {
                pipe_c[i] = color_escapes[rand() % selected_colors_cnt];
                pipe_v[i] = selected_types[rand() % selected_types_cnt];
            }

            pipe_x[i] = (pipe_x[i] + w) % w;
            pipe_y[i] = (pipe_y[i] + h) % h;

            int next_dir;
            int n_test = (s * (rand() % M) / M) - 1;
            if (n_test >= 0) {
                next_dir = pipe_l[i];
            } else {
                next_dir = pipe_l[i] + (2 * (rand() % 2) - 1);
            }
            next_dir = (next_dir + 4) % 4;

            int glyph_idx = pipe_l[i] * 4 + next_dir;
            const char* glyph = "";
            
            if (pipe_v[i] >= 10) {
                glyph = custom_sets[pipe_v[i] - 10][glyph_idx];
            } else {
                glyph = sets[pipe_v[i]][glyph_idx];
            }

            printf("\033[%d;%dH%s%s", pipe_y[i] + 1, pipe_x[i] + 1, pipe_c[i], glyph);
            
            pipe_l[i] = next_dir;
        }
        fflush(stdout);

        if (r > 0 && (t_counter * p) >= r) {
            printf("\033[2J\033[?25l");
            t_counter = 0;
        } else {
            t_counter++;
        }
    }

    cleanup(0);
    return 0;
}
