#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

static char* symbol_name = "do_fork";
module_param(symbol_name, charp, 0644);
MODULE_PARM_DESC(symbol_name, "the function to probe");

static struct kprobe kp = {
	.symbol_name	= "do_fork",
};

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	dump_stack();
	printk(KERN_INFO"%s", __func__);
	return 0;
}

static void handler_post(struct kprobe *p, struct pt_regs *regs,
				unsigned long flags)
{
	printk(KERN_INFO"%s", __func__);
	return;
}

static int handler_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
	printk(KERN_INFO"%s", __func__);
	return 0;
}

static int __init kprobe_init(void)
{
	int ret;
	kp.pre_handler   = handler_pre;
	kp.post_handler  = handler_post;
	kp.fault_handler = handler_fault;

	if(symbol_name != NULL)
	{
		kp.symbol_name = symbol_name;
	}

	if((ret = register_kprobe(&kp)) < 0)
	{
		printk(KERN_INFO "register_kprobe failed, returned %d\n", ret);
		return ret;
	}
	printk(KERN_INFO"%s", __func__);

	return 0;
}

static void __exit kprobe_exit(void)
{
	unregister_kprobe(&kp);
	printk(KERN_INFO"%s", __func__);

	return;
}

module_init(kprobe_init)
module_exit(kprobe_exit)
MODULE_LICENSE("GPL");

