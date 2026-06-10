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
#ifndef __IBM_NEWEMAC_RGMII_H
#define __IBM_NEWEMAC_RGMII_H

/* RGMII bridge type */
#define RGMII_STANDARD		0
#define RGMII_AXON		1

/* RGMII bridge */
struct rgmii_regs {
	u32 fer;		/* Function enable register */
	u32 ssr;		/* Speed select register */
};

/* RGMII device */
struct rgmii_instance {
	struct rgmii_regs __iomem	*base;

	/* RGMII bridge flags */
	int				flags;
#define EMAC_RGMII_FLAG_HAS_MDIO	0x00000001

	/* Only one EMAC whacks us at a time */
	struct mutex			lock;

	/* number of EMACs using this RGMII bridge */
	int				users;

	/* OF device instance */
	struct platform_device		*ofdev;
};

#ifdef CONFIG_IBM_EMAC_RGMII

extern int rgmii_init(void);
extern void rgmii_exit(void);
extern int rgmii_attach(struct platform_device *ofdev, int input, int mode);
extern void rgmii_detach(struct platform_device *ofdev, int input);
extern void rgmii_get_mdio(struct platform_device *ofdev, int input);
extern void rgmii_put_mdio(struct platform_device *ofdev, int input);
extern void rgmii_set_speed(struct platform_device *ofdev, int input, int speed);
extern int rgmii_get_regs_len(struct platform_device *ofdev);
extern void *rgmii_dump_regs(struct platform_device *ofdev, void *buf);

#else

# define rgmii_init()		0
# define rgmii_exit()		do { } while(0)
# define rgmii_attach(x,y,z)	(-ENXIO)
# define rgmii_detach(x,y)	do { } while(0)
# define rgmii_get_mdio(o,i)	do { } while (0)
# define rgmii_put_mdio(o,i)	do { } while (0)
# define rgmii_set_speed(x,y,z)	do { } while(0)
# define rgmii_get_regs_len(x)	0
# define rgmii_dump_regs(x,buf)	(buf)
#endif				/* !CONFIG_IBM_EMAC_RGMII */

#endif /* __IBM_NEWEMAC_RGMII_H */
