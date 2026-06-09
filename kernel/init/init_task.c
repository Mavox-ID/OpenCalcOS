#include <beep/init_task.h>
#include <beep/export.h>
#include <beep/mqueue.h>
#include <beep/sched.h>
#include <beep/init.h>
#include <beep/fs.h>
#include <beep/mm.h>

#include <asm/pgtable.h>
#include <asm/uaccess.h>

static struct signal_struct init_signals = INIT_SIGNALS(init_signals);
static struct sighand_struct init_sighand = INIT_SIGHAND(init_sighand);

/* Initial task structure */
struct task_struct init_task = INIT_TASK(init_task);
EXPORT_SYMBOL(init_task);

/*
 * Initial thread structure. Alignment of this is handled by a special
 * linker map entry.
 */
union thread_union init_thread_union __init_task_data =
	{ INIT_THREAD_INFO(init_task) };
