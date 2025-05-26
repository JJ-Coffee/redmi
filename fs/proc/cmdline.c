// SPDX-License-Identifier: GPL-2.0
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/setup.h>

#ifdef CONFIG_KSU_SUSFS_SPOOF_CMDLINE_OR_BOOTCONFIG
extern int susfs_spoof_cmdline_or_bootconfig(struct seq_file *m);
#endif

static char spoofed_cmdline[COMMAND_LINE_SIZE];

static int cmdline_proc_show(struct seq_file *m, void *v)
{
#ifdef CONFIG_KSU_SUSFS_SPOOF_CMDLINE_OR_BOOTCONFIG
	if (!susfs_spoof_cmdline_or_bootconfig(m)) {
		seq_putc(m, '\n');
		return 0;
	}
#endif
	seq_printf(m, "%s\n", spoofed_cmdline);
	return 0;
}

static void __init spoof_cmdline_flags(char *cmd)
{
	strlcpy(spoofed_cmdline, cmd, COMMAND_LINE_SIZE);

	char *ptr;

	ptr = strstr(spoofed_cmdline, "androidboot.verifiedbootstate=");
	if (ptr) memcpy(ptr + 28, "green", 5);

	ptr = strstr(spoofed_cmdline, "androidboot.flash.locked=");
	if (ptr) memcpy(ptr + 25, "1", 1);

	ptr = strstr(spoofed_cmdline, "androidboot.secureboot.lockstate=");
	if (ptr) memcpy(ptr + 21, "locked", 1);

	ptr = strstr(spoofed_cmdline, "androidboot.vbmeta.device_state=");
	if (ptr) memcpy(ptr + 33, "locked", 6);

	ptr = strstr(spoofed_cmdline, "androidboot.veritymode=");
	if (ptr) memcpy(ptr + 23, "enforcing", 9);
}



static int cmdline_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cmdline_proc_show, NULL);
}

static const struct file_operations cmdline_proc_fops = {
	.open		= cmdline_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_cmdline_init(void)
{
	spoof_cmdline_flags(saved_command_line);
	proc_create("cmdline", 0, NULL, &cmdline_proc_fops);
	return 0;
}

fs_initcall(proc_cmdline_init);
