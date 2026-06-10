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
/* Used for uploading DSP binary code */
struct dsp56k_upload {
	int len;
	char __user *bin;
};

/* For the DSP host flags */
struct dsp56k_host_flags {
	int dir;     /* Bit field. 1 = write output bit, 0 = do nothing.
		      * 0x0000 means reading only, 0x0011 means
		      * writing the bits stored in `out' on HF0 and HF1.
		      * Note that HF2 and HF3 can only be read.
		      */
	int out;     /* Bit field like above. */
	int status;  /* Host register's current state is returned */
};

/* ioctl command codes */
#define DSP56K_UPLOAD	        1    /* Upload DSP binary program       */
#define DSP56K_SET_TX_WSIZE	2    /* Host transmit word size (1-4)   */
#define DSP56K_SET_RX_WSIZE	3    /* Host receive word size (1-4)    */
#define DSP56K_HOST_FLAGS	4    /* Host flag registers             */
#define DSP56K_HOST_CMD         5    /* Trig Host Command (0-31)        */
