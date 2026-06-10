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
#include <string.h>

#include "bpf-helper.h"

int bpf_resolve_jumps(struct bpf_labels *labels,
		      struct sock_filter *filter, size_t count)
{
	struct sock_filter *begin = filter;
	__u8 insn = count - 1;

	if (count < 1)
		return -1;
	/*
	* Walk it once, backwards, to build the label table and do fixups.
	* Since backward jumps are disallowed by BPF, this is easy.
	*/
	filter += insn;
	for (; filter >= begin; --insn, --filter) {
		if (filter->code != (BPF_JMP+BPF_JA))
			continue;
		switch ((filter->jt<<8)|filter->jf) {
		case (JUMP_JT<<8)|JUMP_JF:
			if (labels->labels[filter->k].location == 0xffffffff) {
				fprintf(stderr, "Unresolved label: '%s'\n",
					labels->labels[filter->k].label);
				return 1;
			}
			filter->k = labels->labels[filter->k].location -
				    (insn + 1);
			filter->jt = 0;
			filter->jf = 0;
			continue;
		case (LABEL_JT<<8)|LABEL_JF:
			if (labels->labels[filter->k].location != 0xffffffff) {
				fprintf(stderr, "Duplicate label use: '%s'\n",
					labels->labels[filter->k].label);
				return 1;
			}
			labels->labels[filter->k].location = insn;
			filter->k = 0; /* fall through */
			filter->jt = 0;
			filter->jf = 0;
			continue;
		}
	}
	return 0;
}

/* Simple lookup table for labels. */
__u32 seccomp_bpf_label(struct bpf_labels *labels, const char *label)
{
	struct __bpf_label *begin = labels->labels, *end;
	int id;
	if (labels->count == 0) {
		begin->label = label;
		begin->location = 0xffffffff;
		labels->count++;
		return 0;
	}
	end = begin + labels->count;
	for (id = 0; begin < end; ++begin, ++id) {
		if (!strcmp(label, begin->label))
			return id;
	}
	begin->label = label;
	begin->location = 0xffffffff;
	labels->count++;
	return id;
}

void seccomp_bpf_print(struct sock_filter *filter, size_t count)
{
	struct sock_filter *end = filter + count;
	for ( ; filter < end; ++filter)
		printf("{ code=%u,jt=%u,jf=%u,k=%u },\n",
			filter->code, filter->jt, filter->jf, filter->k);
}
