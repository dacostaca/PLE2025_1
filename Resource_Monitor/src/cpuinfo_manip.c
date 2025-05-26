#include "cpuinfo_manip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para strtoull

void get_cpu_model_and_cores(cpu_stats_t *stats) {
    FILE *fp;
    char buffer[1024];
    int core_count = 0;
    int model_name_found = 0;

    if (!stats) return;

    strncpy(stats->model_name, "N/A", MAX_CPU_NAME_LEN -1);
    stats->model_name[MAX_CPU_NAME_LEN-1] = '\0';
    stats->num_cores = 0;

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        perror("Error opening /proc/cpuinfo");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (!model_name_found && (strncmp(buffer, "model name", 10) == 0 || strncmp(buffer, "Processor", 9) == 0 || strncmp(buffer, "Hardware", 8) == 0) ) {
            char *model = strchr(buffer, ':');
            if (model && *(++model)) {
                while (*model == ' ' || *model == '\t') model++; // Skip leading spaces
                char *newline = strchr(model, '\n');
                if (newline) *newline = '\0'; // Remove trailing newline
                strncpy(stats->model_name, model, MAX_CPU_NAME_LEN -1);
                stats->model_name[MAX_CPU_NAME_LEN-1] = '\0';
                model_name_found = 1;
            }
        }
        if (strncmp(buffer, "processor", 9) == 0) {
            core_count++;
        }
    }
    fclose(fp);

    stats->num_cores = (core_count > 0 && core_count <= MAX_CORES) ? core_count : (core_count > MAX_CORES ? MAX_CORES : 1);

    for(int i=0; i < stats->num_cores; ++i) {
        stats->cores[i].prev_idle_time = 0;
        stats->cores[i].prev_total_time = 0;
        stats->cores[i].usage_percentage = 0.0;
    }
}

void get_cpu_usage(cpu_stats_t *stats) {
    FILE *fp;
    char buffer[1024];
    unsigned long long user, nice, system_time, idle, iowait, irq, softirq, steal, guest, guest_nice;
    unsigned long long current_idle_time, current_total_time;
    unsigned long long total_delta, idle_delta;

    if (!stats || stats->num_cores == 0) return;

    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Error opening /proc/stat");
        for(int i=0; i<stats->num_cores; ++i) stats->cores[i].usage_percentage = -1.0; // Indicate error
        return;
    }

    // Skip the aggregate "cpu" line
    if(fgets(buffer, sizeof(buffer), fp) == NULL) {
        fclose(fp);
        return;
    }

    for (int core_id_iter = 0; core_id_iter < stats->num_cores; ++core_id_iter) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL) { // Read line for cpuX
            // Not enough cpu lines, fill remaining with error/stale data
            for(int j=core_id_iter; j<stats->num_cores; ++j) stats->cores[j].usage_percentage = -2.0; // Indicate missing data
            break; 
        }

        int core_id_file; // To store the core ID read from the file, e.g., from "cpu0", "cpu1"
        // Example line: cpu0 12345 678 91011 121314 1516 17 18 0 0 0
        if (sscanf(buffer, "cpu%d %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                   &core_id_file, &user, &nice, &system_time, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 11) {
            
            if (core_id_file >= 0 && core_id_file < stats->num_cores) { // Ensure core_id_file is a valid index
                current_idle_time = idle + iowait;
                current_total_time = user + nice + system_time + idle + iowait + irq + softirq + steal;
                // guest and guest_nice are already part of user and nice in kernel >= 2.6.24 / 2.6.33

                if (stats->cores[core_id_file].prev_total_time > 0) { // Avoid division by zero and ensure previous data exists
                    total_delta = current_total_time - stats->cores[core_id_file].prev_total_time;
                    idle_delta = current_idle_time - stats->cores[core_id_file].prev_idle_time;

                    if (total_delta > 0) {
                        stats->cores[core_id_file].usage_percentage = ((double)(total_delta - idle_delta) / (double)total_delta) * 100.0;
                        if (stats->cores[core_id_file].usage_percentage < 0.0) stats->cores[core_id_file].usage_percentage = 0.0; // Cap at 0
                        if (stats->cores[core_id_file].usage_percentage > 100.0) stats->cores[core_id_file].usage_percentage = 100.0; // Cap at 100
                    } else {
                        stats->cores[core_id_file].usage_percentage = 0.0; 
                    }
                } else {
                     // First pass, set usage to 0 or undefined, and store current times for next calculation
                     stats->cores[core_id_file].usage_percentage = 0.0;
                }
                stats->cores[core_id_file].prev_idle_time = current_idle_time;
                stats->cores[core_id_file].prev_total_time = current_total_time;
            }
        } else {
             // Line format did not match, mark as error for this core
             if (core_id_iter < stats->num_cores) stats->cores[core_id_iter].usage_percentage = -3.0; // Indicate parsing error
        }
    }
    fclose(fp);
}
