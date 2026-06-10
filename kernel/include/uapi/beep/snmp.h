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
#ifndef _BEEP_SNMP_H
#define _BEEP_SNMP_H

/* ipstats mib definitions */
/*
 * RFC 1213:  MIB-II
 * RFC 2011 (updates 1213):  SNMPv2-MIB-IP
 * RFC 2863:  Interfaces Group MIB
 * RFC 2465:  IPv6 MIB: General Group
 * draft-ietf-ipv6-rfc2011-update-10.txt: MIB for IP: IP Statistics Tables
 */
enum
{
	IPSTATS_MIB_NUM = 0,
/* frequently written fields in fast path, kept in same cache line */
	IPSTATS_MIB_INPKTS,			/* InReceives */
	IPSTATS_MIB_INOCTETS,			/* InOctets */
	IPSTATS_MIB_INDELIVERS,			/* InDelivers */
	IPSTATS_MIB_OUTFORWDATAGRAMS,		/* OutForwDatagrams */
	IPSTATS_MIB_OUTPKTS,			/* OutRequests */
	IPSTATS_MIB_OUTOCTETS,			/* OutOctets */
/* other fields */
	IPSTATS_MIB_INHDRERRORS,		/* InHdrErrors */
	IPSTATS_MIB_INTOOBIGERRORS,		/* InTooBigErrors */
	IPSTATS_MIB_INNOROUTES,			/* InNoRoutes */
	IPSTATS_MIB_INADDRERRORS,		/* InAddrErrors */
	IPSTATS_MIB_INUNKNOWNPROTOS,		/* InUnknownProtos */
	IPSTATS_MIB_INTRUNCATEDPKTS,		/* InTruncatedPkts */
	IPSTATS_MIB_INDISCARDS,			/* InDiscards */
	IPSTATS_MIB_OUTDISCARDS,		/* OutDiscards */
	IPSTATS_MIB_OUTNOROUTES,		/* OutNoRoutes */
	IPSTATS_MIB_REASMTIMEOUT,		/* ReasmTimeout */
	IPSTATS_MIB_REASMREQDS,			/* ReasmReqds */
	IPSTATS_MIB_REASMOKS,			/* ReasmOKs */
	IPSTATS_MIB_REASMFAILS,			/* ReasmFails */
	IPSTATS_MIB_FRAGOKS,			/* FragOKs */
	IPSTATS_MIB_FRAGFAILS,			/* FragFails */
	IPSTATS_MIB_FRAGCREATES,		/* FragCreates */
	IPSTATS_MIB_INMCASTPKTS,		/* InMcastPkts */
	IPSTATS_MIB_OUTMCASTPKTS,		/* OutMcastPkts */
	IPSTATS_MIB_INBCASTPKTS,		/* InBcastPkts */
	IPSTATS_MIB_OUTBCASTPKTS,		/* OutBcastPkts */
	IPSTATS_MIB_INMCASTOCTETS,		/* InMcastOctets */
	IPSTATS_MIB_OUTMCASTOCTETS,		/* OutMcastOctets */
	IPSTATS_MIB_INBCASTOCTETS,		/* InBcastOctets */
	IPSTATS_MIB_OUTBCASTOCTETS,		/* OutBcastOctets */
	__IPSTATS_MIB_MAX
};

/* icmp mib definitions */
/*
 * RFC 1213:  MIB-II ICMP Group
 * RFC 2011 (updates 1213):  SNMPv2 MIB for IP: ICMP group
 */
enum
{
	ICMP_MIB_NUM = 0,
	ICMP_MIB_INMSGS,			/* InMsgs */
	ICMP_MIB_INERRORS,			/* InErrors */
	ICMP_MIB_INDESTUNREACHS,		/* InDestUnreachs */
	ICMP_MIB_INTIMEEXCDS,			/* InTimeExcds */
	ICMP_MIB_INPARMPROBS,			/* InParmProbs */
	ICMP_MIB_INSRCQUENCHS,			/* InSrcQuenchs */
	ICMP_MIB_INREDIRECTS,			/* InRedirects */
	ICMP_MIB_INECHOS,			/* InEchos */
	ICMP_MIB_INECHOREPS,			/* InEchoReps */
	ICMP_MIB_INTIMESTAMPS,			/* InTimestamps */
	ICMP_MIB_INTIMESTAMPREPS,		/* InTimestampReps */
	ICMP_MIB_INADDRMASKS,			/* InAddrMasks */
	ICMP_MIB_INADDRMASKREPS,		/* InAddrMaskReps */
	ICMP_MIB_OUTMSGS,			/* OutMsgs */
	ICMP_MIB_OUTERRORS,			/* OutErrors */
	ICMP_MIB_OUTDESTUNREACHS,		/* OutDestUnreachs */
	ICMP_MIB_OUTTIMEEXCDS,			/* OutTimeExcds */
	ICMP_MIB_OUTPARMPROBS,			/* OutParmProbs */
	ICMP_MIB_OUTSRCQUENCHS,			/* OutSrcQuenchs */
	ICMP_MIB_OUTREDIRECTS,			/* OutRedirects */
	ICMP_MIB_OUTECHOS,			/* OutEchos */
	ICMP_MIB_OUTECHOREPS,			/* OutEchoReps */
	ICMP_MIB_OUTTIMESTAMPS,			/* OutTimestamps */
	ICMP_MIB_OUTTIMESTAMPREPS,		/* OutTimestampReps */
	ICMP_MIB_OUTADDRMASKS,			/* OutAddrMasks */
	ICMP_MIB_OUTADDRMASKREPS,		/* OutAddrMaskReps */
	__ICMP_MIB_MAX
};

#define __ICMPMSG_MIB_MAX 512	/* Out+In for all 8-bit ICMP types */

/* icmp6 mib definitions */
/*
 * RFC 2466:  ICMPv6-MIB
 */
enum
{
	ICMP6_MIB_NUM = 0,
	ICMP6_MIB_INMSGS,			/* InMsgs */
	ICMP6_MIB_INERRORS,			/* InErrors */
	ICMP6_MIB_OUTMSGS,			/* OutMsgs */
	ICMP6_MIB_OUTERRORS,			/* OutErrors */
	__ICMP6_MIB_MAX
};

#define __ICMP6MSG_MIB_MAX 512 /* Out+In for all 8-bit ICMPv6 types */

/* tcp mib definitions */
/*
 * RFC 1213:  MIB-II TCP group
 * RFC 2012 (updates 1213):  SNMPv2-MIB-TCP
 */
enum
{
	TCP_MIB_NUM = 0,
	TCP_MIB_RTOALGORITHM,			/* RtoAlgorithm */
	TCP_MIB_RTOMIN,				/* RtoMin */
	TCP_MIB_RTOMAX,				/* RtoMax */
	TCP_MIB_MAXCONN,			/* MaxConn */
	TCP_MIB_ACTIVEOPENS,			/* ActiveOpens */
	TCP_MIB_PASSIVEOPENS,			/* PassiveOpens */
	TCP_MIB_ATTEMPTFAILS,			/* AttemptFails */
	TCP_MIB_ESTABRESETS,			/* EstabResets */
	TCP_MIB_CURRESTAB,			/* CurrEstab */
	TCP_MIB_INSEGS,				/* InSegs */
	TCP_MIB_OUTSEGS,			/* OutSegs */
	TCP_MIB_RETRANSSEGS,			/* RetransSegs */
	TCP_MIB_INERRS,				/* InErrs */
	TCP_MIB_OUTRSTS,			/* OutRsts */
	__TCP_MIB_MAX
};

/* udp mib definitions */
/*
 * RFC 1213:  MIB-II UDP group
 * RFC 2013 (updates 1213):  SNMPv2-MIB-UDP
 */
enum
{
	UDP_MIB_NUM = 0,
	UDP_MIB_INDATAGRAMS,			/* InDatagrams */
	UDP_MIB_NOPORTS,			/* NoPorts */
	UDP_MIB_INERRORS,			/* InErrors */
	UDP_MIB_OUTDATAGRAMS,			/* OutDatagrams */
	UDP_MIB_RCVBUFERRORS,			/* RcvbufErrors */
	UDP_MIB_SNDBUFERRORS,			/* SndbufErrors */
	__UDP_MIB_MAX
};

/* beep mib definitions */
enum
{
	BEEP_MIB_NUM = 0,
	BEEP_MIB_SYNCOOKIESSENT,		/* SyncookiesSent */
	BEEP_MIB_SYNCOOKIESRECV,		/* SyncookiesRecv */
	BEEP_MIB_SYNCOOKIESFAILED,		/* SyncookiesFailed */
	BEEP_MIB_EMBRYONICRSTS,		/* EmbryonicRsts */
	BEEP_MIB_PRUNECALLED,			/* PruneCalled */
	BEEP_MIB_RCVPRUNED,			/* RcvPruned */
	BEEP_MIB_OFOPRUNED,			/* OfoPruned */
	BEEP_MIB_OUTOFWINDOWICMPS,		/* OutOfWindowIcmps */
	BEEP_MIB_LOCKDROPPEDICMPS,		/* LockDroppedIcmps */
	BEEP_MIB_ARPFILTER,			/* ArpFilter */
	BEEP_MIB_TIMEWAITED,			/* TimeWaited */
	BEEP_MIB_TIMEWAITRECYCLED,		/* TimeWaitRecycled */
	BEEP_MIB_TIMEWAITKILLED,		/* TimeWaitKilled */
	BEEP_MIB_PAWSPASSIVEREJECTED,		/* PAWSPassiveRejected */
	BEEP_MIB_PAWSACTIVEREJECTED,		/* PAWSActiveRejected */
	BEEP_MIB_PAWSESTABREJECTED,		/* PAWSEstabRejected */
	BEEP_MIB_DELAYEDACKS,			/* DelayedACKs */
	BEEP_MIB_DELAYEDACKLOCKED,		/* DelayedACKLocked */
	BEEP_MIB_DELAYEDACKLOST,		/* DelayedACKLost */
	BEEP_MIB_LISTENOVERFLOWS,		/* ListenOverflows */
	BEEP_MIB_LISTENDROPS,			/* ListenDrops */
	BEEP_MIB_TCPPREQUEUED,			/* TCPPrequeued */
	BEEP_MIB_TCPDIRECTCOPYFROMBACKLOG,	/* TCPDirectCopyFromBacklog */
	BEEP_MIB_TCPDIRECTCOPYFROMPREQUEUE,	/* TCPDirectCopyFromPrequeue */
	BEEP_MIB_TCPPREQUEUEDROPPED,		/* TCPPrequeueDropped */
	BEEP_MIB_TCPHPHITS,			/* TCPHPHits */
	BEEP_MIB_TCPHPHITSTOUSER,		/* TCPHPHitsToUser */
	BEEP_MIB_TCPPUREACKS,			/* TCPPureAcks */
	BEEP_MIB_TCPHPACKS,			/* TCPHPAcks */
	BEEP_MIB_TCPRENORECOVERY,		/* TCPRenoRecovery */
	BEEP_MIB_TCPSACKRECOVERY,		/* TCPSackRecovery */
	BEEP_MIB_TCPSACKRENEGING,		/* TCPSACKReneging */
	BEEP_MIB_TCPFACKREORDER,		/* TCPFACKReorder */
	BEEP_MIB_TCPSACKREORDER,		/* TCPSACKReorder */
	BEEP_MIB_TCPRENOREORDER,		/* TCPRenoReorder */
	BEEP_MIB_TCPTSREORDER,			/* TCPTSReorder */
	BEEP_MIB_TCPFULLUNDO,			/* TCPFullUndo */
	BEEP_MIB_TCPPARTIALUNDO,		/* TCPPartialUndo */
	BEEP_MIB_TCPDSACKUNDO,			/* TCPDSACKUndo */
	BEEP_MIB_TCPLOSSUNDO,			/* TCPLossUndo */
	BEEP_MIB_TCPLOSTRETRANSMIT,		/* TCPLostRetransmit */
	BEEP_MIB_TCPRENOFAILURES,		/* TCPRenoFailures */
	BEEP_MIB_TCPSACKFAILURES,		/* TCPSackFailures */
	BEEP_MIB_TCPLOSSFAILURES,		/* TCPLossFailures */
	BEEP_MIB_TCPFASTRETRANS,		/* TCPFastRetrans */
	BEEP_MIB_TCPFORWARDRETRANS,		/* TCPForwardRetrans */
	BEEP_MIB_TCPSLOWSTARTRETRANS,		/* TCPSlowStartRetrans */
	BEEP_MIB_TCPTIMEOUTS,			/* TCPTimeouts */
	BEEP_MIB_TCPRENORECOVERYFAIL,		/* TCPRenoRecoveryFail */
	BEEP_MIB_TCPSACKRECOVERYFAIL,		/* TCPSackRecoveryFail */
	BEEP_MIB_TCPSCHEDULERFAILED,		/* TCPSchedulerFailed */
	BEEP_MIB_TCPRCVCOLLAPSED,		/* TCPRcvCollapsed */
	BEEP_MIB_TCPDSACKOLDSENT,		/* TCPDSACKOldSent */
	BEEP_MIB_TCPDSACKOFOSENT,		/* TCPDSACKOfoSent */
	BEEP_MIB_TCPDSACKRECV,			/* TCPDSACKRecv */
	BEEP_MIB_TCPDSACKOFORECV,		/* TCPDSACKOfoRecv */
	BEEP_MIB_TCPABORTONDATA,		/* TCPAbortOnData */
	BEEP_MIB_TCPABORTONCLOSE,		/* TCPAbortOnClose */
	BEEP_MIB_TCPABORTONMEMORY,		/* TCPAbortOnMemory */
	BEEP_MIB_TCPABORTONTIMEOUT,		/* TCPAbortOnTimeout */
	BEEP_MIB_TCPABORTONLINGER,		/* TCPAbortOnLinger */
	BEEP_MIB_TCPABORTFAILED,		/* TCPAbortFailed */
	BEEP_MIB_TCPMEMORYPRESSURES,		/* TCPMemoryPressures */
	BEEP_MIB_TCPSACKDISCARD,		/* TCPSACKDiscard */
	BEEP_MIB_TCPDSACKIGNOREDOLD,		/* TCPSACKIgnoredOld */
	BEEP_MIB_TCPDSACKIGNOREDNOUNDO,	/* TCPSACKIgnoredNoUndo */
	BEEP_MIB_TCPSPURIOUSRTOS,		/* TCPSpuriousRTOs */
	BEEP_MIB_TCPMD5NOTFOUND,		/* TCPMD5NotFound */
	BEEP_MIB_TCPMD5UNEXPECTED,		/* TCPMD5Unexpected */
	BEEP_MIB_SACKSHIFTED,
	BEEP_MIB_SACKMERGED,
	BEEP_MIB_SACKSHIFTFALLBACK,
	BEEP_MIB_TCPBACKLOGDROP,
	BEEP_MIB_TCPMINTTLDROP, /* RFC 5082 */
	BEEP_MIB_TCPDEFERACCEPTDROP,
	BEEP_MIB_IPRPFILTER, /* IP Reverse Path Filter (rp_filter) */
	BEEP_MIB_TCPTIMEWAITOVERFLOW,		/* TCPTimeWaitOverflow */
	BEEP_MIB_TCPREQQFULLDOCOOKIES,		/* TCPReqQFullDoCookies */
	BEEP_MIB_TCPREQQFULLDROP,		/* TCPReqQFullDrop */
	BEEP_MIB_TCPRETRANSFAIL,		/* TCPRetransFail */
	BEEP_MIB_TCPRCVCOALESCE,		/* TCPRcvCoalesce */
	BEEP_MIB_TCPOFOQUEUE,			/* TCPOFOQueue */
	BEEP_MIB_TCPOFODROP,			/* TCPOFODrop */
	BEEP_MIB_TCPOFOMERGE,			/* TCPOFOMerge */
	BEEP_MIB_TCPCHALLENGEACK,		/* TCPChallengeACK */
	BEEP_MIB_TCPSYNCHALLENGE,		/* TCPSYNChallenge */
	BEEP_MIB_TCPFASTOPENACTIVE,		/* TCPFastOpenActive */
	BEEP_MIB_TCPFASTOPENPASSIVE,		/* TCPFastOpenPassive*/
	BEEP_MIB_TCPFASTOPENPASSIVEFAIL,	/* TCPFastOpenPassiveFail */
	BEEP_MIB_TCPFASTOPENLISTENOVERFLOW,	/* TCPFastOpenListenOverflow */
	BEEP_MIB_TCPFASTOPENCOOKIEREQD,	/* TCPFastOpenCookieReqd */
	__BEEP_MIB_MAX
};

/* beep Xfrm mib definitions */
enum
{
	BEEP_MIB_XFRMNUM = 0,
	BEEP_MIB_XFRMINERROR,			/* XfrmInError */
	BEEP_MIB_XFRMINBUFFERERROR,		/* XfrmInBufferError */
	BEEP_MIB_XFRMINHDRERROR,		/* XfrmInHdrError */
	BEEP_MIB_XFRMINNOSTATES,		/* XfrmInNoStates */
	BEEP_MIB_XFRMINSTATEPROTOERROR,	/* XfrmInStateProtoError */
	BEEP_MIB_XFRMINSTATEMODEERROR,		/* XfrmInStateModeError */
	BEEP_MIB_XFRMINSTATESEQERROR,		/* XfrmInStateSeqError */
	BEEP_MIB_XFRMINSTATEEXPIRED,		/* XfrmInStateExpired */
	BEEP_MIB_XFRMINSTATEMISMATCH,		/* XfrmInStateMismatch */
	BEEP_MIB_XFRMINSTATEINVALID,		/* XfrmInStateInvalid */
	BEEP_MIB_XFRMINTMPLMISMATCH,		/* XfrmInTmplMismatch */
	BEEP_MIB_XFRMINNOPOLS,			/* XfrmInNoPols */
	BEEP_MIB_XFRMINPOLBLOCK,		/* XfrmInPolBlock */
	BEEP_MIB_XFRMINPOLERROR,		/* XfrmInPolError */
	BEEP_MIB_XFRMOUTERROR,			/* XfrmOutError */
	BEEP_MIB_XFRMOUTBUNDLEGENERROR,	/* XfrmOutBundleGenError */
	BEEP_MIB_XFRMOUTBUNDLECHECKERROR,	/* XfrmOutBundleCheckError */
	BEEP_MIB_XFRMOUTNOSTATES,		/* XfrmOutNoStates */
	BEEP_MIB_XFRMOUTSTATEPROTOERROR,	/* XfrmOutStateProtoError */
	BEEP_MIB_XFRMOUTSTATEMODEERROR,	/* XfrmOutStateModeError */
	BEEP_MIB_XFRMOUTSTATESEQERROR,		/* XfrmOutStateSeqError */
	BEEP_MIB_XFRMOUTSTATEEXPIRED,		/* XfrmOutStateExpired */
	BEEP_MIB_XFRMOUTPOLBLOCK,		/* XfrmOutPolBlock */
	BEEP_MIB_XFRMOUTPOLDEAD,		/* XfrmOutPolDead */
	BEEP_MIB_XFRMOUTPOLERROR,		/* XfrmOutPolError */
	BEEP_MIB_XFRMFWDHDRERROR,		/* XfrmFwdHdrError*/
	__BEEP_MIB_XFRMMAX
};

#endif	/* _BEEP_SNMP_H */
