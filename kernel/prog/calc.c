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
#include <math.h>
#include <ctype.h>

int has_error = 0;
const char *error_msg = "";

void skip_whitespace(const char **str) {
    while (**str == ' ' || **str == '\t') {
        (*str)++;
    }
}

double parse_expression(const char **str);
double parse_term(const char **str);
double parse_power(const char **str);
double parse_primary(const char **str);

double parse_primary(const char **str) {
    skip_whitespace(str);

    if (**str == '(') {
        (*str)++;
        double result = parse_expression(str);
        skip_whitespace(str);
        if (**str == ')') {
            (*str)++;
        } else {
            has_error = 1;
            error_msg = "Missing closing parenthesis ')'";
        }
        return result;
    }

    if (strncmp(*str, "sqrt", 4) == 0) {
        *str += 4;
        return sqrt(parse_primary(str));
    }
    if (strncmp(*str, "sin", 3) == 0) {
        *str += 3;
        return sin(parse_primary(str));
    }
    if (strncmp(*str, "cos", 3) == 0) {
        *str += 3;
        return cos(parse_primary(str));
    }
    if (strncmp(*str, "tan", 3) == 0) {
        *str += 3;
        return tan(parse_primary(str));
    }
    if (strncmp(*str, "abs", 3) == 0) {
        *str += 3;
        return fabs(parse_primary(str));
    }
    if (strncmp(*str, "ln", 2) == 0) {
        *str += 2;
        return log(parse_primary(str));
    }

    char *endptr;
    double val = strtod(*str, &endptr);
    if (*str == endptr) {
        has_error = 1;
        error_msg = "Invalid character or empty expression";
        return 0;
    }
    *str = endptr;
    return val;
}

double parse_power(const char **str) {
    skip_whitespace(str);
    
    int sign = 1;
    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }

    double result = parse_primary(str);
    skip_whitespace(str);

    if (**str == '^') {
        (*str)++;
        result = pow(result, parse_power(str));
    }
    
    return sign * result;
}

double parse_term(const char **str) {
    double result = parse_power(str);
    
    while (1) {
        skip_whitespace(str);
        char op = **str;
        if (op == '*' || op == '/') {
            (*str)++;
            double next_factor = parse_power(str);
            if (op == '*') {
                result *= next_factor;
            } else {
                if (next_factor == 0.0) {
                    has_error = 1;
                    error_msg = "Division by zero!";
                    return 0;
                }
                result /= next_factor;
            }
        } else {
            break;
        }
    }
    return result;
}

double parse_expression(const char **str) {
    double result = parse_term(str);
    
    while (1) {
        skip_whitespace(str);
        char op = **str;
        if (op == '+' || op == '-') {
            (*str)++;
            double next_term = parse_term(str);
            if (op == '+') {
                result += next_term;
            } else {
                result -= next_term;
            }
        } else {
            break;
        }
    }
    return result;
}

int main(void) {
    char line[256];
    printf("OpenCalcOS Math Shell\n");
    printf("Supports: +, -, *, /, ^, sqrt(), sin(), cos(), ln(), abs()\n");
    printf("To exit, enter 'exit' or 'quit'\n\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        line[strcspn(line, "\n")] = 0;

        char *cmd = line;
        while (*cmd == ' ' || *cmd == '\t') cmd++;
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
            break;
        }
        if (*cmd == '\0') {
            continue;
        }

        has_error = 0;
        error_msg = "";

        const char *ptr = line;
        double result = parse_expression(&ptr);

        skip_whitespace(&ptr);
        if (*ptr != '\0' && !has_error) {
            has_error = 1;
            error_msg = "Syntax error (extra characters at the end of the expression)";
        }

        if (has_error) {
            printf("Error: %s\n", error_msg);
        } else {
            printf("A> %g\n", result);
        }
    }

    return 0;
}
