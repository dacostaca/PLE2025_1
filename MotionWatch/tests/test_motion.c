#include "../core/motion_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "capture.h"

int main(void) {
    printf("========================================\n");
    printf("  PRUEBA DE DETECCIÓN DE MOVIMIENTO\n");
    printf("========================================\n\n");
    
    // Crear directorio de pruebas
    system("mkdir -p test_frames");
    
    // Paso 1: Capturar fondo estático
    printf("PASO 1: Capturando fondo estático\n");
    printf("Por favor, asegúrese que la cámara apunte a un fondo estático\n");
    printf("Capturando en 3 segundos...\n");
    sleep(3);
    capturar_frame("test_frames/background.jpg");
    printf("¡Captura completada!\n\n");
    
    // Paso 2: Capturar con movimiento
    printf("PASO 2: Capturando con movimiento\n");
    printf("Por favor, mueva un objeto frente a la cámara\n");
    printf("Capturando en 3 segundos...\n");
    sleep(3);
    capturar_frame("test_frames/movement.jpg");
    printf("¡Captura completada!\n\n");
    
    // Paso 3: Probar detección
    printf("PASO 3: Probando detección de movimiento\n");
    
    // Prueba 1: Misma imagen
    int r = detectar_movimiento("test_frames/background.jpg", "test_frames/background.jpg", 1);
    printf("Prueba imágenes iguales: %d (esperado 0)\n", r);
    assert(r == 0);
    
    // Prueba 2: Imágenes diferentes
    r = detectar_movimiento("test_frames/background.jpg", "test_frames/movement.jpg", 1);
    printf("Prueba imágenes diferentes: %d (esperado 1)\n", r);
    assert(r == 1);
    
    // Prueba 3: Archivos inexistentes
    r = detectar_movimiento("test_frames/no_existe.jpg", "test_frames/tampoco.jpg", 1);
    printf("Prueba imágenes inexistentes: %d (esperado -1)\n", r);
    assert(r == -1);
    
    printf("\n✅ Todas las pruebas pasaron correctamente!\n");
    
    // Limpiar (opcional)
    // system("rm -rf test_frames");
    
    return 0;
}
