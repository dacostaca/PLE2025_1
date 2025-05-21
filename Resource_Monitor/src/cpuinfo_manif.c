#include "cpuinfo_manif.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Obtiene la información básica de la CPU desde /proc/cpuinfo
int get_cpu_info(CPUInfo* info) {
    FILE* file = fopen("/proc/cpuinfo", "r");
    if (!file) return -1;

    char line[256];
    int cores_counted = 0;
    int threads_counted = 0;

    // Variables para evitar sobrescribir el modelo o fabricante
    int model_set = 0;
    int vendor_set = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "vendor_id", 9) == 0 && !vendor_set) {
            sscanf(line, "vendor_id : %[^\n]", info->vendor_id);
            vendor_set = 1;
        } else if (strncmp(line, "model name", 10) == 0 && !model_set) {
            sscanf(line, "model name : %[^\n]", info->model_name);
            model_set = 1;
        } else if (strncmp(line, "cpu cores", 9) == 0) {
            int cores;
            sscanf(line, "cpu cores : %d", &cores);
            cores_counted = cores;
        } else if (strncmp(line, "processor", 9) == 0) {
            threads_counted++;  // Cuenta cada hilo lógico
        }
    }

    fclose(file);

    info->cores = cores_counted;
    info->threads = threads_counted;

    return 0;
}

// Retorna la cantidad total de hilos lógicos (núcleos visibles para el sistema)
int get_logical_thread_count() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

// Parsea /proc/stat para obtener los tiempos de CPU por cada hilo
int get_cpu_stats(CPUStat stats[], int count) {
    FILE* file = fopen("/proc/stat", "r");
    if (!file) return -1;

    char line[512];
    int cpu_index = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "cpu", 3) == 0 && line[3] >= '0' && line[3] <= '9') {
            if (cpu_index >= count) break;

            sscanf(line,
                "cpu%d %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                &cpu_index,
                &stats[cpu_index].user,
                &stats[cpu_index].nice,
                &stats[cpu_index].system,
                &stats[cpu_index].idle,
                &stats[cpu_index].iowait,
                &stats[cpu_index].irq,
                &stats[cpu_index].softirq,
                &stats[cpu_index].steal,
                &stats[cpu_index].guest,
                &stats[cpu_index].guest_nice
            );
        }
    }

    fclose(file);
    return 0;
}

// Calcula el uso del CPU entre dos lecturas consecutivas
double calculate_cpu_usage(const CPUStat* prev, const CPUStat* curr) {
    unsigned long long prev_idle = prev->idle + prev->iowait;
    unsigned long long curr_idle = curr->idle + curr->iowait;

    unsigned long long prev_non_idle = prev->user + prev->nice + prev->system +
                                       prev->irq + prev->softirq + prev->steal;
    unsigned long long curr_non_idle = curr->user + curr->nice + curr->system +
                                       curr->irq + curr->softirq + curr->steal;

    unsigned long long prev_total = prev_idle + prev_non_idle;
    unsigned long long curr_total = curr_idle + curr_non_idle;

    unsigned long long total_diff = curr_total - prev_total;
    unsigned long long idle_diff = curr_idle - prev_idle;

    if (total_diff == 0) return 0.0;

    return (double)(total_diff - idle_diff) * 100.0 / total_diff;
}
