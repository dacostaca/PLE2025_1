#ifndef MEMINFO_MANIP_H
#define MEMINFO_MANIP_H

typedef struct {
    long total_phys_mem_mb;
    double phys_mem_usage_percentage;
    long total_swap_mem_mb;
    double swap_mem_usage_percentage;
} mem_stats_t;

void get_memory_usage(mem_stats_t *stats);

#endif // MEMINFO_MANIP_H
