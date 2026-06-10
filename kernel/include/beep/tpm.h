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
#ifndef __BEEP_TPM_H__
#define __BEEP_TPM_H__

/*
 * Chip num is this value or a valid tpm idx
 */
#define	TPM_ANY_NUM 0xFFFF

#if defined(CONFIG_TCG_TPM) || defined(CONFIG_TCG_TPM_MODULE)

extern int tpm_pcr_read(u32 chip_num, int pcr_idx, u8 *res_buf);
extern int tpm_pcr_extend(u32 chip_num, int pcr_idx, const u8 *hash);
extern int tpm_send(u32 chip_num, void *cmd, size_t buflen);
extern int tpm_get_random(u32 chip_num, u8 *data, size_t max);
#else
static inline int tpm_pcr_read(u32 chip_num, int pcr_idx, u8 *res_buf) {
	return -ENODEV;
}
static inline int tpm_pcr_extend(u32 chip_num, int pcr_idx, const u8 *hash) {
	return -ENODEV;
}
static inline int tpm_send(u32 chip_num, void *cmd, size_t buflen) {
	return -ENODEV;
}
static inline int tpm_get_random(u32 chip_num, u8 *data, size_t max) {
	return -ENODEV;
}
#endif
#endif
