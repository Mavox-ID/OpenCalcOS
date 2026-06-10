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
#ifndef _ASM_PMON_H
#define _ASM_PMON_H

struct callvectors {
	int	(*open) (char*, int, int);
	int	(*close) (int);
	int	(*read) (int, void*, int);
	int	(*write) (int, void*, int);
	off_t	(*lseek) (int, off_t, int);
	int	(*printf) (const char*, ...);
	void	(*cacheflush) (void);
	char*	(*gets) (char*);
	union {
		int	(*smpfork) (unsigned long cp, char *sp);
		int	(*cpustart) (long, void (*)(void), void *, long);
	} _s;
	int	(*semlock) (int sem);
	void	(*semunlock) (int sem);
};

extern struct callvectors *debug_vectors;

#define pmon_open(name, flags, mode)	debug_vectors->open(name, flage, mode)
#define pmon_close(fd)			debug_vectors->close(fd)
#define pmon_read(fd, buf, count)	debug_vectors->read(fd, buf, count)
#define pmon_write(fd, buf, count)	debug_vectors->write(fd, buf, count)
#define pmon_lseek(fd, off, whence)	debug_vectors->lseek(fd, off, whence)
#define pmon_printf(fmt...)		debug_vectors->printf(fmt)
#define pmon_cacheflush()		debug_vectors->cacheflush()
#define pmon_gets(s)			debug_vectors->gets(s)
#define pmon_cpustart(n, f, sp, gp)	debug_vectors->_s.cpustart(n, f, sp, gp)
#define pmon_smpfork(cp, sp)		debug_vectors->_s.smpfork(cp, sp)
#define pmon_semlock(sem)		debug_vectors->semlock(sem)
#define pmon_semunlock(sem)		debug_vectors->semunlock(sem)

#endif /* _ASM_PMON_H */
