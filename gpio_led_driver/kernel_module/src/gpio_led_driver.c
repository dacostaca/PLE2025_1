//Creación de modulo kernel para control de led por GPIO
//con implementación de driver de dispositivo de caracteres

//Hecho por Daniel Felipe Acosta Castro
//ultima actualización: 19/06/2025

#include "../include/gpio_led_driver.h"
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/err.h>

static int majorNumber;
static struct class* ledClass = NULL;
static struct device* ledDevice = NULL;

static int gpioPin = 112;
module_param(gpioPin, int, S_IRUGO);
MODULE_PARM_DESC(gpioPin, "GPIO numero de pin para LED");

static bool ledOn = false;

static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

//FUNCIONES DE ENTRADA Y SALIDA
static int __init led_init(void){
	int result;

	printk(KERN_INFO "LED GPIO: Inicializando modulo LED GPIO\n");

	//Solicitar GPIO
	if (!gpio_is_valid(gpioPin)) {
		printk(KERN_ERR "LED GPIO: GPIO invalido %d\n", gpioPin);
		return -ENODEV;
	}

	result = gpio_request(gpioPin, "led_gpio");
	if (result) {
		printk(KERN_ERR "LED GPIO: Falla al solicitar GPIO %d (error %d)\n", gpioPin, result);
		return result;
	}

	gpio_direction_output(gpioPin, 0);

	//Register character device
	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
	if (majorNumber < 0) {
		printk(KERN_ERR "LED GPIO: Error al registrar major number (error %d)\n", majorNumber);
		gpio_free(gpioPin);
		return majorNumber;
	}

	//Register device class
	ledClass = class_create(CLASS_NAME);
	if (IS_ERR(ledClass)) {
		unregister_chrdev(majorNumber, DEVICE_NAME);
		gpio_free(gpioPin);
		printk(KERN_ERR "LED GPIO: Falla al registro de clase dispositivo\n");
		return PTR_ERR(ledClass);
	}

	//Register device driver
	ledDevice = device_create(ledClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(ledDevice)) {
		class_destroy(ledClass);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		gpio_free(gpioPin);
		printk(KERN_ERR "LED GPIO: Falla al crear dispositivo\n");
		return PTR_ERR(ledDevice);
	}

	printk(KERN_INFO "LED GPIO: Modulo cargado! dispositivo creado en /dev/%s with major number %d\n", DEVICE_NAME, majorNumber);
	return 0;
}

static void __exit led_exit(void){
	device_destroy(ledClass, MKDEV(majorNumber, 0));
	class_unregister(ledClass);
	class_destroy(ledClass);
	unregister_chrdev(majorNumber, DEVICE_NAME);
	gpio_free(gpioPin);
	printk(KERN_INFO "LED GPIO: Modulo descargado y GPIO liberado\n");
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

static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset)
{
	char kbuf[2] = {0};
	if (len >2) {
		printk(KERN_ERR "LED GPIO: tamaño de escritura invalido %zu\n", len);
		return -EINVAL;
	}
	if (copy_from_user(kbuf, buffer, len)) {
		printk(KERN_ERR "LED GPIO: Falla al recibir byte desde usuario\n");
		return -EFAULT;
	}

	if (kbuf[0] == '1') {
		gpio_set_value(gpioPin, 1);
		ledOn = true;
		printk(KERN_INFO "LED GPIO: LED ENCENDIDO\n");
	} else if (kbuf[0] == '0') {
		gpio_set_value(gpioPin, 0);
		ledOn = false;
		printk(KERN_INFO "LED GPIO: LED APAGADO\n");
	} else {
		printk(KERN_ERR "LED GPIO: Comando Invalido '%c'\n", kbuf[0]);
		return -EINVAL;
	}
	return len;
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Felipe Acosta Castro");
MODULE_DESCRIPTION("Controlador de dispositivo de caracteres para manejo de led por GPIO (Lichee RV DOCK)");
