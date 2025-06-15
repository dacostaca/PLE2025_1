// gpio_led_user.c – Aplicación de usuario para controlar el LED vía /dev/gpioled
// Hecho por Daniel Felipe Acosta Castro
// Última actualización: 15/06/2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/gpioled"

static void print_usage(const char *progname) {
    fprintf(stderr,
        "Uso: %s <comando>\n"
        "  on     – Enciende el LED\n"
        "  off    – Apaga el LED\n"
        "  state  – Consulta el estado del LED\n",
        progname);
}

int main(int argc, char *argv[]) {
    int fd;
    char buf;
    ssize_t ret;

    if (argc != 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "state") == 0) {
        fd = open(DEVICE_PATH, O_RDONLY);
    } else {
        fd = open(DEVICE_PATH, O_WRONLY);
    }

    if (fd < 0) {
        fprintf(stderr, "Error al abrir %s: %s\n", DEVICE_PATH, strerror(errno));
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "on") == 0) {
        buf = '1';
        ret = write(fd, &buf, 1);
        if (ret != 1) {
            fprintf(stderr, "Error al escribir 'on': %s\n", strerror(errno));
            close(fd);
            return EXIT_FAILURE;
        }
        printf("LED encendido.\n");

    } else if (strcmp(argv[1], "off") == 0) {
        buf = '0';
        ret = write(fd, &buf, 1);
        if (ret != 1) {
            fprintf(stderr, "Error al escribir 'off': %s\n", strerror(errno));
            close(fd);
            return EXIT_FAILURE;
        }
        printf("LED apagado.\n");

    } else if (strcmp(argv[1], "state") == 0) {
        ret = read(fd, &buf, 1);
        if (ret != 1) {
            fprintf(stderr, "Error al leer estado: %s\n", strerror(errno));
            close(fd);
            return EXIT_FAILURE;
        }
        printf("Estado del LED: %s\n", (buf == '1') ? "ON" : "OFF");

    } else {
        print_usage(argv[0]);
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}
