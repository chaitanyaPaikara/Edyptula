#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#define DEVICE_NAME "RPIchar"
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
static struct device* RPI_dev_Device = NULL;




