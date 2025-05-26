#include "tui.h"
#include <ncurses.h> // Should be included by the user of this module if linking with ncurses

void init_tui(void) {
    initscr();            // Start ncurses mode
    cbreak();             // Disable line buffering, make chars available immediately
    noecho();             // Don't echo typed characters to the screen
    keypad(stdscr, TRUE); // Enable F-keys, arrow keys etc.
    nodelay(stdscr, TRUE); // Make getch() non-blocking
    curs_set(0);          // Make the cursor invisible
}

void end_tui(void) {
    curs_set(1);          // Make the cursor visible again
    endwin();             // Restore terminal to normal mode
}

void display_data(const cpu_stats_t *cpu, const mem_stats_t *mem) {
    if (!cpu || !mem) return;

    clear(); // Clear the screen on each update
    int row = 0;

    // Title
    attron(A_BOLD);
    mvprintw(row++, 0, "--- Raspberry Pi Resource Monitor ---");
    attroff(A_BOLD);
    row++; // Blank line

    // CPU Info
    mvprintw(row++, 0, "CPU Model    : %s", cpu->model_name);
    mvprintw(row++, 0, "Cores/Threads: %d", cpu->num_cores);
    row++; // Blank line

    attron(A_UNDERLINE);
    mvprintw(row++, 0, "CPU Usage per Core:");
    attroff(A_UNDERLINE);
    for (int i = 0; i < cpu->num_cores; ++i) {
        // Display usage, handle potential negative values from get_cpu_usage error indications
        if(cpu->cores[i].usage_percentage < 0) {
            mvprintw(row++, 2, "  Core %2d:  Error", i);
        } else {
            mvprintw(row++, 2, "  Core %2d: %6.2f%%", i, cpu->cores[i].usage_percentage);
        }
    }
    row++; // Blank line

    // Memory Info
    attron(A_UNDERLINE);
    mvprintw(row++, 0, "Memory Information:");
    attroff(A_UNDERLINE);
    mvprintw(row++, 2, "Physical Total : %6ld MB", mem->total_phys_mem_mb);
    mvprintw(row++, 2, "Physical Usage : %6.2f%%", mem->phys_mem_usage_percentage);
    mvprintw(row++, 2, "Swap Total     : %6ld MB", mem->total_swap_mem_mb);
    mvprintw(row++, 2, "Swap Usage     : %6.2f%%", mem->swap_mem_usage_percentage);
    row++; // Blank line

    // Instructions
    mvprintw(row++, 0, "Press 'q' to quit.");

    refresh(); // Update the physical screen with changes
}

int get_input_char(void) {
    return getch(); // Read a character (non-blocking due to nodelay)
}
