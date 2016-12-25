#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chaitanya");
MODULE_DESCRIPTION("lINUX DEVICE DRIVER FOR Printing GREETING!!!...");
MODULE_VERSION("0.1");

static char *name_ptr = "Peeps...";
module_param(name_ptr,charp,S_IRUGO);
MODULE_PARM_DESC(name_ptr, "Display in /var/log/kern.log");

static int __init hello_init(void){
	printk(KERN_INFO "F**K : Hello %s.\n",name_ptr);
	return 0;
}

static void __exit hello_exit(void){
	printk(KERN_INFO "F**K : Goodbye %s.\n",name_ptr);
}

module_init(hello_init);
module_exit(hello_exit);
