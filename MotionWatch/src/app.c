#include "app.h"
#include "capture.h"
#include "utils.h"
#include "motion_engine.h"
#include "gpio.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LED_CAPTURA 112
#define LED_MOVIMIENTO 118

static void* thread_captura(void* arg) {
    const char* frame1 = "frames/frame_prev.jpg";
    const char* frame2 = "frames/frame_curr.jpg";

    while (1) {
        gpio_set(LED_CAPTURA, 1);  // ENCENDER LED DE CAPTURA
        rename(frame2, frame1);    // Mover la última captura anterior

        if (capturar_frame() != 0) {
            fprintf(stderr, "[ERROR] Fallo en captura.\n");
        } else {
            rename("frames/last.jpg", frame2);
            printf("[INFO] Captura actualizada.\n");

            if (access(frame1, F_OK) == 0) {
                int mov = detectar_movimiento(frame1, frame2);
                if (mov == 1) {
                    printf("[ALERTA] Movimiento detectado!\n");
                    gpio_set(LED_MOVIMIENTO, 1);
                    sleep(1); // Encender LED por 1 segundo
                    gpio_set(LED_MOVIMIENTO, 0);
                } else {
                    printf("[INFO] Sin movimiento.\n");
                }
            }
        }

        gpio_set(LED_CAPTURA, 0);  // APAGAR LED DE CAPTURA
        sleep(1);
    }

    return NULL;
}

void app_run(void) {
    crear_directorio_si_no_existe("frames");
    crear_directorio_si_no_existe("logs");

    gpio_init(LED_CAPTURA);
    gpio_init(LED_MOVIMIENTO);

    pthread_t captura_tid;
    if (pthread_create(&captura_tid, NULL, thread_captura, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(captura_tid, NULL);
}
