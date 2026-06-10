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
#if !defined(_PCMCIA_SA1100_H)
# define _PCMCIA_SA1100_H

/* SA-1100 PCMCIA Memory and I/O timing
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * The SA-1110 Developer's Manual, section 10.2.5, says the following:
 *
 *  "To calculate the recommended BS_xx value for each address space:
 *   divide the command width time (the greater of twIOWR and twIORD,
 *   or the greater of twWE and twOE) by processor cycle time; divide
 *   by 2; divide again by 3 (number of BCLK's per command assertion);
 *   round up to the next whole number; and subtract 1."
 */

/* MECR: Expansion Memory Configuration Register
 * (SA-1100 Developers Manual, p.10-13; SA-1110 Developers Manual, p.10-24)
 *
 * MECR layout is:
 *
 *   FAST1 BSM1<4:0> BSA1<4:0> BSIO1<4:0> FAST0 BSM0<4:0> BSA0<4:0> BSIO0<4:0>
 *
 * (This layout is actually true only for the SA-1110; the FASTn bits are
 * reserved on the SA-1100.)
 */

#define MECR_SOCKET_0_SHIFT (0)
#define MECR_SOCKET_1_SHIFT (16)

#define MECR_BS_MASK        (0x1f)
#define MECR_FAST_MODE_MASK (0x01)

#define MECR_BSIO_SHIFT (0)
#define MECR_BSA_SHIFT  (5)
#define MECR_BSM_SHIFT  (10)
#define MECR_FAST_SHIFT (15)

#define MECR_SET(mecr, sock, shift, mask, bs) \
((mecr)=((mecr)&~(((mask)<<(shift))<<\
                  ((sock)==0?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT)))|\
        (((bs)<<(shift))<<((sock)==0?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT)))

#define MECR_GET(mecr, sock, shift, mask) \
((((mecr)>>(((sock)==0)?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT))>>\
 (shift))&(mask))

#define MECR_BSIO_SET(mecr, sock, bs) \
MECR_SET((mecr), (sock), MECR_BSIO_SHIFT, MECR_BS_MASK, (bs))

#define MECR_BSIO_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_BSIO_SHIFT, MECR_BS_MASK)

#define MECR_BSA_SET(mecr, sock, bs) \
MECR_SET((mecr), (sock), MECR_BSA_SHIFT, MECR_BS_MASK, (bs))

#define MECR_BSA_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_BSA_SHIFT, MECR_BS_MASK)

#define MECR_BSM_SET(mecr, sock, bs) \
MECR_SET((mecr), (sock), MECR_BSM_SHIFT, MECR_BS_MASK, (bs))

#define MECR_BSM_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_BSM_SHIFT, MECR_BS_MASK)

#define MECR_FAST_SET(mecr, sock, fast) \
MECR_SET((mecr), (sock), MECR_FAST_SHIFT, MECR_FAST_MODE_MASK, (fast))

#define MECR_FAST_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_FAST_SHIFT, MECR_FAST_MODE_MASK)


/* This function implements the BS value calculation for setting the MECR
 * using integer arithmetic:
 */
static inline unsigned int sa1100_pcmcia_mecr_bs(unsigned int pcmcia_cycle_ns,
						 unsigned int cpu_clock_khz){
  unsigned int t = ((pcmcia_cycle_ns * cpu_clock_khz) / 6) - 1000000;
  return (t / 1000000) + (((t % 1000000) == 0) ? 0 : 1);
}

/* This function returns the (approximate) command assertion period, in
 * nanoseconds, for a given CPU clock frequency and MECR BS value:
 */
static inline unsigned int sa1100_pcmcia_cmd_time(unsigned int cpu_clock_khz,
						  unsigned int pcmcia_mecr_bs){
  return (((10000000 * 2) / cpu_clock_khz) * (3 * (pcmcia_mecr_bs + 1))) / 10;
}


int sa11xx_drv_pcmcia_add_one(struct soc_pcmcia_socket *skt);
void sa11xx_drv_pcmcia_ops(struct pcmcia_low_level *ops);
extern int sa11xx_drv_pcmcia_probe(struct device *dev, struct pcmcia_low_level *ops, int first, int nr);

#endif  /* !defined(_PCMCIA_SA1100_H) */
