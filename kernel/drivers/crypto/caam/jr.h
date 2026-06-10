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
#ifndef JR_H
#define JR_H

/* Prototypes for backend-level services exposed to APIs */
int caam_jr_register(struct device *ctrldev, struct device **rdev);
int caam_jr_deregister(struct device *rdev);
int caam_jr_enqueue(struct device *dev, u32 *desc,
		    void (*cbk)(struct device *dev, u32 *desc, u32 status,
				void *areq),
		    void *areq);

extern int caam_jr_probe(struct platform_device *pdev, struct device_node *np,
			 int ring);
extern int caam_jr_shutdown(struct device *dev);
#endif /* JR_H */
