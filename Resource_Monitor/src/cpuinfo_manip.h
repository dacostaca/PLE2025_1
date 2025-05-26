#ifndef CPUINFO_MANIP_H
#define CPUINFO_MANIP_H

#define MAX_CPU_NAME_LEN 256
#define MAX_CORES 16 // Suficiente para una RPi y la mayoría de los sistemas comunes

typedef struct {
    double usage_percentage;
    unsigned long long prev_idle_time;
    unsigned long long prev_total_time;
} cpu_core_info;

typedef struct {
    char model_name[MAX_CPU_NAME_LEN];
    int num_cores;
    cpu_core_info cores[MAX_CORES]; // Array estático para simplicidad
} cpu_stats_t;

void get_cpu_model_and_cores(cpu_stats_t *stats);
void get_cpu_usage(cpu_stats_t *stats);

#endif // CPUINFO_MANIP_H
