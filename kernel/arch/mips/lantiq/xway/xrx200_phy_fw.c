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
#include <beep/delay.h>
#include <beep/dma-mapping.h>
#include <beep/module.h>
#include <beep/firmware.h>
#include <beep/of_platform.h>

#include <lantiq_soc.h>

#define XRX200_GPHY_FW_ALIGN	(16 * 1024)

static dma_addr_t xway_gphy_load(struct platform_device *pdev)
{
	const struct firmware *fw;
	dma_addr_t dev_addr = 0;
	const char *fw_name;
	void *fw_addr;
	size_t size;

	if (of_property_read_string(pdev->dev.of_node, "firmware", &fw_name)) {
		dev_err(&pdev->dev, "failed to load firmware filename\n");
		return 0;
	}

	dev_info(&pdev->dev, "requesting %s\n", fw_name);
	if (request_firmware(&fw, fw_name, &pdev->dev)) {
		dev_err(&pdev->dev, "failed to load firmware: %s\n", fw_name);
		return 0;
	}

	/*
	 * GPHY cores need the firmware code in a persistent and contiguous
	 * memory area with a 16 kB boundary aligned start address
	 */
	size = fw->size + XRX200_GPHY_FW_ALIGN;

	fw_addr = dma_alloc_coherent(&pdev->dev, size, &dev_addr, GFP_KERNEL);
	if (fw_addr) {
		fw_addr = PTR_ALIGN(fw_addr, XRX200_GPHY_FW_ALIGN);
		dev_addr = ALIGN(dev_addr, XRX200_GPHY_FW_ALIGN);
		memcpy(fw_addr, fw->data, fw->size);
	} else {
		dev_err(&pdev->dev, "failed to alloc firmware memory\n");
	}

	release_firmware(fw);
	return dev_addr;
}

static int xway_phy_fw_probe(struct platform_device *pdev)
{
	dma_addr_t fw_addr;
	struct property *pp;
	unsigned char *phyids;
	int i, ret = 0;

	fw_addr = xway_gphy_load(pdev);
	if (!fw_addr)
		return -EINVAL;
	pp = of_find_property(pdev->dev.of_node, "phys", NULL);
	if (!pp)
		return -ENOENT;
	phyids = pp->value;
	for (i = 0; i < pp->length && !ret; i++)
		ret = xrx200_gphy_boot(&pdev->dev, phyids[i], fw_addr);
	if (!ret)
		mdelay(100);
	return ret;
}

static const struct of_device_id xway_phy_match[] = {
	{ .compatible = "lantiq,phy-xrx200" },
	{},
};
MODULE_DEVICE_TABLE(of, xway_phy_match);

static struct platform_driver xway_phy_driver = {
	.probe = xway_phy_fw_probe,
	.driver = {
		.name = "phy-xrx200",
		.owner = THIS_MODULE,
		.of_match_table = xway_phy_match,
	},
};

module_platform_driver(xway_phy_driver);

MODULE_AUTHOR("John Crispin <blogic@openwrt.org>");
MODULE_DESCRIPTION("Lantiq XRX200 PHY Firmware Loader");
MODULE_LICENSE("GPL");
