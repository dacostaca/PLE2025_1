#include "app.h"
#include "capture.h"
#include "utils.h"
#include "motion_engine.h"
#include "gpio.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define UMBRAL_MOVIMIENTO 1 // 1% de píxeles diferentes

static volatile sig_atomic_t running = 1;

void handle_signal(int sig) {
    running = 0;
}

static void* thread_captura(void* arg) {
    const char* frame_prev = "frames/frame_prev.jpg";
    const char* frame_curr = "frames/frame_curr.jpg";

    // Inicialmente, capturar dos frames
    if (access(frame_prev, F_OK) != 0) {
        // Si no existe el frame previo, capturar uno
        gpio_set(LED_CAPTURA, 1);
        capturar_frame(frame_prev);
        gpio_set(LED_CAPTURA, 0);
        sleep(1);
    }

    while (running) {
        gpio_set(LED_CAPTURA, 1);  // ENCENDER LED DE CAPTURA

        // Capturar nuevo frame
        if (capturar_frame(frame_curr) != 0) {
            fprintf(stderr, "[ERROR] Fallo en captura.\n");
        } else {
            printf("[INFO] Captura actualizada.\n");

            // Comparar con el frame anterior
            int mov = detectar_movimiento(frame_prev, frame_curr, UMBRAL_MOVIMIENTO);
            if (mov == 1) {
                printf("[ALERTA] Movimiento detectado!\n");
                gpio_set(LED_MOVIMIENTO, 1);
                sleep(1); // Encender LED por 1 segundo
                gpio_set(LED_MOVIMIENTO, 0);
            } else if (mov == 0) {
                printf("[INFO] Sin movimiento.\n");
            } else {
                fprintf(stderr, "[ERROR] Fallo en detección de movimiento.\n");
            }

            // Actualizar el frame anterior
            remove(frame_prev); // Eliminar el anterior
            rename(frame_curr, frame_prev); // El actual ahora es el anterior
        }

        gpio_set(LED_CAPTURA, 0);  // APAGAR LED DE CAPTURA
        sleep(1); // Esperar 1 segundo entre capturas
    }

    return NULL;
}

void app_run(void) {
    crear_directorio_si_no_existe("frames");
    crear_directorio_si_no_existe("logs");

    // Inicializar GPIOs
    gpio_init(LED_CAPTURA);
    gpio_init(LED_MOVIMIENTO);
    // Apagar LEDs inicialmente
    gpio_set(LED_CAPTURA, 0);
    gpio_set(LED_MOVIMIENTO, 0);

    // Configurar manejador de señales
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    pthread_t captura_tid;
    if (pthread_create(&captura_tid, NULL, thread_captura, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(captura_tid, NULL);

    // Apagar LEDs al salir
    gpio_set(LED_CAPTURA, 0);
    gpio_set(LED_MOVIMIENTO, 0);
}
