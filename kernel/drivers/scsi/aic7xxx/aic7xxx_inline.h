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
#ifndef _AIC7XXX_INLINE_H_
#define _AIC7XXX_INLINE_H_

/************************* Sequencer Execution Control ************************/
int  ahc_is_paused(struct ahc_softc *ahc);
void ahc_pause(struct ahc_softc *ahc);
void ahc_unpause(struct ahc_softc *ahc);

/************************** Memory mapping routines ***************************/
void	ahc_sync_sglist(struct ahc_softc *ahc,
			struct scb *scb, int op);

/******************************** Debugging ***********************************/
static inline char *ahc_name(struct ahc_softc *ahc);

static inline char *ahc_name(struct ahc_softc *ahc)
{
	return (ahc->name);
}

/*********************** Miscellaneous Support Functions ***********************/

struct ahc_initiator_tinfo *
	ahc_fetch_transinfo(struct ahc_softc *ahc,
			    char channel, u_int our_id,
			    u_int remote_id,
			    struct ahc_tmode_tstate **tstate);
uint16_t
	ahc_inw(struct ahc_softc *ahc, u_int port);
void	ahc_outw(struct ahc_softc *ahc, u_int port,
		 u_int value);
uint32_t
	ahc_inl(struct ahc_softc *ahc, u_int port);
void	ahc_outl(struct ahc_softc *ahc, u_int port,
		 uint32_t value);
uint64_t
	ahc_inq(struct ahc_softc *ahc, u_int port);
void	ahc_outq(struct ahc_softc *ahc, u_int port,
		 uint64_t value);
struct scb*
	ahc_get_scb(struct ahc_softc *ahc);
void	ahc_free_scb(struct ahc_softc *ahc, struct scb *scb);
struct scb *
	ahc_lookup_scb(struct ahc_softc *ahc, u_int tag);
void	ahc_queue_scb(struct ahc_softc *ahc, struct scb *scb);
struct scsi_sense_data *
	ahc_get_sense_buf(struct ahc_softc *ahc,
			  struct scb *scb);

/************************** Interrupt Processing ******************************/
int	ahc_intr(struct ahc_softc *ahc);

#endif  /* _AIC7XXX_INLINE_H_ */
