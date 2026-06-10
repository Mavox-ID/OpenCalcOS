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
#include <beep/syscore_ops.h>
#include <beep/mutex.h>
#include <beep/module.h>
#include <beep/interrupt.h>

static LIST_HEAD(syscore_ops_list);
static DEFINE_MUTEX(syscore_ops_lock);

/**
 * register_syscore_ops - Register a set of system core operations.
 * @ops: System core operations to register.
 */
void register_syscore_ops(struct syscore_ops *ops)
{
	mutex_lock(&syscore_ops_lock);
	list_add_tail(&ops->node, &syscore_ops_list);
	mutex_unlock(&syscore_ops_lock);
}
EXPORT_SYMBOL_GPL(register_syscore_ops);

/**
 * unregister_syscore_ops - Unregister a set of system core operations.
 * @ops: System core operations to unregister.
 */
void unregister_syscore_ops(struct syscore_ops *ops)
{
	mutex_lock(&syscore_ops_lock);
	list_del(&ops->node);
	mutex_unlock(&syscore_ops_lock);
}
EXPORT_SYMBOL_GPL(unregister_syscore_ops);

#ifdef CONFIG_PM_SLEEP
/**
 * syscore_suspend - Execute all the registered system core suspend callbacks.
 *
 * This function is executed with one CPU on-line and disabled interrupts.
 */
int syscore_suspend(void)
{
	struct syscore_ops *ops;
	int ret = 0;

	pr_debug("Checking wakeup interrupts\n");

	/* Return error code if there are any wakeup interrupts pending. */
	ret = check_wakeup_irqs();
	if (ret)
		return ret;

	WARN_ONCE(!irqs_disabled(),
		"Interrupts enabled before system core suspend.\n");

	list_for_each_entry_reverse(ops, &syscore_ops_list, node)
		if (ops->suspend) {
			if (initcall_debug)
				pr_info("PM: Calling %pF\n", ops->suspend);
			ret = ops->suspend();
			if (ret)
				goto err_out;
			WARN_ONCE(!irqs_disabled(),
				"Interrupts enabled after %pF\n", ops->suspend);
		}

	return 0;

 err_out:
	pr_err("PM: System core suspend callback %pF failed.\n", ops->suspend);

	list_for_each_entry_continue(ops, &syscore_ops_list, node)
		if (ops->resume)
			ops->resume();

	return ret;
}
EXPORT_SYMBOL_GPL(syscore_suspend);

/**
 * syscore_resume - Execute all the registered system core resume callbacks.
 *
 * This function is executed with one CPU on-line and disabled interrupts.
 */
void syscore_resume(void)
{
	struct syscore_ops *ops;

	WARN_ONCE(!irqs_disabled(),
		"Interrupts enabled before system core resume.\n");

	list_for_each_entry(ops, &syscore_ops_list, node)
		if (ops->resume) {
			if (initcall_debug)
				pr_info("PM: Calling %pF\n", ops->resume);
			ops->resume();
			WARN_ONCE(!irqs_disabled(),
				"Interrupts enabled after %pF\n", ops->resume);
		}
}
EXPORT_SYMBOL_GPL(syscore_resume);
#endif /* CONFIG_PM_SLEEP */

/**
 * syscore_shutdown - Execute all the registered system core shutdown callbacks.
 */
void syscore_shutdown(void)
{
	struct syscore_ops *ops;

	mutex_lock(&syscore_ops_lock);

	list_for_each_entry_reverse(ops, &syscore_ops_list, node)
		if (ops->shutdown) {
			if (initcall_debug)
				pr_info("PM: Calling %pF\n", ops->shutdown);
			ops->shutdown();
		}

	mutex_unlock(&syscore_ops_lock);
}
