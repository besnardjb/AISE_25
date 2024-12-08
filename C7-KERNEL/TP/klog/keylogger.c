#include <linux/module.h>
#include <linux/keyboard.h>

#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("JBB");
MODULE_DESCRIPTION("A First module");
MODULE_VERSION("1.0");

static int func(struct notifier_block* s, unsigned long action, void* pointer)
{
	struct keyboard_notifier_param* param = (struct keyboard_notifier_param*) pointer;
	printk(KERN_INFO "Called by keyboard interaction\n");

	/* TODO PRINT */

	return NOTIFY_OK;
}

static struct notifier_block s = {
	.notifier_call = func,
};

static int __init mymod_init(void){
	printk(KERN_INFO "MyMod: Hello there !\n");
	register_keyboard_notifier(&s);
	return 0;
}
static void __exit mymod_exit(void){
	printk(KERN_INFO "MyMod: Goodbye !\n");
	unregister_keyboard_notifier(&s);
}
module_init(mymod_init);
module_exit(mymod_exit);
