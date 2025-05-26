#include <stdio.h>
#include <assert.h>
#include <unistd.h> // Para usleep
#include "tui.h"       // Para init_tui, end_tui, display_data
#include "cpuinfo_manip.h" // Para la estructura cpu_stats_t
#include "meminfo_manip.h" // Para la estructura mem_stats_t

// Prueba básica del ciclo de vida de la TUI y visualización de datos mock.
void test_tui_lifecycle_and_display() {
    printf("--- Running test_tui_lifecycle_and_display ---\n");
    printf("Este test mostrará una pantalla ncurses por 2 segundos.\n");
    
    init_tui();

    // Crear datos mock para display_data
    cpu_stats_t mock_cpu_stats;
    mem_stats_t mock_mem_stats;

    // Llenar mock_cpu_stats
    snprintf(mock_cpu_stats.model_name, MAX_CPU_NAME_LEN, "Test CPU X-Series");
    mock_cpu_stats.num_cores = 2;
    mock_cpu_stats.cores[0].usage_percentage = 25.50;
    mock_cpu_stats.cores[1].usage_percentage = 75.15;

    // Llenar mock_mem_stats
    mock_mem_stats.total_phys_mem_mb = 4096;
    mock_mem_stats.phys_mem_usage_percentage = 50.75;
    mock_mem_stats.total_swap_mem_mb = 1024;
    mock_mem_stats.swap_mem_usage_percentage = 10.20;

    attron(A_BOLD);
    mvprintw(0, 0, "--- TUI Test Screen ---");
    attroff(A_BOLD);
    display_data(&mock_cpu_stats, &mock_mem_stats); // Mostrar datos mock
    mvprintw(15, 0, "TUI Test: Mostrando datos mock. Cerrando en 2 segundos...");
    refresh();
    
    usleep(2000000); // Mantener la pantalla por 2 segundos

    end_tui();
    
    // Después de end_tui(), la salida printf normal debería funcionar.
    printf("\ntest_tui_lifecycle_and_display: ncurses finalizado. Si viste la pantalla, el test es PASSED.\n");
}

int main() {
    test_tui_lifecycle_and_display();
    // No se pueden usar asserts directos para la salida visual de ncurses fácilmente,
    // pero se verifica que el ciclo init/end no crashea.
    return 0;
}
