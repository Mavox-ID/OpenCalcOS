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
#ifndef _UAPI_HDLCDRV_H
#define _UAPI_HDLCDRV_H

/* -------------------------------------------------------------------- */
/*
 * structs for the IOCTL commands
 */

struct hdlcdrv_params {
	int iobase;
	int irq;
	int dma;
	int dma2;
	int seriobase;
	int pariobase;
	int midiiobase;
};	

struct hdlcdrv_channel_params {
	int tx_delay;  /* the transmitter keyup delay in 10ms units */
	int tx_tail;   /* the transmitter keyoff delay in 10ms units */
	int slottime;  /* the slottime in 10ms; usually 10 = 100ms */
	int ppersist;  /* the p-persistence 0..255 */
	int fulldup;   /* some driver do not support full duplex, setting */
	               /* this just makes them send even if DCD is on */
};	

struct hdlcdrv_old_channel_state {
  	int ptt;
  	int dcd;
  	int ptt_keyed;
};

struct hdlcdrv_channel_state {
 	int ptt;
 	int dcd;
 	int ptt_keyed;
 	unsigned long tx_packets;
 	unsigned long tx_errors;
 	unsigned long rx_packets;
 	unsigned long rx_errors;
};

struct hdlcdrv_ioctl {
	int cmd;
	union {
		struct hdlcdrv_params mp;
		struct hdlcdrv_channel_params cp;
		struct hdlcdrv_channel_state cs;
		struct hdlcdrv_old_channel_state ocs;
		unsigned int calibrate;
		unsigned char bits;
		char modename[128];
		char drivername[32];
	} data;
};

/* -------------------------------------------------------------------- */

/*
 * ioctl values
 */
#define HDLCDRVCTL_GETMODEMPAR       0
#define HDLCDRVCTL_SETMODEMPAR       1
#define HDLCDRVCTL_MODEMPARMASK      2  /* not handled by hdlcdrv */
#define HDLCDRVCTL_GETCHANNELPAR    10
#define HDLCDRVCTL_SETCHANNELPAR    11
#define HDLCDRVCTL_OLDGETSTAT       20
#define HDLCDRVCTL_CALIBRATE        21
#define HDLCDRVCTL_GETSTAT          22

/*
 * these are mainly for debugging purposes
 */
#define HDLCDRVCTL_GETSAMPLES       30
#define HDLCDRVCTL_GETBITS          31

/*
 * not handled by hdlcdrv, but by its depending drivers
 */
#define HDLCDRVCTL_GETMODE          40
#define HDLCDRVCTL_SETMODE          41
#define HDLCDRVCTL_MODELIST         42
#define HDLCDRVCTL_DRIVERNAME       43

/*
 * mask of needed modem parameters, returned by HDLCDRVCTL_MODEMPARMASK
 */
#define HDLCDRV_PARMASK_IOBASE      (1<<0)
#define HDLCDRV_PARMASK_IRQ         (1<<1)
#define HDLCDRV_PARMASK_DMA         (1<<2)
#define HDLCDRV_PARMASK_DMA2        (1<<3)
#define HDLCDRV_PARMASK_SERIOBASE   (1<<4)
#define HDLCDRV_PARMASK_PARIOBASE   (1<<5)
#define HDLCDRV_PARMASK_MIDIIOBASE  (1<<6)

/* -------------------------------------------------------------------- */


/* -------------------------------------------------------------------- */

#endif /* _UAPI_HDLCDRV_H */

/* -------------------------------------------------------------------- */
