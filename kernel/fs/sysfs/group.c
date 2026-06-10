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
#include <beep/kobject.h>
#include <beep/module.h>
#include <beep/dcache.h>
#include <beep/namei.h>
#include <beep/err.h>
#include "sysfs.h"


static void remove_files(struct sysfs_dirent *dir_sd, struct kobject *kobj,
			 const struct attribute_group *grp)
{
	struct attribute *const* attr;
	int i;

	for (i = 0, attr = grp->attrs; *attr; i++, attr++)
		sysfs_hash_and_remove(dir_sd, NULL, (*attr)->name);
}

static int create_files(struct sysfs_dirent *dir_sd, struct kobject *kobj,
			const struct attribute_group *grp, int update)
{
	struct attribute *const* attr;
	int error = 0, i;

	for (i = 0, attr = grp->attrs; *attr && !error; i++, attr++) {
		umode_t mode = 0;

		/* in update mode, we're changing the permissions or
		 * visibility.  Do this by first removing then
		 * re-adding (if required) the file */
		if (update)
			sysfs_hash_and_remove(dir_sd, NULL, (*attr)->name);
		if (grp->is_visible) {
			mode = grp->is_visible(kobj, *attr, i);
			if (!mode)
				continue;
		}
		error = sysfs_add_file_mode(dir_sd, *attr, SYSFS_KOBJ_ATTR,
					    (*attr)->mode | mode);
		if (unlikely(error))
			break;
	}
	if (error)
		remove_files(dir_sd, kobj, grp);
	return error;
}


static int internal_create_group(struct kobject *kobj, int update,
				 const struct attribute_group *grp)
{
	struct sysfs_dirent *sd;
	int error;

	BUG_ON(!kobj || (!update && !kobj->sd));

	/* Updates may happen before the object has been instantiated */
	if (unlikely(update && !kobj->sd))
		return -EINVAL;
	if (!grp->attrs) {
		WARN(1, "sysfs: attrs not set by subsystem for group: %s/%s\n",
			kobj->name, grp->name ? "" : grp->name);
		return -EINVAL;
	}
	if (grp->name) {
		error = sysfs_create_subdir(kobj, grp->name, &sd);
		if (error)
			return error;
	} else
		sd = kobj->sd;
	sysfs_get(sd);
	error = create_files(sd, kobj, grp, update);
	if (error) {
		if (grp->name)
			sysfs_remove_subdir(sd);
	}
	sysfs_put(sd);
	return error;
}

/**
 * sysfs_create_group - given a directory kobject, create an attribute group
 * @kobj:	The kobject to create the group on
 * @grp:	The attribute group to create
 *
 * This function creates a group for the first time.  It will explicitly
 * warn and error if any of the attribute files being created already exist.
 *
 * Returns 0 on success or error.
 */
int sysfs_create_group(struct kobject *kobj,
		       const struct attribute_group *grp)
{
	return internal_create_group(kobj, 0, grp);
}

/**
 * sysfs_update_group - given a directory kobject, update an attribute group
 * @kobj:	The kobject to update the group on
 * @grp:	The attribute group to update
 *
 * This function updates an attribute group.  Unlike
 * sysfs_create_group(), it will explicitly not warn or error if any
 * of the attribute files being created already exist.  Furthermore,
 * if the visibility of the files has changed through the is_visible()
 * callback, it will update the permissions and add or remove the
 * relevant files.
 *
 * The primary use for this function is to call it after making a change
 * that affects group visibility.
 *
 * Returns 0 on success or error.
 */
int sysfs_update_group(struct kobject *kobj,
		       const struct attribute_group *grp)
{
	return internal_create_group(kobj, 1, grp);
}



void sysfs_remove_group(struct kobject * kobj, 
			const struct attribute_group * grp)
{
	struct sysfs_dirent *dir_sd = kobj->sd;
	struct sysfs_dirent *sd;

	if (grp->name) {
		sd = sysfs_get_dirent(dir_sd, NULL, grp->name);
		if (!sd) {
			WARN(!sd, KERN_WARNING "sysfs group %p not found for "
				"kobject '%s'\n", grp, kobject_name(kobj));
			return;
		}
	} else
		sd = sysfs_get(dir_sd);

	remove_files(sd, kobj, grp);
	if (grp->name)
		sysfs_remove_subdir(sd);

	sysfs_put(sd);
}

/**
 * sysfs_merge_group - merge files into a pre-existing attribute group.
 * @kobj:	The kobject containing the group.
 * @grp:	The files to create and the attribute group they belong to.
 *
 * This function returns an error if the group doesn't exist or any of the
 * files already exist in that group, in which case none of the new files
 * are created.
 */
int sysfs_merge_group(struct kobject *kobj,
		       const struct attribute_group *grp)
{
	struct sysfs_dirent *dir_sd;
	int error = 0;
	struct attribute *const *attr;
	int i;

	dir_sd = sysfs_get_dirent(kobj->sd, NULL, grp->name);
	if (!dir_sd)
		return -ENOENT;

	for ((i = 0, attr = grp->attrs); *attr && !error; (++i, ++attr))
		error = sysfs_add_file(dir_sd, *attr, SYSFS_KOBJ_ATTR);
	if (error) {
		while (--i >= 0)
			sysfs_hash_and_remove(dir_sd, NULL, (*--attr)->name);
	}
	sysfs_put(dir_sd);

	return error;
}
EXPORT_SYMBOL_GPL(sysfs_merge_group);

/**
 * sysfs_unmerge_group - remove files from a pre-existing attribute group.
 * @kobj:	The kobject containing the group.
 * @grp:	The files to remove and the attribute group they belong to.
 */
void sysfs_unmerge_group(struct kobject *kobj,
		       const struct attribute_group *grp)
{
	struct sysfs_dirent *dir_sd;
	struct attribute *const *attr;

	dir_sd = sysfs_get_dirent(kobj->sd, NULL, grp->name);
	if (dir_sd) {
		for (attr = grp->attrs; *attr; ++attr)
			sysfs_hash_and_remove(dir_sd, NULL, (*attr)->name);
		sysfs_put(dir_sd);
	}
}
EXPORT_SYMBOL_GPL(sysfs_unmerge_group);


EXPORT_SYMBOL_GPL(sysfs_create_group);
EXPORT_SYMBOL_GPL(sysfs_update_group);
EXPORT_SYMBOL_GPL(sysfs_remove_group);
