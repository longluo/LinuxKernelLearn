#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/sched.h> 
#include <linux/version.h>
#include <linux/string.h>
#include <linux/uaccess.h>

static struct proc_dir_entry *Proc_Parent_Process;
static struct task_struct *Current_Task;

static long Length = 0;
static pid_t PID = 2;

static int get_task_by_pid( char *page, struct task_struct *task )
{
	int i = 0;
	for_each_process( task ) {
		if( PID == task->pid ) {
			for ( i = 0; task != &init_task; task = task->parent, i++)
				Length += sprintf(page+Length, "%d. PID = %d\n",i,task->pid);

			return (0);
		}
	}
	return (1);
}

static int read_parent_process(char *page, char **start, off_t off, int count,
							   int *eof, void *data)
{
	Length = sprintf(page, "First Proc File System Module\n");
	Length += sprintf(page+Length, "Virtual File Name: %s\n",Proc_Parent_Process->name);

	if ( 1 == get_task_by_pid(page, Current_Task) )
		Length += sprintf(page+Length, "PID was not found\n");

	return (Length);
}

static int write_parent_process( struct file *file, const char __user *buffer,
									unsigned long count, void *data )
{
	char *char_pid;

	char_pid = kmalloc((size_t) count, GFP_KERNEL );

	if ( copy_from_user(char_pid, buffer, count) ) {
		kfree(char_pid);
		return -EFAULT;
	}

	sscanf(char_pid, "%d", &PID);

	return (PID);
}

static int __init my_init(void)
{
	printk(KERN_INFO "Hello Process File System World!\n");
	Proc_Parent_Process = create_proc_entry("parent_process", 0, NULL);
	Proc_Parent_Process->read_proc = read_parent_process;
	Proc_Parent_Process->write_proc = write_parent_process;

	return (0);
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Bye Process File System World!\n");
	if (Proc_Parent_Process) {
		remove_proc_entry("parent_process", NULL);
	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Long Luo");
MODULE_DESCRIPTION("This is a Process File System hello world");
