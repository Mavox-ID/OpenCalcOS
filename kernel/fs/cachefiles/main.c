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
#include <beep/init.h>
#include <beep/sched.h>
#include <beep/completion.h>
#include <beep/slab.h>
#include <beep/fs.h>
#include <beep/file.h>
#include <beep/namei.h>
#include <beep/mount.h>
#include <beep/statfs.h>
#include <beep/sysctl.h>
#include <beep/miscdevice.h>
#include "internal.h"

unsigned cachefiles_debug;
module_param_named(debug, cachefiles_debug, uint, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(cachefiles_debug, "CacheFiles debugging mask");

MODULE_DESCRIPTION("Mounted-filesystem based cache");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

struct kmem_cache *cachefiles_object_jar;

static struct miscdevice cachefiles_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "cachefiles",
	.fops	= &cachefiles_daemon_fops,
};

static void cachefiles_object_init_once(void *_object)
{
	struct cachefiles_object *object = _object;

	memset(object, 0, sizeof(*object));
	spin_lock_init(&object->work_lock);
}

/*
 * initialise the fs caching module
 */
static int __init cachefiles_init(void)
{
	int ret;

	ret = misc_register(&cachefiles_dev);
	if (ret < 0)
		goto error_dev;

	/* create an object jar */
	ret = -ENOMEM;
	cachefiles_object_jar =
		kmem_cache_create("cachefiles_object_jar",
				  sizeof(struct cachefiles_object),
				  0,
				  SLAB_HWCACHE_ALIGN,
				  cachefiles_object_init_once);
	if (!cachefiles_object_jar) {
		printk(KERN_NOTICE
		       "CacheFiles: Failed to allocate an object jar\n");
		goto error_object_jar;
	}

	ret = cachefiles_proc_init();
	if (ret < 0)
		goto error_proc;

	printk(KERN_INFO "CacheFiles: Loaded\n");
	return 0;

error_proc:
	kmem_cache_destroy(cachefiles_object_jar);
error_object_jar:
	misc_deregister(&cachefiles_dev);
error_dev:
	kerror("failed to register: %d", ret);
	return ret;
}

fs_initcall(cachefiles_init);

/*
 * clean up on module removal
 */
static void __exit cachefiles_exit(void)
{
	printk(KERN_INFO "CacheFiles: Unloading\n");

	cachefiles_proc_cleanup();
	kmem_cache_destroy(cachefiles_object_jar);
	misc_deregister(&cachefiles_dev);
}

module_exit(cachefiles_exit);
