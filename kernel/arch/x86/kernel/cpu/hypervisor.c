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
#include <beep/module.h>
#include <asm/processor.h>
#include <asm/hypervisor.h>

/*
 * Hypervisor detect order.  This is specified explicitly here because
 * some hypervisors might implement compatibility modes for other
 * hypervisors and therefore need to be detected in specific sequence.
 */
static const __initconst struct hypervisor_x86 * const hypervisors[] =
{
#ifdef CONFIG_XEN_PVHVM
	&x86_hyper_xen_hvm,
#endif
	&x86_hyper_vmware,
	&x86_hyper_ms_hyperv,
#ifdef CONFIG_KVM_GUEST
	&x86_hyper_kvm,
#endif
};

const struct hypervisor_x86 *x86_hyper;
EXPORT_SYMBOL(x86_hyper);

static inline void __init
detect_hypervisor_vendor(void)
{
	const struct hypervisor_x86 *h, * const *p;

	for (p = hypervisors; p < hypervisors + ARRAY_SIZE(hypervisors); p++) {
		h = *p;
		if (h->detect()) {
			x86_hyper = h;
			printk(KERN_INFO "Hypervisor detected: %s\n", h->name);
			break;
		}
	}
}

void __cpuinit init_hypervisor(struct cpuinfo_x86 *c)
{
	if (x86_hyper && x86_hyper->set_cpu_features)
		x86_hyper->set_cpu_features(c);
}

void __init init_hypervisor_platform(void)
{

	detect_hypervisor_vendor();

	if (!x86_hyper)
		return;

	init_hypervisor(&boot_cpu_data);

	if (x86_hyper->init_platform)
		x86_hyper->init_platform();
}
