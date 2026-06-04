/**
 * @file nspire.c
 * @author Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * Functions for Nspire platform
 */

#include "../include/nspireio/platform.h"
#include "../include/nspireio/nspireio.h"
#include "../common/util.h"
#include <os.h>
#include <libndls.h>

#ifndef getBW
#define getBW(c) (((((c) >> 11) & 0x1F) * 299 + (((c) >> 5) & 0x3F) * 587 + ((c) & 0x1F) * 114) / 1000)
#endif

#define KEY_CTRL       KEY_NSPIRE_CTRL
#define KEY_SHIFT      KEY_NSPIRE_SHIFT
#define KEY_ESC        KEY_NSPIRE_ESC
#define KEY_A          KEY_NSPIRE_A
#define KEY_B          KEY_NSPIRE_B
#define KEY_C          KEY_NSPIRE_C
#define KEY_D          KEY_NSPIRE_D
#define KEY_E          KEY_NSPIRE_E
#define KEY_F          KEY_NSPIRE_F
#define KEY_G          KEY_NSPIRE_G
#define KEY_H          KEY_NSPIRE_H
#define KEY_I          KEY_NSPIRE_I
#define KEY_J          KEY_NSPIRE_J
#define KEY_K          KEY_NSPIRE_K
#define KEY_L          KEY_NSPIRE_L
#define KEY_M          KEY_NSPIRE_M
#define KEY_N          KEY_NSPIRE_N
#define KEY_O          KEY_NSPIRE_O
#define KEY_P          KEY_NSPIRE_P
#define KEY_Q          KEY_NSPIRE_Q
#define KEY_R          KEY_NSPIRE_R
#define KEY_S          KEY_NSPIRE_S
#define KEY_T          KEY_NSPIRE_T
#define KEY_U          KEY_NSPIRE_U
#define KEY_V          KEY_NSPIRE_V
#define KEY_W          KEY_NSPIRE_W
#define KEY_X          KEY_NSPIRE_X
#define KEY_Y          KEY_NSPIRE_Y
#define KEY_Z          KEY_NSPIRE_Z
#define KEY_0          KEY_NSPIRE_0
#define KEY_1          KEY_NSPIRE_1
#define KEY_2          KEY_NSPIRE_2
#define KEY_3          KEY_NSPIRE_3
#define KEY_4          KEY_NSPIRE_4
#define KEY_5          KEY_NSPIRE_5
#define KEY_6          KEY_NSPIRE_6
#define KEY_7          KEY_NSPIRE_7
#define KEY_8          KEY_NSPIRE_8
#define KEY_9          KEY_NSPIRE_9
#define KEY_ENTER      KEY_NSPIRE_ENTER
#define KEY_RET        KEY_NSPIRE_ENTER
#define KEY_DEL        KEY_NSPIRE_DEL
#define KEY_TAB        KEY_NSPIRE_TAB
#define KEY_UP         KEY_NSPIRE_UP
#define KEY_DOWN       KEY_NSPIRE_DOWN
#define KEY_COMMA      KEY_NSPIRE_COMMA
#define KEY_PERIOD     KEY_NSPIRE_PERIOD
#define KEY_COLON      KEY_NSPIRE_COLON
#define KEY_SPACE      KEY_NSPIRE_SPACE
#define KEY_DIVIDE     KEY_NSPIRE_DIVIDE
#define KEY_MULTIPLY   KEY_NSPIRE_MULTIPLY
#define KEY_MINUS      KEY_NSPIRE_MINUS
#define KEY_NEGATIVE   KEY_NSPIRE_NEGATIVE
#define KEY_PLUS       KEY_NSPIRE_PLUS
#define KEY_EQU        KEY_NSPIRE_EQU
#define KEY_LTHAN      KEY_NSPIRE_LTHAN
#define KEY_GTHAN      KEY_NSPIRE_GTHAN
#define KEY_QUOTE      KEY_NSPIRE_QUOTE
#define KEY_APOSTROPHE KEY_NSPIRE_APOSTROPHE
#define KEY_QUES       KEY_NSPIRE_QUES
#define KEY_QUESEXCL   KEY_NSPIRE_QUESEXCL
#define KEY_BAR        KEY_NSPIRE_BAR
#define KEY_EXP        KEY_NSPIRE_EXP
#define KEY_EE         KEY_NSPIRE_EE
#define KEY_LP         KEY_NSPIRE_LP
#define KEY_RP         KEY_NSPIRE_RP
#ifndef SCR_320x240_4
#define SCR_320x240_4 0
#endif

#ifndef SCR_320x240_565
#define SCR_320x240_565 3
#endif

static void* scrbuf;
static unsigned scrsize;
static bool is_color;

bool nio_scrbuf_init()
{
	if(scrbuf == NULL)
	{
		is_color = (lcd_type() != SCR_320x240_4);
		scrsize = (is_color ? SCREEN_WIDTH*SCREEN_HEIGHT*2 : SCREEN_WIDTH*SCREEN_HEIGHT/2);
		scrbuf = malloc(scrsize);
		if (!scrbuf) return false;
		if (!lcd_init(is_color ? SCR_320x240_565 : SCR_320x240_4))
		{
			free(scrbuf);
			scrbuf = NULL;
			return false;
		}
	}
	return true;
}

void nio_scrbuf_clear()
{
	memset(scrbuf,0xFF,scrsize);
}

void nio_scrbuf_free()
{
	free(scrbuf);
	scrbuf = NULL;
	lcd_init(SCR_TYPE_INVALID);
}

unsigned short getPaletteColor(unsigned int color)
{
	unsigned short palette[16] = {0x0000, 0xa800, 0x0540, 0xaaa0, 0x0015, 0xa815, 0x0555, 0xad55,
					0x5aab, 0xfaab, 0x5feb, 0xffeb, 0x5abf, 0xfabf, 0x5fff, 0xffff};
	int rbtable[6] = {0,6,12,18,24,31};
	int gtable[6] = {0,12,25,37,50,63};
	unsigned int c = color;
	unsigned int d;
	if(c < 16)
	{
			return palette[c];
	}
	else if(c < 232)
	{
			d = c-16;
			return (rbtable[d/36]<<11)+(gtable[(d/6)%6]<<5)+rbtable[d%6];
	}
	else if(c < 256)
	{
			d = c-232;
			return ((d+1)<<11)+((d*2+2)<<5)+(d+1);
	}
	return 0;
}

// by totorigolo
void nio_vram_pixel_set(unsigned int x, unsigned int y, unsigned int c)
{
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	
	c = getPaletteColor(c);

	if(is_color)
	{
		uint16_t *ptr = (uint16_t*)scrbuf + (x + SCREEN_WIDTH * y);
		*ptr = c;
	}
	else
	{
		c = getBW(c);
		uint8_t* p = (uint8_t*)scrbuf + ((x >> 1) + (y << 7) + (y << 5));
		*p = (x & 1) ? ((*p & 0xF0) | c) : ((*p & 0x0F) | (c << 4));
	}
}

void nio_vram_fill(const unsigned x, const unsigned y, unsigned w, const unsigned h, unsigned color)
{
	// Hack: Round up to the screen width to cover the pixels between the last char and the edge.
	if(x + w == (unsigned)(SCREEN_WIDTH/NIO_CHAR_WIDTH) * NIO_CHAR_WIDTH)
		w = SCREEN_WIDTH - x;

	color = getPaletteColor(color);
	if(is_color)
	{
		uint16_t *p = (uint16_t*)scrbuf + x + SCREEN_WIDTH*y;
		for (unsigned int i = 0; i < h; i++)
		{
			for (unsigned int j = 0; j < w; j++)
				*p++ = color;
			p += (SCREEN_WIDTH - w);
		}
	}
	else
	{
		color = getBW(color);
		uint8_t *p;
		if (x & 1)
		{
			p = (uint8_t*)scrbuf + (x/2) + (SCREEN_WIDTH/2)*y;
			for (unsigned int i = 0; i < h; i++, p += (SCREEN_WIDTH/2))
				*p = (*p & 0xF0) | color;
		}
		if ((x + w) & 1)
		{
			p = (uint8_t*)scrbuf + (x+w)/2 + (SCREEN_WIDTH/2)*y;
			for (unsigned int i = 0; i < h; i++, p += (SCREEN_WIDTH/2))
				*p = (*p & 0x0F) | (color << 4);
		}
		color = color | (color << 4);
		p = (uint8_t*)scrbuf + (x+1)/2 + (SCREEN_WIDTH/2)*y;
		size_t n = (w - (x & 1))/2;
		for (unsigned int i = 0; i < h; i++, p += (SCREEN_WIDTH/2))
			memset(p, color, n);
	}
}

void nio_vram_scroll(const unsigned x, const unsigned y, unsigned w, const unsigned h, const unsigned scroll, const unsigned color) {
	if (!scroll) return;

	// Hack: Round up to the screen width to cover the pixels between the last char and the edge.
	if(x + w == (unsigned)(SCREEN_WIDTH/NIO_CHAR_WIDTH) * NIO_CHAR_WIDTH)
		w = SCREEN_WIDTH - x;

	unsigned int r = h - scroll;
	if (is_color)
	{
		uint16_t *p1 = (uint16_t*)scrbuf+x+SCREEN_WIDTH*y;
		uint16_t *p2 = p1 + SCREEN_WIDTH*scroll;
		size_t n = sizeof(uint16_t)*w;
		for (unsigned int i = 0; i < r; ++i, p1 += SCREEN_WIDTH, p2 += SCREEN_WIDTH)
			memmove(p1, p2, n);
	}
	else
	{
		uint8_t *p1, *p2;
		size_t n = (w - (x & 1))/2;

		if (x & 1)
		{
			p1 = (uint8_t*)scrbuf+x/2+(SCREEN_WIDTH/2)*y;
			p2 = p1 + (SCREEN_WIDTH/2)*scroll;
			for (unsigned int i = 0; i < r; ++i, p1 += SCREEN_WIDTH/2, p2 += SCREEN_WIDTH/2)
				*p1 = ((*p1 & 0xF0) | (*p2 & 0xF));
		}
		if ((x + w) & 1)
		{
			p1 = (uint8_t*)scrbuf+(x+w)/2+(SCREEN_WIDTH/2)*y;
			p2 = p1 + (SCREEN_WIDTH/2)*scroll;
			for (unsigned int i = 0; i < r; ++i, p1 += SCREEN_WIDTH/2, p2 += SCREEN_WIDTH/2)
				*p1 = ((*p1 & 0xF) | (*p2 & 0xF0));
		}
		p1 = (uint8_t*)scrbuf+(x+1)/2+(SCREEN_WIDTH/2)*y;
		p2 = p1 + (SCREEN_WIDTH/2)*scroll;
		for (unsigned int i = 0; i < r; ++i, p1 += SCREEN_WIDTH/2, p2 += SCREEN_WIDTH/2)
			memmove(p1, p2, n);
	}
	nio_vram_fill(x, y + h - scroll, w, scroll, color);
}

void nio_vram_draw(void)
{lcd_blit(scrbuf, is_color ? SCR_320x240_565 : SCR_320x240_4);}

unsigned int nio_cursor_clock(void) {
    return *(volatile unsigned*)0x90090000;
}

#define SHIFTCTRL(x, y, z) (ctrl ? (z) : shift ? (y) : (x))
#define SHIFT(x, y) SHIFTCTRL(x, y, 0)
#define NORMAL(x) SHIFT(x, 0)

char nio_ascii_get(int* adaptive_cursor_state)
{
	bool ctrl = isKeyPressed(KEY_CTRL);
	bool shift = isKeyPressed(KEY_SHIFT);

	*adaptive_cursor_state = SHIFTCTRL(0, 1, 4);
	
	if(isKeyPressed(KEY_ESC)) return NIO_KEY_ESC;
	
	// Characters
	if(isKeyPressed(KEY_A)) return SHIFT('a','A');
	if(isKeyPressed(KEY_B)) return SHIFT('b','B');
	if(isKeyPressed(KEY_C)) return SHIFT('c','C');
	if(isKeyPressed(KEY_D)) return SHIFT('d','D');
	if(isKeyPressed(KEY_E)) return SHIFT('e','E');
	if(isKeyPressed(KEY_F)) return SHIFT('f','F');
	if(isKeyPressed(KEY_G)) return SHIFT('g','G');
	if(isKeyPressed(KEY_H)) return SHIFT('h','H');
	if(isKeyPressed(KEY_I)) return SHIFT('i','I');
	if(isKeyPressed(KEY_J)) return SHIFT('j','J');
	if(isKeyPressed(KEY_K)) return SHIFT('k','K');
	if(isKeyPressed(KEY_L)) return SHIFT('l','L');
	if(isKeyPressed(KEY_M)) return SHIFT('m','M');
	if(isKeyPressed(KEY_N)) return SHIFT('n','N');
	if(isKeyPressed(KEY_O)) return SHIFT('o','O');
	if(isKeyPressed(KEY_P)) return SHIFT('p','P');
	if(isKeyPressed(KEY_Q)) return SHIFT('q','Q');
	if(isKeyPressed(KEY_R)) return SHIFT('r','R');
	if(isKeyPressed(KEY_S)) return SHIFT('s','S');
	if(isKeyPressed(KEY_T)) return SHIFT('t','T');
	if(isKeyPressed(KEY_U)) return SHIFT('u','U');
	if(isKeyPressed(KEY_V)) return SHIFT('v','V');
	if(isKeyPressed(KEY_W)) return SHIFT('w','W');
	if(isKeyPressed(KEY_X)) return SHIFT('x','X');
	if(isKeyPressed(KEY_Y)) return SHIFT('y','Y');
	if(isKeyPressed(KEY_Z)) return SHIFT('z','Z');
	
	// Numbers
	if(isKeyPressed(KEY_0)) return NORMAL('0');
	if(isKeyPressed(KEY_1)) return NORMAL('1');
	if(isKeyPressed(KEY_2)) return NORMAL('2');
	if(isKeyPressed(KEY_3)) return NORMAL('3');
	if(isKeyPressed(KEY_4)) return NORMAL('4');
	if(isKeyPressed(KEY_5)) return NORMAL('5');
	if(isKeyPressed(KEY_6)) return NORMAL('6');
	if(isKeyPressed(KEY_7)) return NORMAL('7');
	if(isKeyPressed(KEY_8)) return NORMAL('8');
	if(isKeyPressed(KEY_9)) return NORMAL('9');
	
	// Symbols
	if(isKeyPressed(KEY_COMMA))		return SHIFT(',',';');
	if(isKeyPressed(KEY_PERIOD)) 	return SHIFT('.',':');
	if(isKeyPressed(KEY_COLON))		return NORMAL(':');
	if(isKeyPressed(KEY_LP))			return SHIFTCTRL('(','[',']');
	if(isKeyPressed(KEY_RP))			return SHIFTCTRL(')','{','}');
	if(isKeyPressed(KEY_SPACE))		return SHIFT(' ','_');
	if(isKeyPressed(KEY_DIVIDE))		return SHIFT('/','\\');
	if(isKeyPressed(KEY_MULTIPLY))	return SHIFT('*','\"');
	if(isKeyPressed(KEY_MINUS))		return SHIFTCTRL('-','<', '_');
	if(isKeyPressed(KEY_NEGATIVE))	return SHIFT('-','_');
	if(isKeyPressed(KEY_PLUS))		return SHIFT('+', '>');
	if(isKeyPressed(KEY_EQU))		return SHIFT('=', '|');
	if(isKeyPressed(KEY_LTHAN))		return NORMAL('<');
	if(isKeyPressed(KEY_GTHAN))		return NORMAL('>');
	if(isKeyPressed(KEY_QUOTE))		return NORMAL('\"');
	if(isKeyPressed(KEY_APOSTROPHE))	return NORMAL('\'');
	if(isKeyPressed(KEY_QUES))		return SHIFT('?','!');
	if(isKeyPressed(KEY_QUESEXCL))	return SHIFT('?','!');
	if(isKeyPressed(KEY_BAR))		return NORMAL('|');
	if(isKeyPressed(KEY_EXP))		return NORMAL('^');
	if(isKeyPressed(KEY_EE))		return SHIFTCTRL('&','%', '@');
	if(isKeyPressed(KEY_ENTER))		return SHIFT('\n','~');
	
	// Special chars
	if(isKeyPressed(KEY_DEL))		return '\b';
	if(isKeyPressed(KEY_RET))		return '\n';
	if(isKeyPressed(KEY_TAB))		return '\t';
	if(isKeyPressed(KEY_UP))			return NIO_KEY_UP;
	if(isKeyPressed(KEY_DOWN))		return NIO_KEY_DOWN;
	
	return 0;
}
