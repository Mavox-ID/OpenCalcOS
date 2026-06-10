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
#include <beep/slab.h>
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/platform_device.h>

#include <beep/platform_data/video-msm_fb.h>

struct panel_info {
	struct platform_device pdev;
	struct msm_panel_data panel_data;
};

static int mddi_dummy_suspend(struct msm_panel_data *panel_data)
{
	return 0;
}

static int mddi_dummy_resume(struct msm_panel_data *panel_data)
{
	return 0;
}

static int mddi_dummy_blank(struct msm_panel_data *panel_data)
{
	return 0;
}

static int mddi_dummy_unblank(struct msm_panel_data *panel_data)
{
	return 0;
}

static int mddi_dummy_probe(struct platform_device *pdev)
{
	struct msm_mddi_client_data *client_data = pdev->dev.platform_data;
	struct panel_info *panel =
		kzalloc(sizeof(struct panel_info), GFP_KERNEL);
	int ret;
	if (!panel)
		return -ENOMEM;
	platform_set_drvdata(pdev, panel);
	panel->panel_data.suspend = mddi_dummy_suspend;
	panel->panel_data.resume = mddi_dummy_resume;
	panel->panel_data.blank = mddi_dummy_blank;
	panel->panel_data.unblank = mddi_dummy_unblank;
	panel->panel_data.caps = MSMFB_CAP_PARTIAL_UPDATES;
	panel->pdev.name = "msm_panel";
	panel->pdev.id = pdev->id;
	platform_device_add_resources(&panel->pdev,
				      client_data->fb_resource, 1);
	panel->panel_data.fb_data = client_data->private_client_data;
	panel->pdev.dev.platform_data = &panel->panel_data;
	ret = platform_device_register(&panel->pdev);
	if (ret) {
		kfree(panel);
		return ret;
	}
	return 0;
}

static int mddi_dummy_remove(struct platform_device *pdev)
{
	struct panel_info *panel = platform_get_drvdata(pdev);
	kfree(panel);
	return 0;
}

static struct platform_driver mddi_client_dummy = {
	.probe = mddi_dummy_probe,
	.remove = mddi_dummy_remove,
	.driver = { .name = "mddi_c_dummy" },
};

static int __init mddi_client_dummy_init(void)
{
	platform_driver_register(&mddi_client_dummy);
	return 0;
}

module_init(mddi_client_dummy_init);

