//module based on work by Derek Malloy
//http://derekmolloy.ie/writing-a-linux-kernel-module-part-1-introduction


#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Bakewell");
MODULE_DESCRIPTION("My first kernel module");
MODULE_VERSION("0.1");

static char* name = "Thomas";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "the name to display (my own)");

static int __init helloTCB_init(void){
	printk(KERN_INFO "EBB: Hello %s from the BBB LKM!\n", name);
	return 0;
}

static void __exit helloTCB_exit(void){
	printk(KERN_INFO "EBB: Goodbye %s from the BBB LKM!\n", name);
}

module_init(helloTCB_init);
module_exit(helloTCB_exit);

