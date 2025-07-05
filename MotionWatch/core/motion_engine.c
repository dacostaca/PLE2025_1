#include "motion_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int detectar_movimiento(const char* frame1, const char* frame2) {

    if (access("/dev/video0", R_OK | W_OK) != 0) {
        fprintf(stderr, "No se puede acceder a la cámara (/dev/video0): %s\n", strerror(errno));
        return -1;
    }
    char cmd[512];
    snprintf(cmd, sizeof(cmd),
        "ffmpeg -i %s -i %s -filter_complex \"blend=difference:shortest=1,blackframe=10:10\" -f null - 2>&1 | grep -q 'blackframe:'",
        frame1, frame2);

    int result = system(cmd);

    if (result == 0) {
        // Se encontró diferencia suficiente (movimiento)
        return 1;
    } else if (result == 256) {
        // No se detectó cambio significativo
        return 0;
    } else {
        // Error al ejecutar ffmpeg o comando inválido
        return -1;
    }
}
