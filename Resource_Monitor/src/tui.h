#ifndef TUI_H
#define TUI_H

#include "cpuinfo_manip.h"
#include "meminfo_manip.h"

void init_tui(void);
void end_tui(void);
void display_data(const cpu_stats_t *cpu, const mem_stats_t *mem);
int get_input_char(void);

#endif // TUI_H
