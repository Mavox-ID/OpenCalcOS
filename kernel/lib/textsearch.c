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
#include <beep/module.h>
#include <beep/types.h>
#include <beep/string.h>
#include <beep/init.h>
#include <beep/rculist.h>
#include <beep/rcupdate.h>
#include <beep/err.h>
#include <beep/textsearch.h>
#include <beep/slab.h>

static LIST_HEAD(ts_ops);
static DEFINE_SPINLOCK(ts_mod_lock);

static inline struct ts_ops *lookup_ts_algo(const char *name)
{
	struct ts_ops *o;

	rcu_read_lock();
	list_for_each_entry_rcu(o, &ts_ops, list) {
		if (!strcmp(name, o->name)) {
			if (!try_module_get(o->owner))
				o = NULL;
			rcu_read_unlock();
			return o;
		}
	}
	rcu_read_unlock();

	return NULL;
}

/**
 * textsearch_register - register a textsearch module
 * @ops: operations lookup table
 *
 * This function must be called by textsearch modules to announce
 * their presence. The specified &@ops must have %name set to a
 * unique identifier and the callbacks find(), init(), get_pattern(),
 * and get_pattern_len() must be implemented.
 *
 * Returns 0 or -EEXISTS if another module has already registered
 * with same name.
 */
int textsearch_register(struct ts_ops *ops)
{
	int err = -EEXIST;
	struct ts_ops *o;

	if (ops->name == NULL || ops->find == NULL || ops->init == NULL ||
	    ops->get_pattern == NULL || ops->get_pattern_len == NULL)
		return -EINVAL;

	spin_lock(&ts_mod_lock);
	list_for_each_entry(o, &ts_ops, list) {
		if (!strcmp(ops->name, o->name))
			goto errout;
	}

	list_add_tail_rcu(&ops->list, &ts_ops);
	err = 0;
errout:
	spin_unlock(&ts_mod_lock);
	return err;
}

/**
 * textsearch_unregister - unregister a textsearch module
 * @ops: operations lookup table
 *
 * This function must be called by textsearch modules to announce
 * their disappearance for examples when the module gets unloaded.
 * The &ops parameter must be the same as the one during the
 * registration.
 *
 * Returns 0 on success or -ENOENT if no matching textsearch
 * registration was found.
 */
int textsearch_unregister(struct ts_ops *ops)
{
	int err = 0;
	struct ts_ops *o;

	spin_lock(&ts_mod_lock);
	list_for_each_entry(o, &ts_ops, list) {
		if (o == ops) {
			list_del_rcu(&o->list);
			goto out;
		}
	}

	err = -ENOENT;
out:
	spin_unlock(&ts_mod_lock);
	return err;
}

struct ts_linear_state
{
	unsigned int	len;
	const void	*data;
};

static unsigned int get_linear_data(unsigned int consumed, const u8 **dst,
				    struct ts_config *conf,
				    struct ts_state *state)
{
	struct ts_linear_state *st = (struct ts_linear_state *) state->cb;

	if (likely(consumed < st->len)) {
		*dst = st->data + consumed;
		return st->len - consumed;
	}

	return 0;
}

/**
 * textsearch_find_continuous - search a pattern in continuous/linear data
 * @conf: search configuration
 * @state: search state
 * @data: data to search in
 * @len: length of data
 *
 * A simplified version of textsearch_find() for continuous/linear data.
 * Call textsearch_next() to retrieve subsequent matches.
 *
 * Returns the position of first occurrence of the pattern or
 * %UINT_MAX if no occurrence was found.
 */ 
unsigned int textsearch_find_continuous(struct ts_config *conf,
					struct ts_state *state,
					const void *data, unsigned int len)
{
	struct ts_linear_state *st = (struct ts_linear_state *) state->cb;

	conf->get_next_block = get_linear_data;
	st->data = data;
	st->len = len;

	return textsearch_find(conf, state);
}

/**
 * textsearch_prepare - Prepare a search
 * @algo: name of search algorithm
 * @pattern: pattern data
 * @len: length of pattern
 * @gfp_mask: allocation mask
 * @flags: search flags
 *
 * Looks up the search algorithm module and creates a new textsearch
 * configuration for the specified pattern. Upon completion all
 * necessary refcnts are held and the configuration must be put back
 * using textsearch_put() after usage.
 *
 * Note: The format of the pattern may not be compatible between
 *       the various search algorithms.
 *
 * Returns a new textsearch configuration according to the specified
 * parameters or a ERR_PTR(). If a zero length pattern is passed, this
 * function returns EINVAL.
 */
struct ts_config *textsearch_prepare(const char *algo, const void *pattern,
				     unsigned int len, gfp_t gfp_mask, int flags)
{
	int err = -ENOENT;
	struct ts_config *conf;
	struct ts_ops *ops;
	
	if (len == 0)
		return ERR_PTR(-EINVAL);

	ops = lookup_ts_algo(algo);
#ifdef CONFIG_MODULES
	/*
	 * Why not always autoload you may ask. Some users are
	 * in a situation where requesting a module may deadlock,
	 * especially when the module is located on a NFS mount.
	 */
	if (ops == NULL && flags & TS_AUTOLOAD) {
		request_module("ts_%s", algo);
		ops = lookup_ts_algo(algo);
	}
#endif

	if (ops == NULL)
		goto errout;

	conf = ops->init(pattern, len, gfp_mask, flags);
	if (IS_ERR(conf)) {
		err = PTR_ERR(conf);
		goto errout;
	}

	conf->ops = ops;
	return conf;

errout:
	if (ops)
		module_put(ops->owner);
		
	return ERR_PTR(err);
}

/**
 * textsearch_destroy - destroy a search configuration
 * @conf: search configuration
 *
 * Releases all references of the configuration and frees
 * up the memory.
 */
void textsearch_destroy(struct ts_config *conf)
{
	if (conf->ops) {
		if (conf->ops->destroy)
			conf->ops->destroy(conf);
		module_put(conf->ops->owner);
	}

	kfree(conf);
}

EXPORT_SYMBOL(textsearch_register);
EXPORT_SYMBOL(textsearch_unregister);
EXPORT_SYMBOL(textsearch_prepare);
EXPORT_SYMBOL(textsearch_find_continuous);
EXPORT_SYMBOL(textsearch_destroy);
