#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#define DEVICE_NAME "char_dev"
#define CLASS_NAME "RPI_dev"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chaitanya");
MODULE_DESCRIPTION("Linux character driver");
MODULE_VERSION("0.1");

static int majorNumber;
static char message[256] = {0};
static short size_of _messages;
static int numberOpens = 0;
static struct class* RPI_dev_Class = NULL;
static struct device* char_dev_Device = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, char *, size_t, loff_t *);

static struct file_operations fops =
	{
		.open = dev_open;
		.release = dev_release;
		.write = dev_write;
		.read = dev_read;
	};

static int __init char_dev_init(void){
	printkl(KERN_INFO "F**K : Loading and Initialing the LKM.\n");
	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
	if(majorNumber < 0){
		printk(KERN_ALERT "F**K : Failed to register the major Number.\n");
		return majorNumber;
	}
	printk(KERN_INFO "F**K : Register the major Number.\n");
	RPI_dev_class = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(RPI_dev_class)){
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "F**K : Failed to register the DEVICE CLASS.\n");
		return PTR_ERR(RPI_dev_class);
	}
	char_dev_device = device_create(RPI_dev_class, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
        if(IS_ERR(char_dev_class)){
		class_destroy(RPI_dev_class);
                unregister_chrdev(majorNumber, DEVICE_NAME);
                printk(KERN_ALERT "F**K : Failed to register the DEVICE.\n");
                return PTR_ERR(char_dev_class);
        }
	printk(KERN_INFO "F**K : Device class also created succesfully.\n")
	return 0;
}

static void __exit char_dev_exit(void){
	device_destroy(char_dev_device, MKDEV(majorNumber, 0));
	unregister_class(RPI_dev_class);
	class_destroy(RPI_dev_class);
	unregister_chrdev(majorNumber, DEVICE_NAME);
	printk(KERN_INFO "F**K : Goodbye , exiting the LKM.\n");
}

static int dev_open(struct inode *inodep, struct file *filep){
	numberOpens++;
	printk(KERN_INFO "F**K : Device with major number %d has been opened %d times.\n",majorNumber , numberOpens);
	return 0 ;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
	int error_count = 0;
	error_count = copy_to_user(buffer, message, size_of_message)
	if(error_count == 0){
		printk(KERN_INFO "F**K : Sent %d characters to the user.\n", size_of_message);
		return (size_of_message = 0);
	}
	else {
		printk(KERN_INFO "F**K : Failed to send %d characters the message.\n", error_count);
		return -EFAULT;
	}
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   sprintf(message, "%s(%zu letters)", buffer, len);
   size_of_message = strlen(message);
   printk(KERN_INFO "F**K : Received %zu characters from the user\n", len);
   return len;
}

static int dev_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "F**K : Device successfully closed\n");
   return 0;
}

module_init(char_dev_init);
module_exit(char_dev_exit);
