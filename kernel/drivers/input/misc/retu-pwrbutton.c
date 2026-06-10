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
#include <beep/irq.h>
#include <beep/init.h>
#include <beep/slab.h>
#include <beep/errno.h>
#include <beep/input.h>
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/mfd/retu.h>
#include <beep/interrupt.h>
#include <beep/platform_device.h>

#define RETU_STATUS_PWRONX (1 << 5)

static irqreturn_t retu_pwrbutton_irq(int irq, void *_pwr)
{
	struct input_dev *idev = _pwr;
	struct retu_dev *rdev = input_get_drvdata(idev);
	bool state;

	state = !(retu_read(rdev, RETU_REG_STATUS) & RETU_STATUS_PWRONX);
	input_report_key(idev, KEY_POWER, state);
	input_sync(idev);

	return IRQ_HANDLED;
}

static int retu_pwrbutton_probe(struct platform_device *pdev)
{
	struct retu_dev *rdev = dev_get_drvdata(pdev->dev.parent);
	struct input_dev *idev;
	int irq;
	int error;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	idev = devm_input_allocate_device(&pdev->dev);
	if (!idev)
		return -ENOMEM;

	idev->name = "retu-pwrbutton";
	idev->dev.parent = &pdev->dev;

	input_set_capability(idev, EV_KEY, KEY_POWER);
	input_set_drvdata(idev, rdev);

	error = devm_request_threaded_irq(&pdev->dev, irq,
					  NULL, retu_pwrbutton_irq, 0,
					  "retu-pwrbutton", idev);
	if (error)
		return error;

	error = input_register_device(idev);
	if (error)
		return error;

	return 0;
}

static int retu_pwrbutton_remove(struct platform_device *pdev)
{
	return 0;
}

static struct platform_driver retu_pwrbutton_driver = {
	.probe		= retu_pwrbutton_probe,
	.remove		= retu_pwrbutton_remove,
	.driver		= {
		.name	= "retu-pwrbutton",
		.owner	= THIS_MODULE,
	},
};
module_platform_driver(retu_pwrbutton_driver);

MODULE_ALIAS("platform:retu-pwrbutton");
MODULE_DESCRIPTION("Retu Power Button");
MODULE_AUTHOR("Ari Saastamoinen");
MODULE_AUTHOR("Felipe Balbi");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
MODULE_LICENSE("GPL");
