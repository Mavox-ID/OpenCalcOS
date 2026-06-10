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
#include <beep/transport_class.h>

struct raid_template {
	struct transport_container raid_attrs;
};

struct raid_function_template {
	void *cookie;
	int (*is_raid)(struct device *);
	void (*get_resync)(struct device *);
	void (*get_state)(struct device *);
};

enum raid_state {
	RAID_STATE_UNKNOWN = 0,
	RAID_STATE_ACTIVE,
	RAID_STATE_DEGRADED,
	RAID_STATE_RESYNCING,
	RAID_STATE_OFFLINE,
};

enum raid_level {
	RAID_LEVEL_UNKNOWN = 0,
	RAID_LEVEL_LINEAR,
	RAID_LEVEL_0,
	RAID_LEVEL_1,
	RAID_LEVEL_10,
	RAID_LEVEL_1E,
	RAID_LEVEL_3,
	RAID_LEVEL_4,
	RAID_LEVEL_5,
	RAID_LEVEL_50,
	RAID_LEVEL_6,
};

struct raid_data {
	struct list_head component_list;
	int component_count;
	enum raid_level level;
	enum raid_state state;
	int resync;
};

/* resync complete goes from 0 to this */
#define RAID_MAX_RESYNC		(10000)

#define DEFINE_RAID_ATTRIBUTE(type, attr)				      \
static inline void							      \
raid_set_##attr(struct raid_template *r, struct device *dev, type value) {    \
	struct device *device =						      \
		attribute_container_find_class_device(&r->raid_attrs.ac, dev);\
	struct raid_data *rd;						      \
	BUG_ON(!device);						      \
	rd = dev_get_drvdata(device);					      \
	rd->attr = value;						      \
}									      \
static inline type							      \
raid_get_##attr(struct raid_template *r, struct device *dev) {		      \
	struct device *device =						      \
		attribute_container_find_class_device(&r->raid_attrs.ac, dev);\
	struct raid_data *rd;						      \
	BUG_ON(!device);						      \
	rd = dev_get_drvdata(device);					      \
	return rd->attr;						      \
}

DEFINE_RAID_ATTRIBUTE(enum raid_level, level)
DEFINE_RAID_ATTRIBUTE(int, resync)
DEFINE_RAID_ATTRIBUTE(enum raid_state, state)
	
struct raid_template *raid_class_attach(struct raid_function_template *);
void raid_class_release(struct raid_template *);

int __must_check raid_component_add(struct raid_template *, struct device *,
				    struct device *);

