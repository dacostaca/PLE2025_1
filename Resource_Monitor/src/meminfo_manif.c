#include "meminfo_manif.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Esta función lee el archivo /proc/meminfo y extrae los valores necesarios
int get_mem_info(MemInfo* info) {
    FILE* file = fopen("/proc/meminfo", "r");
    if (!file) return -1;

    char line[256];

    unsigned long mem_total_kb = 0;
    unsigned long mem_free_kb = 0;
    unsigned long buffers_kb = 0;
    unsigned long cached_kb = 0;
    unsigned long sreclaimable_kb = 0;
    unsigned long shmem_kb = 0;

    unsigned long swap_total_kb = 0;
    unsigned long swap_free_kb = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %lu kB", &mem_total_kb) == 1) continue;
        if (sscanf(line, "MemFree: %lu kB", &mem_free_kb) == 1) continue;
        if (sscanf(line, "Buffers: %lu kB", &buffers_kb) == 1) continue;
        if (sscanf(line, "Cached: %lu kB", &cached_kb) == 1) continue;
        if (sscanf(line, "SReclaimable: %lu kB", &sreclaimable_kb) == 1) continue;
        if (sscanf(line, "Shmem: %lu kB", &shmem_kb) == 1) continue;

        if (sscanf(line, "SwapTotal: %lu kB", &swap_total_kb) == 1) continue;
        if (sscanf(line, "SwapFree: %lu kB", &swap_free_kb) == 1) continue;
    }

    fclose(file);

    // Cálculo de memoria usada
    unsigned long mem_available_kb = mem_free_kb + buffers_kb + cached_kb + sreclaimable_kb - shmem_kb;
    unsigned long mem_used_kb = mem_total_kb - mem_available_kb;

    info->total_mem_mb = mem_total_kb / 1024;
    info->used_mem_mb = mem_used_kb / 1024;
    info->used_mem_percent = (float)mem_used_kb * 100.0f / mem_total_kb;

    // Cálculo de swap usada
    unsigned long swap_used_kb = swap_total_kb - swap_free_kb;
    info->total_swap_mb = swap_total_kb / 1024;
    info->used_swap_mb = swap_used_kb / 1024;
    info->used_swap_percent = (swap_total_kb == 0) ? 0.0f :
                              (float)swap_used_kb * 100.0f / swap_total_kb;

    return 0;
}
