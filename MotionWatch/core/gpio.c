#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void gpio_init(int pin) {
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d", pin);
    
    // Verificar si ya está exportado
    if (access(path, F_OK) != 0) {
        // Exportar el pin
        FILE *export_file = fopen("/sys/class/gpio/export", "w");
        if (export_file) {
            fprintf(export_file, "%d", pin);
            fclose(export_file);
            usleep(100000); // Esperar 100ms
        } else {
            fprintf(stderr, "Error exportando GPIO %d: %s\n", pin, strerror(errno));
        }
    }

    // Configurar como salida
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    FILE *direction_file = fopen(path, "w");
    if (direction_file) {
        if (fprintf(direction_file, "out") < 0) {
            fprintf(stderr, "Error configurando dirección GPIO %d: %s\n", pin, strerror(errno));
        }
        fclose(direction_file);
    } else {
        fprintf(stderr, "Error abriendo dirección GPIO %d: %s\n", pin, strerror(errno));
    }
}

void gpio_set(int pin, int value) {
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    FILE *value_file = fopen(path, "w");
    if (value_file) {
        if (fprintf(value_file, "%d", value) < 0) {
            fprintf(stderr, "Error estableciendo valor GPIO %d: %s\n", pin, strerror(errno));
        }
        fclose(value_file);
    } else {
        fprintf(stderr, "Error abriendo valor GPIO %d: %s\n", pin, strerror(errno));
    }
}
