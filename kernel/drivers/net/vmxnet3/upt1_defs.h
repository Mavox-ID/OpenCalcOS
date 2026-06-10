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
#ifndef _UPT1_DEFS_H
#define _UPT1_DEFS_H

struct UPT1_TxStats {
	u64			TSOPktsTxOK;  /* TSO pkts post-segmentation */
	u64			TSOBytesTxOK;
	u64			ucastPktsTxOK;
	u64			ucastBytesTxOK;
	u64			mcastPktsTxOK;
	u64			mcastBytesTxOK;
	u64			bcastPktsTxOK;
	u64			bcastBytesTxOK;
	u64			pktsTxError;
	u64			pktsTxDiscard;
};

struct UPT1_RxStats {
	u64			LROPktsRxOK;    /* LRO pkts */
	u64			LROBytesRxOK;   /* bytes from LRO pkts */
	/* the following counters are for pkts from the wire, i.e., pre-LRO */
	u64			ucastPktsRxOK;
	u64			ucastBytesRxOK;
	u64			mcastPktsRxOK;
	u64			mcastBytesRxOK;
	u64			bcastPktsRxOK;
	u64			bcastBytesRxOK;
	u64			pktsRxOutOfBuf;
	u64			pktsRxError;
};

/* interrupt moderation level */
enum {
	UPT1_IML_NONE		= 0, /* no interrupt moderation */
	UPT1_IML_HIGHEST	= 7, /* least intr generated */
	UPT1_IML_ADAPTIVE	= 8, /* adpative intr moderation */
};
/* values for UPT1_RSSConf.hashFunc */
enum {
	UPT1_RSS_HASH_TYPE_NONE      = 0x0,
	UPT1_RSS_HASH_TYPE_IPV4      = 0x01,
	UPT1_RSS_HASH_TYPE_TCP_IPV4  = 0x02,
	UPT1_RSS_HASH_TYPE_IPV6      = 0x04,
	UPT1_RSS_HASH_TYPE_TCP_IPV6  = 0x08,
};

enum {
	UPT1_RSS_HASH_FUNC_NONE      = 0x0,
	UPT1_RSS_HASH_FUNC_TOEPLITZ  = 0x01,
};

#define UPT1_RSS_MAX_KEY_SIZE        40
#define UPT1_RSS_MAX_IND_TABLE_SIZE  128

struct UPT1_RSSConf {
	u16			hashType;
	u16			hashFunc;
	u16			hashKeySize;
	u16			indTableSize;
	u8			hashKey[UPT1_RSS_MAX_KEY_SIZE];
	u8			indTable[UPT1_RSS_MAX_IND_TABLE_SIZE];
};

/* features */
enum {
	UPT1_F_RXCSUM		= cpu_to_le64(0x0001),   /* rx csum verification */
	UPT1_F_RSS		= cpu_to_le64(0x0002),
	UPT1_F_RXVLAN		= cpu_to_le64(0x0004),   /* VLAN tag stripping */
	UPT1_F_LRO		= cpu_to_le64(0x0008),
};
#endif
