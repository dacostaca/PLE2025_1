#ifndef CPUINFO_MANIF_H
#define CPUINFO_MANIF_H

// Estructura que guarda información estática de la CPU
typedef struct {
    char model_name[128];  // Nombre del modelo de CPU
    char vendor_id[64];    // ID del fabricante
    int cores;             // Núcleos físicos
    int threads;           // Hilos (núcleos lógicos)
} CPUInfo;

// Estructura para guardar tiempos de CPU (usado para calcular % de uso)
typedef struct {
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
    unsigned long long guest;
    unsigned long long guest_nice;
} CPUStat;

// Función que obtiene la información estática de la CPU (modelo, fabricante, etc.)
int get_cpu_info(CPUInfo* info);

// Función que obtiene el número total de hilos lógicos
int get_logical_thread_count();

// Función que obtiene las estadísticas actuales de uso de CPU (una por hilo)
int get_cpu_stats(CPUStat stats[], int count);

// Función que calcula el porcentaje de uso entre dos lecturas
double calculate_cpu_usage(const CPUStat* prev, const CPUStat* curr);

#endif
