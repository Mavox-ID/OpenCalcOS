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
#ifndef _CRYPTO_IF_ALG_H
#define _CRYPTO_IF_ALG_H

#include <beep/compiler.h>
#include <beep/completion.h>
#include <beep/if_alg.h>
#include <beep/scatterlist.h>
#include <beep/types.h>
#include <net/sock.h>

#define ALG_MAX_PAGES			16

struct crypto_async_request;

struct alg_sock {
	/* struct sock must be the first member of struct alg_sock */
	struct sock sk;

	struct sock *parent;

	const struct af_alg_type *type;
	void *private;
};

struct af_alg_completion {
	struct completion completion;
	int err;
};

struct af_alg_control {
	struct af_alg_iv *iv;
	int op;
};

struct af_alg_type {
	void *(*bind)(const char *name, u32 type, u32 mask);
	void (*release)(void *private);
	int (*setkey)(void *private, const u8 *key, unsigned int keylen);
	int (*accept)(void *private, struct sock *sk);

	struct proto_ops *ops;
	struct module *owner;
	char name[14];
};

struct af_alg_sgl {
	struct scatterlist sg[ALG_MAX_PAGES];
	struct page *pages[ALG_MAX_PAGES];
};

int af_alg_register_type(const struct af_alg_type *type);
int af_alg_unregister_type(const struct af_alg_type *type);

int af_alg_release(struct socket *sock);
int af_alg_accept(struct sock *sk, struct socket *newsock);

int af_alg_make_sg(struct af_alg_sgl *sgl, void __user *addr, int len,
		   int write);
void af_alg_free_sg(struct af_alg_sgl *sgl);

int af_alg_cmsg_send(struct msghdr *msg, struct af_alg_control *con);

int af_alg_wait_for_completion(int err, struct af_alg_completion *completion);
void af_alg_complete(struct crypto_async_request *req, int err);

static inline struct alg_sock *alg_sk(struct sock *sk)
{
	return (struct alg_sock *)sk;
}

static inline void af_alg_release_parent(struct sock *sk)
{
	sock_put(alg_sk(sk)->parent);
}

static inline void af_alg_init_completion(struct af_alg_completion *completion)
{
	init_completion(&completion->completion);
}

#endif	/* _CRYPTO_IF_ALG_H */
