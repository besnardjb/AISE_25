#include <linux/module.h>      // Required for all kernel modules
#include <linux/kernel.h>      // Required for printk()
#include <linux/init.h>        // Required for __init and __exit macros

MODULE_LICENSE("GPL");         // License type (GPL is the most common)
MODULE_AUTHOR("AISE Example MODULE");
MODULE_DESCRIPTION("A simple Hello World Linux module"); // Description

// Initialization function that runs when the module is loaded
static int __init hello_init(void)
{
    printk(KERN_INFO "Hello, World! The kernel module is loaded.\n");
    return 0;   // Returning 0 means the module was loaded successfully
}

// Exit function that runs when the module is unloaded
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, World! The kernel module is unloaded.\n");
}

// Registering the init and exit functions
module_init(hello_init);
module_exit(hello_exit);
