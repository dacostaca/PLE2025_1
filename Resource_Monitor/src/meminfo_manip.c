#include "meminfo_manip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para atol

// Helper function to parse a value from a line in /proc/meminfo
long parse_mem_value(const char* line_buffer, const char* key) {
    if (strncmp(line_buffer, key, strlen(key)) == 0) {
        const char *value_str = line_buffer + strlen(key);
        while (*value_str == ' ' || *value_str == '\t' || *value_str == ':') { // Skip spaces and colon
            value_str++;
        }
        return atol(value_str); // Extracts value in kB
    }
    return -1; // Key not found or error
}


void get_memory_usage(mem_stats_t *stats) {
    FILE *fp;
    char buffer[256];
    long mem_total_kb = -1, mem_free_kb = -1, buffers_kb = -1, cached_kb = -1, sreclaimable_kb = -1;
    long swap_total_kb = -1, swap_free_kb = -1;
    long mem_available_kb = -1;

    if (!stats) return;

    // Initialize stats to default/error values
    stats->total_phys_mem_mb = 0;
    stats->phys_mem_usage_percentage = 0.0;
    stats->total_swap_mem_mb = 0;
    stats->swap_mem_usage_percentage = 0.0;

    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Error opening /proc/meminfo");
        return;
    }

    long val;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if ((val = parse_mem_value(buffer, "MemTotal:")) != -1) mem_total_kb = val;
        else if ((val = parse_mem_value(buffer, "MemFree:")) != -1) mem_free_kb = val;
        else if ((val = parse_mem_value(buffer, "MemAvailable:")) != -1) mem_available_kb = val;
        else if ((val = parse_mem_value(buffer, "Buffers:")) != -1) buffers_kb = val;
        else if ((val = parse_mem_value(buffer, "Cached:")) != -1) cached_kb = val;
        else if ((val = parse_mem_value(buffer, "SReclaimable:")) != -1) sreclaimable_kb = val;
        else if ((val = parse_mem_value(buffer, "SwapTotal:")) != -1) swap_total_kb = val;
        else if ((val = parse_mem_value(buffer, "SwapFree:")) != -1) swap_free_kb = val;
    }
    fclose(fp);

    if (mem_total_kb != -1) {
        stats->total_phys_mem_mb = mem_total_kb / 1024; // Convert kB to MB
        long mem_used_kb;

        if (mem_available_kb != -1) { // Use MemAvailable if present (Kernel 3.14+)
            mem_used_kb = mem_total_kb - mem_available_kb;
        } else if (mem_free_kb != -1 && buffers_kb != -1 && cached_kb != -1 && sreclaimable_kb != -1) {
            // Fallback: MemUsed = MemTotal - (MemFree + Buffers + Cached + SReclaimable)
            // This is a common approximation for "used" memory from user perspective.
            mem_used_kb = mem_total_kb - (mem_free_kb + buffers_kb + cached_kb + sreclaimable_kb);
        } else if (mem_free_kb != -1 && buffers_kb != -1 && cached_kb != -1) {
             // Simpler fallback if SReclaimable is not found/parsed
            mem_used_kb = mem_total_kb - (mem_free_kb + buffers_kb + cached_kb);
        }
         else {
            // Cannot reliably determine used memory, report as 0% or error
            mem_used_kb = 0; 
        }
        
        if (mem_total_kb > 0) {
            stats->phys_mem_usage_percentage = ((double)mem_used_kb / mem_total_kb) * 100.0;
        } else {
            stats->phys_mem_usage_percentage = 0.0;
        }

    }

    if (swap_total_kb > 0) { // Check if swap is enabled and has size
        stats->total_swap_mem_mb = swap_total_kb / 1024;
        if (swap_free_kb != -1) {
            long swap_used_kb = swap_total_kb - swap_free_kb;
            stats->swap_mem_usage_percentage = ((double)swap_used_kb / swap_total_kb) * 100.0;
        } else {
            stats->swap_mem_usage_percentage = 0.0; // Cannot determine free swap
        }
    } else {
        stats->total_swap_mem_mb = 0;
        stats->swap_mem_usage_percentage = 0.0;
    }
}
