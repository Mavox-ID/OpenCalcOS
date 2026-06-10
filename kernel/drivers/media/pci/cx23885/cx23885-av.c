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
#include "cx23885.h"
#include "cx23885-av.h"

void cx23885_av_work_handler(struct work_struct *work)
{
	struct cx23885_dev *dev =
			   container_of(work, struct cx23885_dev, cx25840_work);
	bool handled;

	v4l2_subdev_call(dev->sd_cx25840, core, interrupt_service_routine,
			 PCI_MSK_AV_CORE, &handled);
	cx23885_irq_enable(dev, PCI_MSK_AV_CORE);
}
