// gpio_led_driver/include/gpio_led_driver.h

#ifndef GPIO_LED_DRIVER_H
#define GPIO_LED_DRIVER_H

#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>

#define DEVICE_NAME "gpioled"
#define CLASS_NAME "led"

// Prototipos de funciones
static int dev_open(struct inode *inodep, struct file *filep);
static int dev_release(struct inode *inodep, struct file *filep);
static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset);
static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset);

#endif  // GPIO_LED_DRIVER_H
