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
#ifndef OMAP3_ISP_CCP2_H
#define OMAP3_ISP_CCP2_H

#include <beep/videodev2.h>

struct isp_device;
struct isp_csiphy;

/* Sink and source ccp2 pads */
#define CCP2_PAD_SINK			0
#define CCP2_PAD_SOURCE			1
#define CCP2_PADS_NUM			2

/* CCP2 input media entity */
enum ccp2_input_entity {
	CCP2_INPUT_NONE,
	CCP2_INPUT_SENSOR,
	CCP2_INPUT_MEMORY,
};

/* CCP2 output media entity */
enum ccp2_output_entity {
	CCP2_OUTPUT_NONE,
	CCP2_OUTPUT_CCDC,
	CCP2_OUTPUT_MEMORY,
};


/* Logical channel configuration */
struct isp_interface_lcx_config {
	int crc;
	u32 data_start;
	u32 data_size;
	u32 format;
};

/* Memory channel configuration */
struct isp_interface_mem_config {
	u32 dst_port;
	u32 vsize_count;
	u32 hsize_count;
	u32 src_ofst;
	u32 dst_ofst;
};

/* CCP2 device */
struct isp_ccp2_device {
	struct v4l2_subdev subdev;
	struct v4l2_mbus_framefmt formats[CCP2_PADS_NUM];
	struct media_pad pads[CCP2_PADS_NUM];

	enum ccp2_input_entity input;
	enum ccp2_output_entity output;
	struct isp_interface_lcx_config if_cfg;
	struct isp_interface_mem_config mem_cfg;
	struct isp_video video_in;
	struct isp_csiphy *phy;
	struct regulator *vdds_csib;
	enum isp_pipeline_stream_state state;
	wait_queue_head_t wait;
	atomic_t stopping;
};

/* Function declarations */
int omap3isp_ccp2_init(struct isp_device *isp);
void omap3isp_ccp2_cleanup(struct isp_device *isp);
int omap3isp_ccp2_register_entities(struct isp_ccp2_device *ccp2,
			struct v4l2_device *vdev);
void omap3isp_ccp2_unregister_entities(struct isp_ccp2_device *ccp2);
void omap3isp_ccp2_isr(struct isp_ccp2_device *ccp2);

#endif	/* OMAP3_ISP_CCP2_H */
