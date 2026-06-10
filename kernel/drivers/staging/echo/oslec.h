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
#ifndef __OSLEC_H
#define __OSLEC_H

/* Mask bits for the adaption mode */
#define ECHO_CAN_USE_ADAPTION	0x01
#define ECHO_CAN_USE_NLP	0x02
#define ECHO_CAN_USE_CNG	0x04
#define ECHO_CAN_USE_CLIP	0x08
#define ECHO_CAN_USE_TX_HPF	0x10
#define ECHO_CAN_USE_RX_HPF	0x20
#define ECHO_CAN_DISABLE	0x40

/**
 * oslec_state: G.168 echo canceller descriptor.
 *
 * This defines the working state for a line echo canceller.
 */
struct oslec_state;

/**
 * oslec_create - Create a voice echo canceller context.
 * @len: The length of the canceller, in samples.
 * @return: The new canceller context, or NULL if the canceller could not be
 * created.
 */
struct oslec_state *oslec_create(int len, int adaption_mode);

/**
 * oslec_free - Free a voice echo canceller context.
 * @ec: The echo canceller context.
 */
void oslec_free(struct oslec_state *ec);

/**
 * oslec_flush - Flush (reinitialise) a voice echo canceller context.
 * @ec: The echo canceller context.
 */
void oslec_flush(struct oslec_state *ec);

/**
 * oslec_adaption_mode - set the adaption mode of a voice echo canceller context.
 * @ec The echo canceller context.
 * @adaption_mode: The mode.
 */
void oslec_adaption_mode(struct oslec_state *ec, int adaption_mode);

void oslec_snapshot(struct oslec_state *ec);

/**
 * oslec_update: Process a sample through a voice echo canceller.
 * @ec: The echo canceller context.
 * @tx: The transmitted audio sample.
 * @rx: The received audio sample.
 *
 * The return value is the clean (echo cancelled) received sample.
 */
int16_t oslec_update(struct oslec_state *ec, int16_t tx, int16_t rx);

/**
 * oslec_hpf_tx: Process to high pass filter the tx signal.
 * @ec: The echo canceller context.
 * @tx: The transmitted auio sample.
 *
 * The return value is the HP filtered transmit sample, send this to your D/A.
 */
int16_t oslec_hpf_tx(struct oslec_state *ec, int16_t tx);

#endif /* __OSLEC_H */
