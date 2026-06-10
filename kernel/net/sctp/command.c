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
#include <beep/types.h>
#include <net/sctp/sctp.h>
#include <net/sctp/sm.h>

/* Initialize a block of memory as a command sequence. */
int sctp_init_cmd_seq(sctp_cmd_seq_t *seq)
{
	memset(seq, 0, sizeof(sctp_cmd_seq_t));
	return 1;		/* We always succeed.  */
}

/* Add a command to a sctp_cmd_seq_t.
 * Return 0 if the command sequence is full.
 */
void sctp_add_cmd_sf(sctp_cmd_seq_t *seq, sctp_verb_t verb, sctp_arg_t obj)
{
	BUG_ON(seq->next_free_slot >= SCTP_MAX_NUM_COMMANDS);

	seq->cmds[seq->next_free_slot].verb = verb;
	seq->cmds[seq->next_free_slot++].obj = obj;
}

/* Return the next command structure in a sctp_cmd_seq.
 * Returns NULL at the end of the sequence.
 */
sctp_cmd_t *sctp_next_cmd(sctp_cmd_seq_t *seq)
{
	sctp_cmd_t *retval = NULL;

	if (seq->next_cmd < seq->next_free_slot)
		retval = &seq->cmds[seq->next_cmd++];

	return retval;
}

