#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // For usleep()
#include <signal.h>   // For signal handling

#include "cpuinfo_manip.h"
#include "meminfo_manip.h"
#include "tui.h"

// Global flag to control the main loop, for signal handling
volatile sig_atomic_t keep_running = 1;

// Signal handler function for SIGINT (Ctrl+C)
void sigint_handler(int signal_num) {
    (void)signal_num; // Unused parameter
    keep_running = 0;
}

int main(void) {
    cpu_stats_t current_cpu_stats;
    mem_stats_t current_mem_stats;

    // Register the signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    // Initialize CPU static info (model, cores)
    get_cpu_model_and_cores(&current_cpu_stats);
    if (current_cpu_stats.num_cores == 0) {
        fprintf(stderr, "Error: Could not determine CPU information. Exiting.\n");
        return 1;
    }

    // Perform an initial CPU usage read to populate previous values.
    // The first displayed usage will be based on the delta from this initial read
    // to the first read inside the loop.
    get_cpu_usage(&current_cpu_stats); 
    // A small delay helps get a non-zero delta for the first proper reading if system is idle.
    // Or better, the first get_cpu_usage() inside the loop will calculate from this.
    // For simplicity, we assume the first display_data might show 0% if no activity.

    init_tui(); // Initialize ncurses

    int ch;
    while (keep_running) {
        ch = get_input_char(); // Check for user input
        if (ch == 'q' || ch == 'Q') {
            keep_running = 0;
        }

        // Get current CPU usage (calculates based on previous values)
        get_cpu_usage(&current_cpu_stats);

        // Get current memory usage
        get_memory_usage(&current_mem_stats);

        // Display all data
        display_data(&current_cpu_stats, &current_mem_stats);

        // Wait for 1 second (1,000,000 microseconds)
        usleep(1000000);
    }

    end_tui(); // Clean up ncurses
    printf("Resource_Monitor exited gracefully.\n");

    return 0;
}
