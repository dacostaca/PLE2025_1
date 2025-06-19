# Directorio del kernel
KDIR := /lib/modules/$(shell uname -r)/build

# Directorio del proyecto
SRC_DIR := $(PWD)/src
BUILD_DIR := $(PWD)/build

# Nombre del módulo
obj-m := gpio_led_driver.o
gpio_led_driver-y := gpio_led_driver.o

# Regla por defecto
all:
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C $(KDIR) M=$(BUILD_DIR) SRC=$(SRC_DIR) modules

# Limpiar
clean:
	$(MAKE) -C $(KDIR) M=$(BUILD_DIR) clean
	rm -rf $(BUILD_DIR)

