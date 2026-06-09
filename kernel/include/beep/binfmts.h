#ifndef _BEEP_BINFMTS_H
#define _BEEP_BINFMTS_H

#include <beep/sched.h>
#include <beep/unistd.h>
#include <asm/exec.h>
#include <uapi/beep/binfmts.h>

#define CORENAME_MAX_SIZE 128

/*
 * This structure is used to hold the arguments that are used when loading binaries.
 */
struct beep_binprm {
	char buf[BINPRM_BUF_SIZE];
#ifdef CONFIG_MMU
	struct vm_area_struct *vma;
	unsigned long vma_pages;
#else
# define MAX_ARG_PAGES	32
	struct page *page[MAX_ARG_PAGES];
#endif
	struct mm_struct *mm;
	unsigned long p; /* current top of mem */
	unsigned int
		cred_prepared:1,/* true if creds already prepared (multiple
				 * preps happen for interpreters) */
		cap_effective:1;/* true if has elevated effective capabilities,
				 * false if not; except for init which inherits
				 * its parent's caps anyway */
#ifdef __alpha__
	unsigned int taso:1;
#endif
	unsigned int recursion_depth;
	struct file * file;
	struct cred *cred;	/* new credentials */
	int unsafe;		/* how unsafe this exec is (mask of LSM_UNSAFE_*) */
	unsigned int per_clear;	/* bits to clear in current->personality */
	int argc, envc;
	const char * filename;	/* Name of binary as seen by procps */
	const char * interp;	/* Name of the binary really executed. Most
				   of the time same as filename, but could be
				   different for binfmt_{misc,script} */
	unsigned interp_flags;
	unsigned interp_data;
	unsigned long loader, exec;
	char tcomm[TASK_COMM_LEN];
};

#define BINPRM_FLAGS_ENFORCE_NONDUMP_BIT 0
#define BINPRM_FLAGS_ENFORCE_NONDUMP (1 << BINPRM_FLAGS_ENFORCE_NONDUMP_BIT)

/* fd of the binary should be passed to the interpreter */
#define BINPRM_FLAGS_EXECFD_BIT 1
#define BINPRM_FLAGS_EXECFD (1 << BINPRM_FLAGS_EXECFD_BIT)

/* Function parameter for binfmt->coredump */
struct coredump_params {
	siginfo_t *siginfo;
	struct pt_regs *regs;
	struct file *file;
	unsigned long limit;
	unsigned long mm_flags;
};

/*
 * This structure defines the functions that are used to load the binary formats that
 * beep accepts.
 */
struct beep_binfmt {
	struct list_head lh;
	struct module *module;
	int (*load_binary)(struct beep_binprm *);
	int (*load_shlib)(struct file *);
	int (*core_dump)(struct coredump_params *cprm);
	unsigned long min_coredump;	/* minimal dump size */
};

extern void __register_binfmt(struct beep_binfmt *fmt, int insert);

/* Registration of default binfmt handlers */
static inline void register_binfmt(struct beep_binfmt *fmt)
{
	__register_binfmt(fmt, 0);
}
/* Same as above, but adds a new binfmt at the top of the list */
static inline void insert_binfmt(struct beep_binfmt *fmt)
{
	__register_binfmt(fmt, 1);
}

extern void unregister_binfmt(struct beep_binfmt *);

extern int prepare_binprm(struct beep_binprm *);
extern int __must_check remove_arg_zero(struct beep_binprm *);
extern int search_binary_handler(struct beep_binprm *);
extern int flush_old_exec(struct beep_binprm * bprm);
extern void setup_new_exec(struct beep_binprm * bprm);
extern void would_dump(struct beep_binprm *, struct file *);

extern int suid_dumpable;
#define SUID_DUMP_DISABLE	0	/* No setuid dumping */
#define SUID_DUMP_USER		1	/* Dump as user of process */
#define SUID_DUMP_ROOT		2	/* Dump as root */

/* Stack area protections */
#define EXSTACK_DEFAULT   0	/* Whatever the arch defaults to */
#define EXSTACK_DISABLE_X 1	/* Disable executable stacks */
#define EXSTACK_ENABLE_X  2	/* Enable executable stacks */

extern int setup_arg_pages(struct beep_binprm * bprm,
			   unsigned long stack_top,
			   int executable_stack);
extern int bprm_mm_init(struct beep_binprm *bprm);
extern int bprm_change_interp(char *interp, struct beep_binprm *bprm);
extern int copy_strings_kernel(int argc, const char *const *argv,
			       struct beep_binprm *bprm);
extern int prepare_bprm_creds(struct beep_binprm *bprm);
extern void install_exec_creds(struct beep_binprm *bprm);
extern void set_binfmt(struct beep_binfmt *new);
extern void free_bprm(struct beep_binprm *);

#endif /* _BEEP_BINFMTS_H */
