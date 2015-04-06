#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

static long jdo_sys_open(int dfd, const char __user *filename, int flags, int mode)	      
{
	printk(KERN_INFO"%s filename=%s\n", __func__, filename);

	jprobe_return();
	return 0;
}

static struct jprobe my_jprobe = 
{
	.entry			= jdo_sys_open,
	.kp = 
	{
		.symbol_name	= "do_sys_open",
	},
};

static int __init jprobe_init(void)
{
	int ret;

	ret = register_jprobe(&my_jprobe);
	if (ret < 0) 
	{
		printk(KERN_INFO "register_jprobe failed, returned %d\n", ret);
		return -1;
	}

	printk(KERN_INFO"%s\n", __func__);

	return 0;
}

static void __exit jprobe_exit(void)
{
	unregister_jprobe(&my_jprobe);
	printk(KERN_INFO"%s\n", __func__);

	return;
}

module_init(jprobe_init)
module_exit(jprobe_exit)
MODULE_LICENSE("GPL");

