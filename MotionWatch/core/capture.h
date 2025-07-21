#ifndef CAPTURE_H
#define CAPTURE_H

/**
 * @brief Captura un frame de la cámara y lo guarda con timestamp.
 *
 * @param filename Nombre del archivo donde guardar el frame
 * @return 0 si fue exitoso, otro valor si hubo error.
 */
int capturar_frame(const char* filename);

#endif // CAPTURE_H
