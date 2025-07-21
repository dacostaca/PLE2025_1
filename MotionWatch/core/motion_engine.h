#ifndef MOTION_ENGINE_H
#define MOTION_ENGINE_H

/**
 * @brief Compara dos imágenes y detecta si hay movimiento.
 *
 * @param frame1 Ruta a la primera imagen.
 * @param frame2 Ruta a la segunda imagen.
 * @param umbral Umbral de diferencia para considerar movimiento (0-100)
 * @return 1 si se detecta movimiento, 0 si no, -1 en error.
 */
int detectar_movimiento(const char* frame1, const char* frame2, int umbral);

#endif // MOTION_ENGINE_H
