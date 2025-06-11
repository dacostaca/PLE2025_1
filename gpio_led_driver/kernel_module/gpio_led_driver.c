//Creación de modulo kernel para control de led por GPIO
//con implementación de driver de dispositivo de caracteres

//Hecho por Daniel Felipe Acosta Castro
//ultima actualización: 10/06/2025

#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include <linux/cdev.h>		//modulos sugeridos por Deepseek (no gpt)
#include <linux/device.h>
#include <linux/printk.h>

#include <linux/init.h> 	//modulos sugeridos por gpt (no Deepseek)

#define DEVICE_NAME "led_gpio"
#define CLASS_NAME "led"		//gpt define una "class name" pero Dpsk define el pin

static int major;
static struct class* led_class = NULL;
static struct device* led_dev = NULL;

//en este punto ambas IA precentan bastantes diferencias, desde aquí...
static int gpioPin = 17;
module_param(gpioPin, int, S_IRUGO);
MODULE_PARM_DESC(gpioPin, "GPIO pin number for LED");

static char msg[2] = {0};	//buffer del mensaje
static short size_of_msg;
static bool ledOn = false;
//... hasta aquí, (lo anterior fue hecho por chat gpt)

//Prototipado de funciones para controlador de caracteres
static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_write(stuct file *, const char __user *, size_t, loff_t *);

static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int __init led_init(void){


}

static void __exit led_exit(void){


}


//Definición de funciones open, release, write, read
static int dev_open(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "LED GPIO: Se ha abierto el dispositivo\n");
	return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "LED GPIO: El dispositivo se ha cerrado exitosamente\n");
	return 0;
}

static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
	char state = ledOn ? '1' : '0';
	if (copy_to_user(buffer, &state, 1)) {
		printk(KERN_ERR "LED GPIO: falla al enviar byte al usuario\n");
		return -EFAULT;
	}
	printk(KERN_INFO "LED GPIO: enviado estado '%c' al usuario\n", state);
	return 1;
}


module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MDOULE_AUTHOR("Daniel Felipe Acosta Castro");
MODULE_DESCRIPTION("Controlador de dispositivo de caracteres para manejo de led por GPIO (Lichee RV DOCK)");
