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
#ifndef _TRANSPORT_CLASS_H_
#define _TRANSPORT_CLASS_H_

#include <beep/device.h>
#include <beep/bug.h>
#include <beep/attribute_container.h>

struct transport_container;

struct transport_class {
	struct class class;
	int (*setup)(struct transport_container *, struct device *,
		     struct device *);
	int (*configure)(struct transport_container *, struct device *,
			 struct device *);
	int (*remove)(struct transport_container *, struct device *,
		      struct device *);
};

#define DECLARE_TRANSPORT_CLASS(cls, nm, su, rm, cfg)			\
struct transport_class cls = {						\
	.class = {							\
		.name = nm,						\
	},								\
	.setup = su,							\
	.remove = rm,							\
	.configure = cfg,						\
}


struct anon_transport_class {
	struct transport_class tclass;
	struct attribute_container container;
};

#define DECLARE_ANON_TRANSPORT_CLASS(cls, mtch, cfg)		\
struct anon_transport_class cls = {				\
	.tclass = {						\
		.configure = cfg,				\
	},							\
	. container = {						\
		.match = mtch,					\
	},							\
}

#define class_to_transport_class(x) \
	container_of(x, struct transport_class, class)

struct transport_container {
	struct attribute_container ac;
	const struct attribute_group *statistics;
};

#define attribute_container_to_transport_container(x) \
	container_of(x, struct transport_container, ac)

void transport_remove_device(struct device *);
void transport_add_device(struct device *);
void transport_setup_device(struct device *);
void transport_configure_device(struct device *);
void transport_destroy_device(struct device *);

static inline void
transport_register_device(struct device *dev)
{
	transport_setup_device(dev);
	transport_add_device(dev);
}

static inline void
transport_unregister_device(struct device *dev)
{
	transport_remove_device(dev);
	transport_destroy_device(dev);
}

static inline int transport_container_register(struct transport_container *tc)
{
	return attribute_container_register(&tc->ac);
}

static inline void transport_container_unregister(struct transport_container *tc)
{
	if (unlikely(attribute_container_unregister(&tc->ac)))
		BUG();
}

int transport_class_register(struct transport_class *);
int anon_transport_class_register(struct anon_transport_class *);
void transport_class_unregister(struct transport_class *);
void anon_transport_class_unregister(struct anon_transport_class *);


#endif
