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
#ifndef __CVMX_MPI_DEFS_H__
#define __CVMX_MPI_DEFS_H__

#define CVMX_MPI_CFG (CVMX_ADD_IO_SEG(0x0001070000001000ull))
#define CVMX_MPI_DATX(offset) (CVMX_ADD_IO_SEG(0x0001070000001080ull) + ((offset) & 15) * 8)
#define CVMX_MPI_STS (CVMX_ADD_IO_SEG(0x0001070000001008ull))
#define CVMX_MPI_TX (CVMX_ADD_IO_SEG(0x0001070000001010ull))

union cvmx_mpi_cfg {
	uint64_t u64;
	struct cvmx_mpi_cfg_s {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_29_63:35;
		uint64_t clkdiv:13;
		uint64_t csena3:1;
		uint64_t csena2:1;
		uint64_t csena1:1;
		uint64_t csena0:1;
		uint64_t cslate:1;
		uint64_t tritx:1;
		uint64_t idleclks:2;
		uint64_t cshi:1;
		uint64_t csena:1;
		uint64_t int_ena:1;
		uint64_t lsbfirst:1;
		uint64_t wireor:1;
		uint64_t clk_cont:1;
		uint64_t idlelo:1;
		uint64_t enable:1;
#else
		uint64_t enable:1;
		uint64_t idlelo:1;
		uint64_t clk_cont:1;
		uint64_t wireor:1;
		uint64_t lsbfirst:1;
		uint64_t int_ena:1;
		uint64_t csena:1;
		uint64_t cshi:1;
		uint64_t idleclks:2;
		uint64_t tritx:1;
		uint64_t cslate:1;
		uint64_t csena0:1;
		uint64_t csena1:1;
		uint64_t csena2:1;
		uint64_t csena3:1;
		uint64_t clkdiv:13;
		uint64_t reserved_29_63:35;
#endif
	} s;
	struct cvmx_mpi_cfg_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_29_63:35;
		uint64_t clkdiv:13;
		uint64_t reserved_12_15:4;
		uint64_t cslate:1;
		uint64_t tritx:1;
		uint64_t idleclks:2;
		uint64_t cshi:1;
		uint64_t csena:1;
		uint64_t int_ena:1;
		uint64_t lsbfirst:1;
		uint64_t wireor:1;
		uint64_t clk_cont:1;
		uint64_t idlelo:1;
		uint64_t enable:1;
#else
		uint64_t enable:1;
		uint64_t idlelo:1;
		uint64_t clk_cont:1;
		uint64_t wireor:1;
		uint64_t lsbfirst:1;
		uint64_t int_ena:1;
		uint64_t csena:1;
		uint64_t cshi:1;
		uint64_t idleclks:2;
		uint64_t tritx:1;
		uint64_t cslate:1;
		uint64_t reserved_12_15:4;
		uint64_t clkdiv:13;
		uint64_t reserved_29_63:35;
#endif
	} cn30xx;
	struct cvmx_mpi_cfg_cn31xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_29_63:35;
		uint64_t clkdiv:13;
		uint64_t reserved_11_15:5;
		uint64_t tritx:1;
		uint64_t idleclks:2;
		uint64_t cshi:1;
		uint64_t csena:1;
		uint64_t int_ena:1;
		uint64_t lsbfirst:1;
		uint64_t wireor:1;
		uint64_t clk_cont:1;
		uint64_t idlelo:1;
		uint64_t enable:1;
#else
		uint64_t enable:1;
		uint64_t idlelo:1;
		uint64_t clk_cont:1;
		uint64_t wireor:1;
		uint64_t lsbfirst:1;
		uint64_t int_ena:1;
		uint64_t csena:1;
		uint64_t cshi:1;
		uint64_t idleclks:2;
		uint64_t tritx:1;
		uint64_t reserved_11_15:5;
		uint64_t clkdiv:13;
		uint64_t reserved_29_63:35;
#endif
	} cn31xx;
	struct cvmx_mpi_cfg_cn30xx cn50xx;
	struct cvmx_mpi_cfg_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_29_63:35;
		uint64_t clkdiv:13;
		uint64_t reserved_14_15:2;
		uint64_t csena1:1;
		uint64_t csena0:1;
		uint64_t cslate:1;
		uint64_t tritx:1;
		uint64_t idleclks:2;
		uint64_t cshi:1;
		uint64_t reserved_6_6:1;
		uint64_t int_ena:1;
		uint64_t lsbfirst:1;
		uint64_t wireor:1;
		uint64_t clk_cont:1;
		uint64_t idlelo:1;
		uint64_t enable:1;
#else
		uint64_t enable:1;
		uint64_t idlelo:1;
		uint64_t clk_cont:1;
		uint64_t wireor:1;
		uint64_t lsbfirst:1;
		uint64_t int_ena:1;
		uint64_t reserved_6_6:1;
		uint64_t cshi:1;
		uint64_t idleclks:2;
		uint64_t tritx:1;
		uint64_t cslate:1;
		uint64_t csena0:1;
		uint64_t csena1:1;
		uint64_t reserved_14_15:2;
		uint64_t clkdiv:13;
		uint64_t reserved_29_63:35;
#endif
	} cn61xx;
	struct cvmx_mpi_cfg_cn66xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_29_63:35;
		uint64_t clkdiv:13;
		uint64_t csena3:1;
		uint64_t csena2:1;
		uint64_t reserved_12_13:2;
		uint64_t cslate:1;
		uint64_t tritx:1;
		uint64_t idleclks:2;
		uint64_t cshi:1;
		uint64_t reserved_6_6:1;
		uint64_t int_ena:1;
		uint64_t lsbfirst:1;
		uint64_t wireor:1;
		uint64_t clk_cont:1;
		uint64_t idlelo:1;
		uint64_t enable:1;
#else
		uint64_t enable:1;
		uint64_t idlelo:1;
		uint64_t clk_cont:1;
		uint64_t wireor:1;
		uint64_t lsbfirst:1;
		uint64_t int_ena:1;
		uint64_t reserved_6_6:1;
		uint64_t cshi:1;
		uint64_t idleclks:2;
		uint64_t tritx:1;
		uint64_t cslate:1;
		uint64_t reserved_12_13:2;
		uint64_t csena2:1;
		uint64_t csena3:1;
		uint64_t clkdiv:13;
		uint64_t reserved_29_63:35;
#endif
	} cn66xx;
	struct cvmx_mpi_cfg_cn61xx cnf71xx;
};

union cvmx_mpi_datx {
	uint64_t u64;
	struct cvmx_mpi_datx_s {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_8_63:56;
		uint64_t data:8;
#else
		uint64_t data:8;
		uint64_t reserved_8_63:56;
#endif
	} s;
	struct cvmx_mpi_datx_s cn30xx;
	struct cvmx_mpi_datx_s cn31xx;
	struct cvmx_mpi_datx_s cn50xx;
	struct cvmx_mpi_datx_s cn61xx;
	struct cvmx_mpi_datx_s cn66xx;
	struct cvmx_mpi_datx_s cnf71xx;
};

union cvmx_mpi_sts {
	uint64_t u64;
	struct cvmx_mpi_sts_s {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_13_63:51;
		uint64_t rxnum:5;
		uint64_t reserved_1_7:7;
		uint64_t busy:1;
#else
		uint64_t busy:1;
		uint64_t reserved_1_7:7;
		uint64_t rxnum:5;
		uint64_t reserved_13_63:51;
#endif
	} s;
	struct cvmx_mpi_sts_s cn30xx;
	struct cvmx_mpi_sts_s cn31xx;
	struct cvmx_mpi_sts_s cn50xx;
	struct cvmx_mpi_sts_s cn61xx;
	struct cvmx_mpi_sts_s cn66xx;
	struct cvmx_mpi_sts_s cnf71xx;
};

union cvmx_mpi_tx {
	uint64_t u64;
	struct cvmx_mpi_tx_s {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_22_63:42;
		uint64_t csid:2;
		uint64_t reserved_17_19:3;
		uint64_t leavecs:1;
		uint64_t reserved_13_15:3;
		uint64_t txnum:5;
		uint64_t reserved_5_7:3;
		uint64_t totnum:5;
#else
		uint64_t totnum:5;
		uint64_t reserved_5_7:3;
		uint64_t txnum:5;
		uint64_t reserved_13_15:3;
		uint64_t leavecs:1;
		uint64_t reserved_17_19:3;
		uint64_t csid:2;
		uint64_t reserved_22_63:42;
#endif
	} s;
	struct cvmx_mpi_tx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_17_63:47;
		uint64_t leavecs:1;
		uint64_t reserved_13_15:3;
		uint64_t txnum:5;
		uint64_t reserved_5_7:3;
		uint64_t totnum:5;
#else
		uint64_t totnum:5;
		uint64_t reserved_5_7:3;
		uint64_t txnum:5;
		uint64_t reserved_13_15:3;
		uint64_t leavecs:1;
		uint64_t reserved_17_63:47;
#endif
	} cn30xx;
	struct cvmx_mpi_tx_cn30xx cn31xx;
	struct cvmx_mpi_tx_cn30xx cn50xx;
	struct cvmx_mpi_tx_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t reserved_21_63:43;
		uint64_t csid:1;
		uint64_t reserved_17_19:3;
		uint64_t leavecs:1;
		uint64_t reserved_13_15:3;
		uint64_t txnum:5;
		uint64_t reserved_5_7:3;
		uint64_t totnum:5;
#else
		uint64_t totnum:5;
		uint64_t reserved_5_7:3;
		uint64_t txnum:5;
		uint64_t reserved_13_15:3;
		uint64_t leavecs:1;
		uint64_t reserved_17_19:3;
		uint64_t csid:1;
		uint64_t reserved_21_63:43;
#endif
	} cn61xx;
	struct cvmx_mpi_tx_s cn66xx;
	struct cvmx_mpi_tx_cn61xx cnf71xx;
};

#endif
