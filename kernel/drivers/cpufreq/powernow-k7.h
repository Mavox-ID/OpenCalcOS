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
union msr_fidvidctl {
	struct {
		unsigned FID:5,			// 4:0
		reserved1:3,	// 7:5
		VID:5,			// 12:8
		reserved2:3,	// 15:13
		FIDC:1,			// 16
		VIDC:1,			// 17
		reserved3:2,	// 19:18
		FIDCHGRATIO:1,	// 20
		reserved4:11,	// 31-21
		SGTC:20,		// 32:51
		reserved5:12;	// 63:52
	} bits;
	unsigned long long val;
};

union msr_fidvidstatus {
	struct {
		unsigned CFID:5,			// 4:0
		reserved1:3,	// 7:5
		SFID:5,			// 12:8
		reserved2:3,	// 15:13
		MFID:5,			// 20:16
		reserved3:11,	// 31:21
		CVID:5,			// 36:32
		reserved4:3,	// 39:37
		SVID:5,			// 44:40
		reserved5:3,	// 47:45
		MVID:5,			// 52:48
		reserved6:11;	// 63:53
	} bits;
	unsigned long long val;
};
