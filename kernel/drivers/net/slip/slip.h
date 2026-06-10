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
#ifndef _BEEP_SLIP_H
#define _BEEP_SLIP_H


#if defined(CONFIG_INET) && defined(CONFIG_SLIP_COMPRESSED)
# define SL_INCLUDE_CSLIP
#endif

#ifdef SL_INCLUDE_CSLIP
# define SL_MODE_DEFAULT SL_MODE_ADAPTIVE
#else
# define SL_MODE_DEFAULT SL_MODE_SLIP
#endif

/* SLIP configuration. */
#define SL_NRUNIT	256		/* MAX number of SLIP channels;
					   This can be overridden with
					   insmod -oslip_maxdev=nnn	*/
#define SL_MTU		296		/* 296; I am used to 600- FvK	*/

/* SLIP protocol characters. */
#define END             0300		/* indicates end of frame	*/
#define ESC             0333		/* indicates byte stuffing	*/
#define ESC_END         0334		/* ESC ESC_END means END 'data'	*/
#define ESC_ESC         0335		/* ESC ESC_ESC means ESC 'data'	*/


struct slip {
  int			magic;

  /* Various fields. */
  struct tty_struct	*tty;		/* ptr to TTY structure		*/
  struct net_device	*dev;		/* easy for intr handling	*/
  spinlock_t		lock;

#ifdef SL_INCLUDE_CSLIP
  struct slcompress	*slcomp;	/* for header compression 	*/
  unsigned char		*cbuff;		/* compression buffer		*/
#endif

  /* These are pointers to the malloc()ed frame buffers. */
  unsigned char		*rbuff;		/* receiver buffer		*/
  int                   rcount;         /* received chars counter       */
  unsigned char		*xbuff;		/* transmitter buffer		*/
  unsigned char         *xhead;         /* pointer to next byte to XMIT */
  int                   xleft;          /* bytes left in XMIT queue     */
  int			mtu;		/* Our mtu (to spot changes!)   */
  int                   buffsize;       /* Max buffers sizes            */

#ifdef CONFIG_SLIP_MODE_SLIP6
  int			xdata, xbits;	/* 6 bit slip controls 		*/
#endif

  unsigned long		flags;		/* Flag values/ mode etc	*/
#define SLF_INUSE	0		/* Channel in use               */
#define SLF_ESCAPE	1               /* ESC received                 */
#define SLF_ERROR	2               /* Parity, etc. error           */
#define SLF_KEEPTEST	3		/* Keepalive test flag		*/
#define SLF_OUTWAIT	4		/* is outpacket was flag	*/

  unsigned char		mode;		/* SLIP mode			*/
  unsigned char		leased;
  pid_t			pid;
#define SL_MODE_SLIP	0
#define SL_MODE_CSLIP	1
#define SL_MODE_SLIP6	2		/* Matt Dillon's printable slip */
#define SL_MODE_CSLIP6	(SL_MODE_SLIP6|SL_MODE_CSLIP)
#define SL_MODE_AX25	4
#define SL_MODE_ADAPTIVE 8
#ifdef CONFIG_SLIP_SMART
  unsigned char		outfill;	/* # of sec between outfill packet */
  unsigned char		keepalive;	/* keepalive seconds		*/
  struct timer_list	outfill_timer;
  struct timer_list	keepalive_timer;
#endif
};

#define SLIP_MAGIC 0x5302

#endif	/* _BEEP_SLIP.H */
