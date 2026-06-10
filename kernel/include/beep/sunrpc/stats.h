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
#ifndef _BEEP_SUNRPC_STATS_H
#define _BEEP_SUNRPC_STATS_H

#include <beep/proc_fs.h>

struct rpc_stat {
	const struct rpc_program *program;

	unsigned int		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn,
				netreconn;
	unsigned int		rpccnt,
				rpcretrans,
				rpcauthrefresh,
				rpcgarbage;
};

struct svc_stat {
	struct svc_program *	program;

	unsigned int		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn;
	unsigned int		rpccnt,
				rpcbadfmt,
				rpcbadauth,
				rpcbadclnt;
};

struct net;
#ifdef CONFIG_PROC_FS
int			rpc_proc_init(struct net *);
void			rpc_proc_exit(struct net *);
#else
static inline int rpc_proc_init(struct net *net)
{
	return 0;
}

static inline void rpc_proc_exit(struct net *net)
{
}
#endif

#ifdef MODULE
void			rpc_modcount(struct inode *, int);
#endif

#ifdef CONFIG_PROC_FS
struct proc_dir_entry *	rpc_proc_register(struct net *,struct rpc_stat *);
void			rpc_proc_unregister(struct net *,const char *);
void			rpc_proc_zero(const struct rpc_program *);
struct proc_dir_entry *	svc_proc_register(struct net *, struct svc_stat *,
					  const struct file_operations *);
void			svc_proc_unregister(struct net *, const char *);

void			svc_seq_show(struct seq_file *,
				     const struct svc_stat *);
#else

static inline struct proc_dir_entry *rpc_proc_register(struct net *net, struct rpc_stat *s) { return NULL; }
static inline void rpc_proc_unregister(struct net *net, const char *p) {}
static inline void rpc_proc_zero(const struct rpc_program *p) {}

static inline struct proc_dir_entry *svc_proc_register(struct net *net, struct svc_stat *s,
						       const struct file_operations *f) { return NULL; }
static inline void svc_proc_unregister(struct net *net, const char *p) {}

static inline void svc_seq_show(struct seq_file *seq,
				const struct svc_stat *st) {}
#endif

#endif /* _BEEP_SUNRPC_STATS_H */
