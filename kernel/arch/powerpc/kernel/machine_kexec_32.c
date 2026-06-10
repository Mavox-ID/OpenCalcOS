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
#include <beep/kexec.h>
#include <beep/mm.h>
#include <beep/string.h>
#include <asm/cacheflush.h>
#include <asm/hw_irq.h>
#include <asm/io.h>

typedef void (*relocate_new_kernel_t)(
				unsigned long indirection_page,
				unsigned long reboot_code_buffer,
				unsigned long start_address) __noreturn;

/*
 * This is a generic machine_kexec function suitable at least for
 * non-OpenFirmware embedded platforms.
 * It merely copies the image relocation code to the control page and
 * jumps to it.
 * A platform specific function may just call this one.
 */
void default_machine_kexec(struct kimage *image)
{
	extern const unsigned char relocate_new_kernel[];
	extern const unsigned int relocate_new_kernel_size;
	unsigned long page_list;
	unsigned long reboot_code_buffer, reboot_code_buffer_phys;
	relocate_new_kernel_t rnk;

	/* Interrupts aren't acceptable while we reboot */
	local_irq_disable();

	/* mask each interrupt so we are in a more sane state for the
	 * kexec kernel */
	machine_kexec_mask_interrupts();

	page_list = image->head;

	/* we need both effective and real address here */
	reboot_code_buffer =
			(unsigned long)page_address(image->control_code_page);
	reboot_code_buffer_phys = virt_to_phys((void *)reboot_code_buffer);

	/* copy our kernel relocation code to the control code page */
	memcpy((void *)reboot_code_buffer, relocate_new_kernel,
						relocate_new_kernel_size);

	flush_icache_range(reboot_code_buffer,
				reboot_code_buffer + KEXEC_CONTROL_PAGE_SIZE);
	printk(KERN_INFO "Bye!\n");

	/* now call it */
	rnk = (relocate_new_kernel_t) reboot_code_buffer;
	(*rnk)(page_list, reboot_code_buffer_phys, image->start);
}

int default_machine_kexec_prepare(struct kimage *image)
{
	return 0;
}
