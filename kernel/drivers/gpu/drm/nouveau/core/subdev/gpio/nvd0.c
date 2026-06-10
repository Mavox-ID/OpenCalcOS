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
#include <subdev/gpio.h>

struct nvd0_gpio_priv {
	struct nouveau_gpio base;
};

static void
nvd0_gpio_reset(struct nouveau_gpio *gpio, u8 match)
{
	struct nouveau_bios *bios = nouveau_bios(gpio);
	struct nvd0_gpio_priv *priv = (void *)gpio;
	u8 ver, len;
	u16 entry;
	int ent = -1;

	while ((entry = dcb_gpio_entry(bios, 0, ++ent, &ver, &len))) {
		u32 data = nv_ro32(bios, entry);
		u8  line =   (data & 0x0000003f);
		u8  defs = !!(data & 0x00000080);
		u8  func =   (data & 0x0000ff00) >> 8;
		u8  unk0 =   (data & 0x00ff0000) >> 16;
		u8  unk1 =   (data & 0x1f000000) >> 24;

		if ( func  == DCB_GPIO_UNUSED ||
		    (match != DCB_GPIO_UNUSED && match != func))
			continue;

		gpio->set(gpio, 0, func, line, defs);

		nv_mask(priv, 0x00d610 + (line * 4), 0xff, unk0);
		if (unk1--)
			nv_mask(priv, 0x00d740 + (unk1 * 4), 0xff, line);
	}
}

static int
nvd0_gpio_drive(struct nouveau_gpio *gpio, int line, int dir, int out)
{
	u32 data = ((dir ^ 1) << 13) | (out << 12);
	nv_mask(gpio, 0x00d610 + (line * 4), 0x00003000, data);
	nv_mask(gpio, 0x00d604, 0x00000001, 0x00000001); /* update? */
	return 0;
}

static int
nvd0_gpio_sense(struct nouveau_gpio *gpio, int line)
{
	return !!(nv_rd32(gpio, 0x00d610 + (line * 4)) & 0x00004000);
}

static int
nvd0_gpio_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nvd0_gpio_priv *priv;
	int ret;

	ret = nouveau_gpio_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.reset = nvd0_gpio_reset;
	priv->base.drive = nvd0_gpio_drive;
	priv->base.sense = nvd0_gpio_sense;
	priv->base.irq_enable = nv50_gpio_irq_enable;
	nv_subdev(priv)->intr = nv50_gpio_intr;
	return 0;
}

struct nouveau_oclass
nvd0_gpio_oclass = {
	.handle = NV_SUBDEV(GPIO, 0xd0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvd0_gpio_ctor,
		.dtor = nv50_gpio_dtor,
		.init = nv50_gpio_init,
		.fini = nv50_gpio_fini,
	},
};
