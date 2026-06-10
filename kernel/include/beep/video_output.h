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
#ifndef _BEEP_VIDEO_OUTPUT_H
#define _BEEP_VIDEO_OUTPUT_H
#include <beep/device.h>
#include <beep/err.h>
struct output_device;
struct output_properties {
	int (*set_state)(struct output_device *);
	int (*get_status)(struct output_device *);
};
struct output_device {
	int request_state;
	struct output_properties *props;
	struct device dev;
};
#define to_output_device(obj) container_of(obj, struct output_device, dev)
#if	defined(CONFIG_VIDEO_OUTPUT_CONTROL) || defined(CONFIG_VIDEO_OUTPUT_CONTROL_MODULE)
struct output_device *video_output_register(const char *name,
	struct device *dev,
	void *devdata,
	struct output_properties *op);
void video_output_unregister(struct output_device *dev);
#else
static struct output_device *video_output_register(const char *name,
        struct device *dev,
        void *devdata,
        struct output_properties *op)
{
	return ERR_PTR(-ENODEV);
}
static void video_output_unregister(struct output_device *dev)
{
	return;
}
#endif
#endif
