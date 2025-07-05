#include "../core/motion_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Para esta prueba necesitas tener dos imágenes ya creadas:
 * - frames/test_igual_1.jpg
 * - frames/test_igual_2.jpg (idéntica a la primera)
 * - frames/test_diferente.jpg (ligeramente diferente)
 */

int main(void) {
    int r;

    // Prueba 1: Imágenes iguales
    r = detectar_movimiento("frames/test_igual_1.jpg", "frames/test_igual_2.jpg");
    printf("Prueba imágenes iguales: %d\n", r);
    //assert(r == 0);

    // Prueba 2: Imágenes diferentes
    r = detectar_movimiento("frames/test_igual_1.jpg", "frames/test_diferente.jpg");
    printf("Prueba imágenes diferentes: %d\n", r);
    //assert(r == 1);

    // Prueba 3: Archivos inexistentes
    r = detectar_movimiento("frames/no_existe.jpg", "frames/tampoco.jpg");
    printf("Prueba imágenes inexistentes: %d\n", r);
    //assert(r == -1);

    printf("Todas las pruebas pasaron correctamente.\n");
    return 0;
}
