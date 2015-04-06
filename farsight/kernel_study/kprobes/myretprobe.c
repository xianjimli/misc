#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#define FUNC_NAME "sys_open"

static int ret_handler(struct kretprobe_instance *ri, struct pt_regs *regs)
{
	int retval = regs_return_value(regs);
	if (retval < 0) 
	{
		printk("%s returns %d\n", FUNC_NAME, retval);
	}
	
	return 0;
}

static struct kretprobe my_kretprobe = 
{
	.handler = ret_handler,
	.maxactive = 20
};

static int __init kretprobe_init(void)
{
	int ret = 0;
	my_kretprobe.kp.symbol_name = (char *)FUNC_NAME;

	if ((ret = register_kretprobe(&my_kretprobe)) < 0) 
	{
		printk("register_kretprobe failed, returned %d\n", ret);
		return -1;
	}

	printk("Planted return probe at %p\n", my_kretprobe.kp.addr);

	return 0;
}

static void __exit kretprobe_exit(void)
{
	unregister_kretprobe(&my_kretprobe);
	printk("kretprobe unregistered\n");

	return;
}

module_init(kretprobe_init)
module_exit(kretprobe_exit)
MODULE_LICENSE("GPL");

