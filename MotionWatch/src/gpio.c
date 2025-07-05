#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void gpio_init(int pin) {
    char path[64];
    FILE *f = fopen("/sys/class/gpio/export", "w");
    if (f) {
        fprintf(f, "%d", pin);
        fclose(f);
    }
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    f = fopen(path, "w");
    if (f) {
        fputs("out", f);
        fclose(f);
    }
}

void gpio_set(int pin, int value) {
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    FILE *f = fopen(path, "w");
    if (f) {
        fprintf(f, "%d", value);
        fclose(f);
    }
}
