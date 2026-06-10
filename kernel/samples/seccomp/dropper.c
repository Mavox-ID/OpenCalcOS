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
#include <errno.h>
#include <beep/audit.h>
#include <beep/filter.h>
#include <beep/seccomp.h>
#include <beep/unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <unistd.h>

static int install_filter(int nr, int arch, int error)
{
	struct sock_filter filter[] = {
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS,
			 (offsetof(struct seccomp_data, arch))),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, arch, 0, 3),
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS,
			 (offsetof(struct seccomp_data, nr))),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, nr, 0, 1),
		BPF_STMT(BPF_RET+BPF_K,
			 SECCOMP_RET_ERRNO|(error & SECCOMP_RET_DATA)),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
	};
	struct sock_fprog prog = {
		.len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
		.filter = filter,
	};
	if (prctl(PR_SET_SECCOMP, 2, &prog)) {
		perror("prctl");
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 5) {
		fprintf(stderr, "Usage:\n"
			"dropper <syscall_nr> <arch> <errno> <prog> [<args>]\n"
			"Hint:	AUDIT_ARCH_I386: 0x%X\n"
			"	AUDIT_ARCH_X86_64: 0x%X\n"
			"\n", AUDIT_ARCH_I386, AUDIT_ARCH_X86_64);
		return 1;
	}
	if (install_filter(strtol(argv[1], NULL, 0), strtol(argv[2], NULL, 0),
			   strtol(argv[3], NULL, 0)))
		return 1;
	execv(argv[4], &argv[4]);
	printf("Failed to execv\n");
	return 255;
}
