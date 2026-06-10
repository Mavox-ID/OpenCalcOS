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
#ifndef _ASM_S390_CPCMD_H
#define _ASM_S390_CPCMD_H

/*
 * the lowlevel function for cpcmd
 * the caller of __cpcmd has to ensure that the response buffer is below 2 GB
 */
extern int __cpcmd(const char *cmd, char *response, int rlen, int *response_code);

/*
 * cpcmd is the in-kernel interface for issuing CP commands
 *
 * cmd:		null-terminated command string, max 240 characters
 * response:	response buffer for VM's textual response
 * rlen:	size of the response buffer, cpcmd will not exceed this size
 *		but will cap the output, if its too large. Everything that
 *		did not fit into the buffer will be silently dropped
 * response_code: return pointer for VM's error code
 * return value: the size of the response. The caller can check if the buffer
 *		was large enough by comparing the return value and rlen
 * NOTE: If the response buffer is not below 2 GB, cpcmd can sleep
 */
extern int cpcmd(const char *cmd, char *response, int rlen, int *response_code);

#endif /* _ASM_S390_CPCMD_H */
