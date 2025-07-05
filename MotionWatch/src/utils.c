#include "utils.h"
#include <sys/stat.h>
#include <stdio.h>

void crear_directorio_si_no_existe(const char* path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0755) != 0) {
            perror("mkdir");
        }
    }
}
