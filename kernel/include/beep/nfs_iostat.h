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
#ifndef _BEEP_NFS_IOSTAT
#define _BEEP_NFS_IOSTAT

#define NFS_IOSTAT_VERS		"1.1"

/*
 * NFS byte counters
 *
 * 1.  SERVER - the number of payload bytes read from or written
 *     to the server by the NFS client via an NFS READ or WRITE
 *     request.
 *
 * 2.  NORMAL - the number of bytes read or written by applications
 *     via the read(2) and write(2) system call interfaces.
 *
 * 3.  DIRECT - the number of bytes read or written from files
 *     opened with the O_DIRECT flag.
 *
 * These counters give a view of the data throughput into and out
 * of the NFS client.  Comparing the number of bytes requested by
 * an application with the number of bytes the client requests from
 * the server can provide an indication of client efficiency
 * (per-op, cache hits, etc).
 *
 * These counters can also help characterize which access methods
 * are in use.  DIRECT by itself shows whether there is any O_DIRECT
 * traffic.  NORMAL + DIRECT shows how much data is going through
 * the system call interface.  A large amount of SERVER traffic
 * without much NORMAL or DIRECT traffic shows that applications
 * are using mapped files.
 *
 * NFS page counters
 *
 * These count the number of pages read or written via nfs_readpage(),
 * nfs_readpages(), or their write equivalents.
 *
 * NB: When adding new byte counters, please include the measured
 * units in the name of each byte counter to help users of this
 * interface determine what exactly is being counted.
 */
enum nfs_stat_bytecounters {
	NFSIOS_NORMALREADBYTES = 0,
	NFSIOS_NORMALWRITTENBYTES,
	NFSIOS_DIRECTREADBYTES,
	NFSIOS_DIRECTWRITTENBYTES,
	NFSIOS_SERVERREADBYTES,
	NFSIOS_SERVERWRITTENBYTES,
	NFSIOS_READPAGES,
	NFSIOS_WRITEPAGES,
	__NFSIOS_BYTESMAX,
};

/*
 * NFS event counters
 *
 * These counters provide a low-overhead way of monitoring client
 * activity without enabling NFS trace debugging.  The counters
 * show the rate at which VFS requests are made, and how often the
 * client invalidates its data and attribute caches.  This allows
 * system administrators to monitor such things as how close-to-open
 * is working, and answer questions such as "why are there so many
 * GETATTR requests on the wire?"
 *
 * They also count anamolous events such as short reads and writes,
 * silly renames due to close-after-delete, and operations that
 * change the size of a file (such operations can often be the
 * source of data corruption if applications aren't using file
 * locking properly).
 */
enum nfs_stat_eventcounters {
	NFSIOS_INODEREVALIDATE = 0,
	NFSIOS_DENTRYREVALIDATE,
	NFSIOS_DATAINVALIDATE,
	NFSIOS_ATTRINVALIDATE,
	NFSIOS_VFSOPEN,
	NFSIOS_VFSLOOKUP,
	NFSIOS_VFSACCESS,
	NFSIOS_VFSUPDATEPAGE,
	NFSIOS_VFSREADPAGE,
	NFSIOS_VFSREADPAGES,
	NFSIOS_VFSWRITEPAGE,
	NFSIOS_VFSWRITEPAGES,
	NFSIOS_VFSGETDENTS,
	NFSIOS_VFSSETATTR,
	NFSIOS_VFSFLUSH,
	NFSIOS_VFSFSYNC,
	NFSIOS_VFSLOCK,
	NFSIOS_VFSRELEASE,
	NFSIOS_CONGESTIONWAIT,
	NFSIOS_SETATTRTRUNC,
	NFSIOS_EXTENDWRITE,
	NFSIOS_SILLYRENAME,
	NFSIOS_SHORTREAD,
	NFSIOS_SHORTWRITE,
	NFSIOS_DELAY,
	NFSIOS_PNFS_READ,
	NFSIOS_PNFS_WRITE,
	__NFSIOS_COUNTSMAX,
};

/*
 * NFS local caching servicing counters
 */
enum nfs_stat_fscachecounters {
	NFSIOS_FSCACHE_PAGES_READ_OK,
	NFSIOS_FSCACHE_PAGES_READ_FAIL,
	NFSIOS_FSCACHE_PAGES_WRITTEN_OK,
	NFSIOS_FSCACHE_PAGES_WRITTEN_FAIL,
	NFSIOS_FSCACHE_PAGES_UNCACHED,
	__NFSIOS_FSCACHEMAX,
};

#endif	/* _BEEP_NFS_IOSTAT */
