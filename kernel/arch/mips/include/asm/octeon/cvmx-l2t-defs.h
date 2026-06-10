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
#ifndef __CVMX_L2T_DEFS_H__
#define __CVMX_L2T_DEFS_H__

#define CVMX_L2T_ERR (CVMX_ADD_IO_SEG(0x0001180080000008ull))

union cvmx_l2t_err {
	uint64_t u64;
	struct cvmx_l2t_err_s {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_29_63:35;
		uint64_t fadru:1;
		uint64_t lck_intena2:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena:1;
		uint64_t lckerr:1;
		uint64_t fset:3;
		uint64_t fadr:10;
		uint64_t fsyn:6;
		uint64_t ded_err:1;
		uint64_t sec_err:1;
		uint64_t ded_intena:1;
		uint64_t sec_intena:1;
		uint64_t ecc_ena:1;
#else
		uint64_t ecc_ena:1;
		uint64_t sec_intena:1;
		uint64_t ded_intena:1;
		uint64_t sec_err:1;
		uint64_t ded_err:1;
		uint64_t fsyn:6;
		uint64_t fadr:10;
		uint64_t fset:3;
		uint64_t lckerr:1;
		uint64_t lck_intena:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena2:1;
		uint64_t fadru:1;
		uint64_t reserved_29_63:35;
#endif
	} s;
	struct cvmx_l2t_err_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_28_63:36;
		uint64_t lck_intena2:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena:1;
		uint64_t lckerr:1;
		uint64_t reserved_23_23:1;
		uint64_t fset:2;
		uint64_t reserved_19_20:2;
		uint64_t fadr:8;
		uint64_t fsyn:6;
		uint64_t ded_err:1;
		uint64_t sec_err:1;
		uint64_t ded_intena:1;
		uint64_t sec_intena:1;
		uint64_t ecc_ena:1;
#else
		uint64_t ecc_ena:1;
		uint64_t sec_intena:1;
		uint64_t ded_intena:1;
		uint64_t sec_err:1;
		uint64_t ded_err:1;
		uint64_t fsyn:6;
		uint64_t fadr:8;
		uint64_t reserved_19_20:2;
		uint64_t fset:2;
		uint64_t reserved_23_23:1;
		uint64_t lckerr:1;
		uint64_t lck_intena:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena2:1;
		uint64_t reserved_28_63:36;
#endif
	} cn30xx;
	struct cvmx_l2t_err_cn31xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_28_63:36;
		uint64_t lck_intena2:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena:1;
		uint64_t lckerr:1;
		uint64_t reserved_23_23:1;
		uint64_t fset:2;
		uint64_t reserved_20_20:1;
		uint64_t fadr:9;
		uint64_t fsyn:6;
		uint64_t ded_err:1;
		uint64_t sec_err:1;
		uint64_t ded_intena:1;
		uint64_t sec_intena:1;
		uint64_t ecc_ena:1;
#else
		uint64_t ecc_ena:1;
		uint64_t sec_intena:1;
		uint64_t ded_intena:1;
		uint64_t sec_err:1;
		uint64_t ded_err:1;
		uint64_t fsyn:6;
		uint64_t fadr:9;
		uint64_t reserved_20_20:1;
		uint64_t fset:2;
		uint64_t reserved_23_23:1;
		uint64_t lckerr:1;
		uint64_t lck_intena:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena2:1;
		uint64_t reserved_28_63:36;
#endif
	} cn31xx;
	struct cvmx_l2t_err_cn38xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_28_63:36;
		uint64_t lck_intena2:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena:1;
		uint64_t lckerr:1;
		uint64_t fset:3;
		uint64_t fadr:10;
		uint64_t fsyn:6;
		uint64_t ded_err:1;
		uint64_t sec_err:1;
		uint64_t ded_intena:1;
		uint64_t sec_intena:1;
		uint64_t ecc_ena:1;
#else
		uint64_t ecc_ena:1;
		uint64_t sec_intena:1;
		uint64_t ded_intena:1;
		uint64_t sec_err:1;
		uint64_t ded_err:1;
		uint64_t fsyn:6;
		uint64_t fadr:10;
		uint64_t fset:3;
		uint64_t lckerr:1;
		uint64_t lck_intena:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena2:1;
		uint64_t reserved_28_63:36;
#endif
	} cn38xx;
	struct cvmx_l2t_err_cn38xx cn38xxp2;
	struct cvmx_l2t_err_cn50xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_28_63:36;
		uint64_t lck_intena2:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena:1;
		uint64_t lckerr:1;
		uint64_t fset:3;
		uint64_t reserved_18_20:3;
		uint64_t fadr:7;
		uint64_t fsyn:6;
		uint64_t ded_err:1;
		uint64_t sec_err:1;
		uint64_t ded_intena:1;
		uint64_t sec_intena:1;
		uint64_t ecc_ena:1;
#else
		uint64_t ecc_ena:1;
		uint64_t sec_intena:1;
		uint64_t ded_intena:1;
		uint64_t sec_err:1;
		uint64_t ded_err:1;
		uint64_t fsyn:6;
		uint64_t fadr:7;
		uint64_t reserved_18_20:3;
		uint64_t fset:3;
		uint64_t lckerr:1;
		uint64_t lck_intena:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena2:1;
		uint64_t reserved_28_63:36;
#endif
	} cn50xx;
	struct cvmx_l2t_err_cn52xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_28_63:36;
		uint64_t lck_intena2:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena:1;
		uint64_t lckerr:1;
		uint64_t fset:3;
		uint64_t reserved_20_20:1;
		uint64_t fadr:9;
		uint64_t fsyn:6;
		uint64_t ded_err:1;
		uint64_t sec_err:1;
		uint64_t ded_intena:1;
		uint64_t sec_intena:1;
		uint64_t ecc_ena:1;
#else
		uint64_t ecc_ena:1;
		uint64_t sec_intena:1;
		uint64_t ded_intena:1;
		uint64_t sec_err:1;
		uint64_t ded_err:1;
		uint64_t fsyn:6;
		uint64_t fadr:9;
		uint64_t reserved_20_20:1;
		uint64_t fset:3;
		uint64_t lckerr:1;
		uint64_t lck_intena:1;
		uint64_t lckerr2:1;
		uint64_t lck_intena2:1;
		uint64_t reserved_28_63:36;
#endif
	} cn52xx;
	struct cvmx_l2t_err_cn52xx cn52xxp1;
	struct cvmx_l2t_err_s cn56xx;
	struct cvmx_l2t_err_s cn56xxp1;
	struct cvmx_l2t_err_s cn58xx;
	struct cvmx_l2t_err_s cn58xxp1;
};

#endif
