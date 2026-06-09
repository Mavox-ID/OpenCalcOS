/*
 * INET		An implementation of the TCP/IP protocol suite for the BEEP
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		This file implements the various access functions for the
 *		PROC file system.  It is mainly used for debugging and
 *		statistics.
 *
 * Authors:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Gerald J. Heim, <heim@peanuts.informatik.uni-tuebingen.de>
 *		Fred Baumgarten, <dc6iq@insu1.etec.uni-karlsruhe.de>
 *		Erik Schoenfelder, <schoenfr@ibr.cs.tu-bs.de>
 *
 * Fixes:
 *		Alan Cox	:	UDP sockets show the rxqueue/txqueue
 *					using hint flag for the netinfo.
 *	Pauline Middelink	:	identd support
 *		Alan Cox	:	Make /proc safer.
 *	Erik Schoenfelder	:	/proc/net/snmp
 *		Alan Cox	:	Handle dead sockets properly.
 *	Gerhard Koerting	:	Show both timers
 *		Alan Cox	:	Allow inode to be NULL (kernel socket)
 *	Andi Kleen		:	Add support for open_requests and
 *					split functions for more readibility.
 *	Andi Kleen		:	Add support for /proc/net/netstat
 *	Arnaldo C. Melo		:	Convert to seq_file
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#include <beep/types.h>
#include <net/net_namespace.h>
#include <net/icmp.h>
#include <net/protocol.h>
#include <net/tcp.h>
#include <net/udp.h>
#include <net/udplite.h>
#include <beep/bottom_half.h>
#include <beep/inetdevice.h>
#include <beep/proc_fs.h>
#include <beep/seq_file.h>
#include <beep/export.h>
#include <net/sock.h>
#include <net/raw.h>

/*
 *	Report socket allocation statistics [mea@utu.fi]
 */
static int sockstat_seq_show(struct seq_file *seq, void *v)
{
	struct net *net = seq->private;
	int orphans, sockets;

	local_bh_disable();
	orphans = percpu_counter_sum_positive(&tcp_orphan_count);
	sockets = proto_sockets_allocated_sum_positive(&tcp_prot);
	local_bh_enable();

	socket_seq_show(seq);
	seq_printf(seq, "TCP: inuse %d orphan %d tw %d alloc %d mem %ld\n",
		   sock_prot_inuse_get(net, &tcp_prot), orphans,
		   tcp_death_row.tw_count, sockets,
		   proto_memory_allocated(&tcp_prot));
	seq_printf(seq, "UDP: inuse %d mem %ld\n",
		   sock_prot_inuse_get(net, &udp_prot),
		   proto_memory_allocated(&udp_prot));
	seq_printf(seq, "UDPLITE: inuse %d\n",
		   sock_prot_inuse_get(net, &udplite_prot));
	seq_printf(seq, "RAW: inuse %d\n",
		   sock_prot_inuse_get(net, &raw_prot));
	seq_printf(seq,  "FRAG: inuse %d memory %d\n",
			ip_frag_nqueues(net), ip_frag_mem(net));
	return 0;
}

static int sockstat_seq_open(struct inode *inode, struct file *file)
{
	return single_open_net(inode, file, sockstat_seq_show);
}

static const struct file_operations sockstat_seq_fops = {
	.owner	 = THIS_MODULE,
	.open	 = sockstat_seq_open,
	.read	 = seq_read,
	.llseek	 = seq_lseek,
	.release = single_release_net,
};

/* snmp items */
static const struct snmp_mib snmp4_ipstats_list[] = {
	SNMP_MIB_ITEM("InReceives", IPSTATS_MIB_INPKTS),
	SNMP_MIB_ITEM("InHdrErrors", IPSTATS_MIB_INHDRERRORS),
	SNMP_MIB_ITEM("InAddrErrors", IPSTATS_MIB_INADDRERRORS),
	SNMP_MIB_ITEM("ForwDatagrams", IPSTATS_MIB_OUTFORWDATAGRAMS),
	SNMP_MIB_ITEM("InUnknownProtos", IPSTATS_MIB_INUNKNOWNPROTOS),
	SNMP_MIB_ITEM("InDiscards", IPSTATS_MIB_INDISCARDS),
	SNMP_MIB_ITEM("InDelivers", IPSTATS_MIB_INDELIVERS),
	SNMP_MIB_ITEM("OutRequests", IPSTATS_MIB_OUTPKTS),
	SNMP_MIB_ITEM("OutDiscards", IPSTATS_MIB_OUTDISCARDS),
	SNMP_MIB_ITEM("OutNoRoutes", IPSTATS_MIB_OUTNOROUTES),
	SNMP_MIB_ITEM("ReasmTimeout", IPSTATS_MIB_REASMTIMEOUT),
	SNMP_MIB_ITEM("ReasmReqds", IPSTATS_MIB_REASMREQDS),
	SNMP_MIB_ITEM("ReasmOKs", IPSTATS_MIB_REASMOKS),
	SNMP_MIB_ITEM("ReasmFails", IPSTATS_MIB_REASMFAILS),
	SNMP_MIB_ITEM("FragOKs", IPSTATS_MIB_FRAGOKS),
	SNMP_MIB_ITEM("FragFails", IPSTATS_MIB_FRAGFAILS),
	SNMP_MIB_ITEM("FragCreates", IPSTATS_MIB_FRAGCREATES),
	SNMP_MIB_SENTINEL
};

/* Following RFC4293 items are displayed in /proc/net/netstat */
static const struct snmp_mib snmp4_ipextstats_list[] = {
	SNMP_MIB_ITEM("InNoRoutes", IPSTATS_MIB_INNOROUTES),
	SNMP_MIB_ITEM("InTruncatedPkts", IPSTATS_MIB_INTRUNCATEDPKTS),
	SNMP_MIB_ITEM("InMcastPkts", IPSTATS_MIB_INMCASTPKTS),
	SNMP_MIB_ITEM("OutMcastPkts", IPSTATS_MIB_OUTMCASTPKTS),
	SNMP_MIB_ITEM("InBcastPkts", IPSTATS_MIB_INBCASTPKTS),
	SNMP_MIB_ITEM("OutBcastPkts", IPSTATS_MIB_OUTBCASTPKTS),
	SNMP_MIB_ITEM("InOctets", IPSTATS_MIB_INOCTETS),
	SNMP_MIB_ITEM("OutOctets", IPSTATS_MIB_OUTOCTETS),
	SNMP_MIB_ITEM("InMcastOctets", IPSTATS_MIB_INMCASTOCTETS),
	SNMP_MIB_ITEM("OutMcastOctets", IPSTATS_MIB_OUTMCASTOCTETS),
	SNMP_MIB_ITEM("InBcastOctets", IPSTATS_MIB_INBCASTOCTETS),
	SNMP_MIB_ITEM("OutBcastOctets", IPSTATS_MIB_OUTBCASTOCTETS),
	SNMP_MIB_SENTINEL
};

static const struct {
	const char *name;
	int index;
} icmpmibmap[] = {
	{ "DestUnreachs", ICMP_DEST_UNREACH },
	{ "TimeExcds", ICMP_TIME_EXCEEDED },
	{ "ParmProbs", ICMP_PARAMETERPROB },
	{ "SrcQuenchs", ICMP_SOURCE_QUENCH },
	{ "Redirects", ICMP_REDIRECT },
	{ "Echos", ICMP_ECHO },
	{ "EchoReps", ICMP_ECHOREPLY },
	{ "Timestamps", ICMP_TIMESTAMP },
	{ "TimestampReps", ICMP_TIMESTAMPREPLY },
	{ "AddrMasks", ICMP_ADDRESS },
	{ "AddrMaskReps", ICMP_ADDRESSREPLY },
	{ NULL, 0 }
};


static const struct snmp_mib snmp4_tcp_list[] = {
	SNMP_MIB_ITEM("RtoAlgorithm", TCP_MIB_RTOALGORITHM),
	SNMP_MIB_ITEM("RtoMin", TCP_MIB_RTOMIN),
	SNMP_MIB_ITEM("RtoMax", TCP_MIB_RTOMAX),
	SNMP_MIB_ITEM("MaxConn", TCP_MIB_MAXCONN),
	SNMP_MIB_ITEM("ActiveOpens", TCP_MIB_ACTIVEOPENS),
	SNMP_MIB_ITEM("PassiveOpens", TCP_MIB_PASSIVEOPENS),
	SNMP_MIB_ITEM("AttemptFails", TCP_MIB_ATTEMPTFAILS),
	SNMP_MIB_ITEM("EstabResets", TCP_MIB_ESTABRESETS),
	SNMP_MIB_ITEM("CurrEstab", TCP_MIB_CURRESTAB),
	SNMP_MIB_ITEM("InSegs", TCP_MIB_INSEGS),
	SNMP_MIB_ITEM("OutSegs", TCP_MIB_OUTSEGS),
	SNMP_MIB_ITEM("RetransSegs", TCP_MIB_RETRANSSEGS),
	SNMP_MIB_ITEM("InErrs", TCP_MIB_INERRS),
	SNMP_MIB_ITEM("OutRsts", TCP_MIB_OUTRSTS),
	SNMP_MIB_SENTINEL
};

static const struct snmp_mib snmp4_udp_list[] = {
	SNMP_MIB_ITEM("InDatagrams", UDP_MIB_INDATAGRAMS),
	SNMP_MIB_ITEM("NoPorts", UDP_MIB_NOPORTS),
	SNMP_MIB_ITEM("InErrors", UDP_MIB_INERRORS),
	SNMP_MIB_ITEM("OutDatagrams", UDP_MIB_OUTDATAGRAMS),
	SNMP_MIB_ITEM("RcvbufErrors", UDP_MIB_RCVBUFERRORS),
	SNMP_MIB_ITEM("SndbufErrors", UDP_MIB_SNDBUFERRORS),
	SNMP_MIB_SENTINEL
};

static const struct snmp_mib snmp4_net_list[] = {
	SNMP_MIB_ITEM("SyncookiesSent", BEEP_MIB_SYNCOOKIESSENT),
	SNMP_MIB_ITEM("SyncookiesRecv", BEEP_MIB_SYNCOOKIESRECV),
	SNMP_MIB_ITEM("SyncookiesFailed", BEEP_MIB_SYNCOOKIESFAILED),
	SNMP_MIB_ITEM("EmbryonicRsts", BEEP_MIB_EMBRYONICRSTS),
	SNMP_MIB_ITEM("PruneCalled", BEEP_MIB_PRUNECALLED),
	SNMP_MIB_ITEM("RcvPruned", BEEP_MIB_RCVPRUNED),
	SNMP_MIB_ITEM("OfoPruned", BEEP_MIB_OFOPRUNED),
	SNMP_MIB_ITEM("OutOfWindowIcmps", BEEP_MIB_OUTOFWINDOWICMPS),
	SNMP_MIB_ITEM("LockDroppedIcmps", BEEP_MIB_LOCKDROPPEDICMPS),
	SNMP_MIB_ITEM("ArpFilter", BEEP_MIB_ARPFILTER),
	SNMP_MIB_ITEM("TW", BEEP_MIB_TIMEWAITED),
	SNMP_MIB_ITEM("TWRecycled", BEEP_MIB_TIMEWAITRECYCLED),
	SNMP_MIB_ITEM("TWKilled", BEEP_MIB_TIMEWAITKILLED),
	SNMP_MIB_ITEM("PAWSPassive", BEEP_MIB_PAWSPASSIVEREJECTED),
	SNMP_MIB_ITEM("PAWSActive", BEEP_MIB_PAWSACTIVEREJECTED),
	SNMP_MIB_ITEM("PAWSEstab", BEEP_MIB_PAWSESTABREJECTED),
	SNMP_MIB_ITEM("DelayedACKs", BEEP_MIB_DELAYEDACKS),
	SNMP_MIB_ITEM("DelayedACKLocked", BEEP_MIB_DELAYEDACKLOCKED),
	SNMP_MIB_ITEM("DelayedACKLost", BEEP_MIB_DELAYEDACKLOST),
	SNMP_MIB_ITEM("ListenOverflows", BEEP_MIB_LISTENOVERFLOWS),
	SNMP_MIB_ITEM("ListenDrops", BEEP_MIB_LISTENDROPS),
	SNMP_MIB_ITEM("TCPPrequeued", BEEP_MIB_TCPPREQUEUED),
	SNMP_MIB_ITEM("TCPDirectCopyFromBacklog", BEEP_MIB_TCPDIRECTCOPYFROMBACKLOG),
	SNMP_MIB_ITEM("TCPDirectCopyFromPrequeue", BEEP_MIB_TCPDIRECTCOPYFROMPREQUEUE),
	SNMP_MIB_ITEM("TCPPrequeueDropped", BEEP_MIB_TCPPREQUEUEDROPPED),
	SNMP_MIB_ITEM("TCPHPHits", BEEP_MIB_TCPHPHITS),
	SNMP_MIB_ITEM("TCPHPHitsToUser", BEEP_MIB_TCPHPHITSTOUSER),
	SNMP_MIB_ITEM("TCPPureAcks", BEEP_MIB_TCPPUREACKS),
	SNMP_MIB_ITEM("TCPHPAcks", BEEP_MIB_TCPHPACKS),
	SNMP_MIB_ITEM("TCPRenoRecovery", BEEP_MIB_TCPRENORECOVERY),
	SNMP_MIB_ITEM("TCPSackRecovery", BEEP_MIB_TCPSACKRECOVERY),
	SNMP_MIB_ITEM("TCPSACKReneging", BEEP_MIB_TCPSACKRENEGING),
	SNMP_MIB_ITEM("TCPFACKReorder", BEEP_MIB_TCPFACKREORDER),
	SNMP_MIB_ITEM("TCPSACKReorder", BEEP_MIB_TCPSACKREORDER),
	SNMP_MIB_ITEM("TCPRenoReorder", BEEP_MIB_TCPRENOREORDER),
	SNMP_MIB_ITEM("TCPTSReorder", BEEP_MIB_TCPTSREORDER),
	SNMP_MIB_ITEM("TCPFullUndo", BEEP_MIB_TCPFULLUNDO),
	SNMP_MIB_ITEM("TCPPartialUndo", BEEP_MIB_TCPPARTIALUNDO),
	SNMP_MIB_ITEM("TCPDSACKUndo", BEEP_MIB_TCPDSACKUNDO),
	SNMP_MIB_ITEM("TCPLossUndo", BEEP_MIB_TCPLOSSUNDO),
	SNMP_MIB_ITEM("TCPLostRetransmit", BEEP_MIB_TCPLOSTRETRANSMIT),
	SNMP_MIB_ITEM("TCPRenoFailures", BEEP_MIB_TCPRENOFAILURES),
	SNMP_MIB_ITEM("TCPSackFailures", BEEP_MIB_TCPSACKFAILURES),
	SNMP_MIB_ITEM("TCPLossFailures", BEEP_MIB_TCPLOSSFAILURES),
	SNMP_MIB_ITEM("TCPFastRetrans", BEEP_MIB_TCPFASTRETRANS),
	SNMP_MIB_ITEM("TCPForwardRetrans", BEEP_MIB_TCPFORWARDRETRANS),
	SNMP_MIB_ITEM("TCPSlowStartRetrans", BEEP_MIB_TCPSLOWSTARTRETRANS),
	SNMP_MIB_ITEM("TCPTimeouts", BEEP_MIB_TCPTIMEOUTS),
	SNMP_MIB_ITEM("TCPRenoRecoveryFail", BEEP_MIB_TCPRENORECOVERYFAIL),
	SNMP_MIB_ITEM("TCPSackRecoveryFail", BEEP_MIB_TCPSACKRECOVERYFAIL),
	SNMP_MIB_ITEM("TCPSchedulerFailed", BEEP_MIB_TCPSCHEDULERFAILED),
	SNMP_MIB_ITEM("TCPRcvCollapsed", BEEP_MIB_TCPRCVCOLLAPSED),
	SNMP_MIB_ITEM("TCPDSACKOldSent", BEEP_MIB_TCPDSACKOLDSENT),
	SNMP_MIB_ITEM("TCPDSACKOfoSent", BEEP_MIB_TCPDSACKOFOSENT),
	SNMP_MIB_ITEM("TCPDSACKRecv", BEEP_MIB_TCPDSACKRECV),
	SNMP_MIB_ITEM("TCPDSACKOfoRecv", BEEP_MIB_TCPDSACKOFORECV),
	SNMP_MIB_ITEM("TCPAbortOnData", BEEP_MIB_TCPABORTONDATA),
	SNMP_MIB_ITEM("TCPAbortOnClose", BEEP_MIB_TCPABORTONCLOSE),
	SNMP_MIB_ITEM("TCPAbortOnMemory", BEEP_MIB_TCPABORTONMEMORY),
	SNMP_MIB_ITEM("TCPAbortOnTimeout", BEEP_MIB_TCPABORTONTIMEOUT),
	SNMP_MIB_ITEM("TCPAbortOnLinger", BEEP_MIB_TCPABORTONLINGER),
	SNMP_MIB_ITEM("TCPAbortFailed", BEEP_MIB_TCPABORTFAILED),
	SNMP_MIB_ITEM("TCPMemoryPressures", BEEP_MIB_TCPMEMORYPRESSURES),
	SNMP_MIB_ITEM("TCPSACKDiscard", BEEP_MIB_TCPSACKDISCARD),
	SNMP_MIB_ITEM("TCPDSACKIgnoredOld", BEEP_MIB_TCPDSACKIGNOREDOLD),
	SNMP_MIB_ITEM("TCPDSACKIgnoredNoUndo", BEEP_MIB_TCPDSACKIGNOREDNOUNDO),
	SNMP_MIB_ITEM("TCPSpuriousRTOs", BEEP_MIB_TCPSPURIOUSRTOS),
	SNMP_MIB_ITEM("TCPMD5NotFound", BEEP_MIB_TCPMD5NOTFOUND),
	SNMP_MIB_ITEM("TCPMD5Unexpected", BEEP_MIB_TCPMD5UNEXPECTED),
	SNMP_MIB_ITEM("TCPSackShifted", BEEP_MIB_SACKSHIFTED),
	SNMP_MIB_ITEM("TCPSackMerged", BEEP_MIB_SACKMERGED),
	SNMP_MIB_ITEM("TCPSackShiftFallback", BEEP_MIB_SACKSHIFTFALLBACK),
	SNMP_MIB_ITEM("TCPBacklogDrop", BEEP_MIB_TCPBACKLOGDROP),
	SNMP_MIB_ITEM("TCPMinTTLDrop", BEEP_MIB_TCPMINTTLDROP),
	SNMP_MIB_ITEM("TCPDeferAcceptDrop", BEEP_MIB_TCPDEFERACCEPTDROP),
	SNMP_MIB_ITEM("IPReversePathFilter", BEEP_MIB_IPRPFILTER),
	SNMP_MIB_ITEM("TCPTimeWaitOverflow", BEEP_MIB_TCPTIMEWAITOVERFLOW),
	SNMP_MIB_ITEM("TCPReqQFullDoCookies", BEEP_MIB_TCPREQQFULLDOCOOKIES),
	SNMP_MIB_ITEM("TCPReqQFullDrop", BEEP_MIB_TCPREQQFULLDROP),
	SNMP_MIB_ITEM("TCPRetransFail", BEEP_MIB_TCPRETRANSFAIL),
	SNMP_MIB_ITEM("TCPRcvCoalesce", BEEP_MIB_TCPRCVCOALESCE),
	SNMP_MIB_ITEM("TCPOFOQueue", BEEP_MIB_TCPOFOQUEUE),
	SNMP_MIB_ITEM("TCPOFODrop", BEEP_MIB_TCPOFODROP),
	SNMP_MIB_ITEM("TCPOFOMerge", BEEP_MIB_TCPOFOMERGE),
	SNMP_MIB_ITEM("TCPChallengeACK", BEEP_MIB_TCPCHALLENGEACK),
	SNMP_MIB_ITEM("TCPSYNChallenge", BEEP_MIB_TCPSYNCHALLENGE),
	SNMP_MIB_ITEM("TCPFastOpenActive", BEEP_MIB_TCPFASTOPENACTIVE),
	SNMP_MIB_ITEM("TCPFastOpenPassive", BEEP_MIB_TCPFASTOPENPASSIVE),
	SNMP_MIB_ITEM("TCPFastOpenPassiveFail", BEEP_MIB_TCPFASTOPENPASSIVEFAIL),
	SNMP_MIB_ITEM("TCPFastOpenListenOverflow", BEEP_MIB_TCPFASTOPENLISTENOVERFLOW),
	SNMP_MIB_ITEM("TCPFastOpenCookieReqd", BEEP_MIB_TCPFASTOPENCOOKIEREQD),
	SNMP_MIB_SENTINEL
};

static void icmpmsg_put_line(struct seq_file *seq, unsigned long *vals,
			     unsigned short *type, int count)
{
	int j;

	if (count) {
		seq_printf(seq, "\nIcmpMsg:");
		for (j = 0; j < count; ++j)
			seq_printf(seq, " %sType%u",
				type[j] & 0x100 ? "Out" : "In",
				type[j] & 0xff);
		seq_printf(seq, "\nIcmpMsg:");
		for (j = 0; j < count; ++j)
			seq_printf(seq, " %lu", vals[j]);
	}
}

static void icmpmsg_put(struct seq_file *seq)
{
#define PERLINE	16

	int i, count;
	unsigned short type[PERLINE];
	unsigned long vals[PERLINE], val;
	struct net *net = seq->private;

	count = 0;
	for (i = 0; i < ICMPMSG_MIB_MAX; i++) {
		val = atomic_long_read(&net->mib.icmpmsg_statistics->mibs[i]);
		if (val) {
			type[count] = i;
			vals[count++] = val;
		}
		if (count == PERLINE) {
			icmpmsg_put_line(seq, vals, type, count);
			count = 0;
		}
	}
	icmpmsg_put_line(seq, vals, type, count);

#undef PERLINE
}

static void icmp_put(struct seq_file *seq)
{
	int i;
	struct net *net = seq->private;
	atomic_long_t *ptr = net->mib.icmpmsg_statistics->mibs;

	seq_puts(seq, "\nIcmp: InMsgs InErrors");
	for (i=0; icmpmibmap[i].name != NULL; i++)
		seq_printf(seq, " In%s", icmpmibmap[i].name);
	seq_printf(seq, " OutMsgs OutErrors");
	for (i=0; icmpmibmap[i].name != NULL; i++)
		seq_printf(seq, " Out%s", icmpmibmap[i].name);
	seq_printf(seq, "\nIcmp: %lu %lu",
		snmp_fold_field((void __percpu **) net->mib.icmp_statistics, ICMP_MIB_INMSGS),
		snmp_fold_field((void __percpu **) net->mib.icmp_statistics, ICMP_MIB_INERRORS));
	for (i=0; icmpmibmap[i].name != NULL; i++)
		seq_printf(seq, " %lu",
			   atomic_long_read(ptr + icmpmibmap[i].index));
	seq_printf(seq, " %lu %lu",
		snmp_fold_field((void __percpu **) net->mib.icmp_statistics, ICMP_MIB_OUTMSGS),
		snmp_fold_field((void __percpu **) net->mib.icmp_statistics, ICMP_MIB_OUTERRORS));
	for (i=0; icmpmibmap[i].name != NULL; i++)
		seq_printf(seq, " %lu",
			   atomic_long_read(ptr + (icmpmibmap[i].index | 0x100)));
}

/*
 *	Called from the PROCfs module. This outputs /proc/net/snmp.
 */
static int snmp_seq_show(struct seq_file *seq, void *v)
{
	int i;
	struct net *net = seq->private;

	seq_puts(seq, "Ip: Forwarding DefaultTTL");

	for (i = 0; snmp4_ipstats_list[i].name != NULL; i++)
		seq_printf(seq, " %s", snmp4_ipstats_list[i].name);

	seq_printf(seq, "\nIp: %d %d",
		   IPV4_DEVCONF_ALL(net, FORWARDING) ? 1 : 2,
		   sysctl_ip_default_ttl);

	BUILD_BUG_ON(offsetof(struct ipstats_mib, mibs) != 0);
	for (i = 0; snmp4_ipstats_list[i].name != NULL; i++)
		seq_printf(seq, " %llu",
			   snmp_fold_field64((void __percpu **)net->mib.ip_statistics,
					     snmp4_ipstats_list[i].entry,
					     offsetof(struct ipstats_mib, syncp)));

	icmp_put(seq);	/* RFC 2011 compatibility */
	icmpmsg_put(seq);

	seq_puts(seq, "\nTcp:");
	for (i = 0; snmp4_tcp_list[i].name != NULL; i++)
		seq_printf(seq, " %s", snmp4_tcp_list[i].name);

	seq_puts(seq, "\nTcp:");
	for (i = 0; snmp4_tcp_list[i].name != NULL; i++) {
		/* MaxConn field is signed, RFC 2012 */
		if (snmp4_tcp_list[i].entry == TCP_MIB_MAXCONN)
			seq_printf(seq, " %ld",
				   snmp_fold_field((void __percpu **)net->mib.tcp_statistics,
						   snmp4_tcp_list[i].entry));
		else
			seq_printf(seq, " %lu",
				   snmp_fold_field((void __percpu **)net->mib.tcp_statistics,
						   snmp4_tcp_list[i].entry));
	}

	seq_puts(seq, "\nUdp:");
	for (i = 0; snmp4_udp_list[i].name != NULL; i++)
		seq_printf(seq, " %s", snmp4_udp_list[i].name);

	seq_puts(seq, "\nUdp:");
	for (i = 0; snmp4_udp_list[i].name != NULL; i++)
		seq_printf(seq, " %lu",
			   snmp_fold_field((void __percpu **)net->mib.udp_statistics,
					   snmp4_udp_list[i].entry));

	/* the UDP and UDP-Lite MIBs are the same */
	seq_puts(seq, "\nUdpLite:");
	for (i = 0; snmp4_udp_list[i].name != NULL; i++)
		seq_printf(seq, " %s", snmp4_udp_list[i].name);

	seq_puts(seq, "\nUdpLite:");
	for (i = 0; snmp4_udp_list[i].name != NULL; i++)
		seq_printf(seq, " %lu",
			   snmp_fold_field((void __percpu **)net->mib.udplite_statistics,
					   snmp4_udp_list[i].entry));

	seq_putc(seq, '\n');
	return 0;
}

static int snmp_seq_open(struct inode *inode, struct file *file)
{
	return single_open_net(inode, file, snmp_seq_show);
}

static const struct file_operations snmp_seq_fops = {
	.owner	 = THIS_MODULE,
	.open	 = snmp_seq_open,
	.read	 = seq_read,
	.llseek	 = seq_lseek,
	.release = single_release_net,
};



/*
 *	Output /proc/net/netstat
 */
static int netstat_seq_show(struct seq_file *seq, void *v)
{
	int i;
	struct net *net = seq->private;

	seq_puts(seq, "TcpExt:");
	for (i = 0; snmp4_net_list[i].name != NULL; i++)
		seq_printf(seq, " %s", snmp4_net_list[i].name);

	seq_puts(seq, "\nTcpExt:");
	for (i = 0; snmp4_net_list[i].name != NULL; i++)
		seq_printf(seq, " %lu",
			   snmp_fold_field((void __percpu **)net->mib.net_statistics,
					   snmp4_net_list[i].entry));

	seq_puts(seq, "\nIpExt:");
	for (i = 0; snmp4_ipextstats_list[i].name != NULL; i++)
		seq_printf(seq, " %s", snmp4_ipextstats_list[i].name);

	seq_puts(seq, "\nIpExt:");
	for (i = 0; snmp4_ipextstats_list[i].name != NULL; i++)
		seq_printf(seq, " %llu",
			   snmp_fold_field64((void __percpu **)net->mib.ip_statistics,
					     snmp4_ipextstats_list[i].entry,
					     offsetof(struct ipstats_mib, syncp)));

	seq_putc(seq, '\n');
	return 0;
}

static int netstat_seq_open(struct inode *inode, struct file *file)
{
	return single_open_net(inode, file, netstat_seq_show);
}

static const struct file_operations netstat_seq_fops = {
	.owner	 = THIS_MODULE,
	.open	 = netstat_seq_open,
	.read	 = seq_read,
	.llseek	 = seq_lseek,
	.release = single_release_net,
};

static __net_init int ip_proc_init_net(struct net *net)
{
	if (!proc_net_fops_create(net, "sockstat", S_IRUGO, &sockstat_seq_fops))
		goto out_sockstat;
	if (!proc_net_fops_create(net, "netstat", S_IRUGO, &netstat_seq_fops))
		goto out_netstat;
	if (!proc_net_fops_create(net, "snmp", S_IRUGO, &snmp_seq_fops))
		goto out_snmp;

	return 0;

out_snmp:
	proc_net_remove(net, "netstat");
out_netstat:
	proc_net_remove(net, "sockstat");
out_sockstat:
	return -ENOMEM;
}

static __net_exit void ip_proc_exit_net(struct net *net)
{
	proc_net_remove(net, "snmp");
	proc_net_remove(net, "netstat");
	proc_net_remove(net, "sockstat");
}

static __net_initdata struct pernet_operations ip_proc_ops = {
	.init = ip_proc_init_net,
	.exit = ip_proc_exit_net,
};

int __init ip_misc_proc_init(void)
{
	return register_pernet_subsys(&ip_proc_ops);
}

