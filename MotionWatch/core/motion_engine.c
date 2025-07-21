#include "motion_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <math.h>

// Función para leer una imagen JPEG
static int read_jpeg(const char *filename, unsigned char **image, int *width, int *height) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;

    if ((infile = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "No se puede abrir %s\n", filename);
        return -1;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;
    int channels = cinfo.output_components;

    // Alojar memoria para la imagen
    *image = (unsigned char*) malloc(*width * *height * channels);
    unsigned char *rowptr = *image;
    
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, &rowptr, 1);
        rowptr += *width * channels;
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return channels;
}

int detectar_movimiento(const char* frame1, const char* frame2, int umbral) {
    unsigned char *img1 = NULL, *img2 = NULL;
    int width1, height1, width2, height2;
    int channels1, channels2;

    // Leer la primera imagen
    channels1 = read_jpeg(frame1, &img1, &width1, &height1);
    if (channels1 < 0) {
        return -1;
    }

    // Leer la segunda imagen
    channels2 = read_jpeg(frame2, &img2, &width2, &height2);
    if (channels2 < 0) {
        free(img1);
        return -1;
    }

    // Comprobar que las dimensiones son iguales
    if (width1 != width2 || height1 != height2 || channels1 != channels2) {
        free(img1);
        free(img2);
        fprintf(stderr, "Las imágenes tienen dimensiones o canales diferentes\n");
        return -1;
    }

    int width = width1;
    int height = height1;
    int channels = channels1;
    int total_pixels = width * height;
    int diff_pixels = 0;

    // Umbral de diferencia en valor absoluto para considerar un píxel diferente
    const int THRESHOLD = 30; // en cada canal

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * channels;
            int diff = 0;
            for (int c = 0; c < channels; c++) {
                int pixel1 = img1[index + c];
                int pixel2 = img2[index + c];
                diff += abs(pixel1 - pixel2);
            }
            // Si la diferencia promedio por canal supera el umbral, cuenta como diferente
            if (diff / channels > THRESHOLD) {
                diff_pixels++;
            }
        }
    }

    free(img1);
    free(img2);

    // Calcular el porcentaje de píxeles diferentes
    double porcentaje = (double)diff_pixels / total_pixels * 100.0;
    printf("Porcentaje de píxeles diferentes: %.2f%%\n", porcentaje);

    if (porcentaje > umbral) {
        return 1; // Movimiento detectado
    } else {
        return 0; // Sin movimiento
    }
}
