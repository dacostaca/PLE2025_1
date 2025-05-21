#ifndef MEMINFO_MANIF_H
#define MEMINFO_MANIF_H

// Estructura que contiene información de la memoria
typedef struct {
    unsigned long total_mem_mb;     // Memoria física total en MB
    unsigned long used_mem_mb;      // Memoria física usada en MB
    float used_mem_percent;         // Porcentaje de uso de la memoria física

    unsigned long total_swap_mb;    // Memoria swap total en MB
    unsigned long used_swap_mb;     // Memoria swap usada en MB
    float used_swap_percent;        // Porcentaje de uso de la memoria swap
} MemInfo;

// Función que obtiene la información de memoria y la guarda en la estructura
int get_mem_info(MemInfo* info);

#endif
