#include <stdio.h>
#include <assert.h>
#include "meminfo_manip.h" // Se espera que el Makefile maneje las rutas de inclusión

// Prueba básica: verifica que se obtienen datos de memoria sin crash.
void test_get_mem_info_basic() {
    printf("--- Running test_get_mem_info_basic ---\n");
    mem_stats_t stats;

    get_memory_usage(&stats);

    printf("Total Physical Memory: %ld MB\n", stats.total_phys_mem_mb);
    printf("Physical Memory Usage: %.2f%%\n", stats.phys_mem_usage_percentage);
    printf("Total Swap Memory: %ld MB\n", stats.total_swap_mem_mb);
    printf("Swap Memory Usage: %.2f%%\n", stats.swap_mem_usage_percentage);

    assert(stats.total_phys_mem_mb > 0); // Debe haber memoria física
    assert(stats.phys_mem_usage_percentage >= 0.0 && stats.phys_mem_usage_percentage <= 100.0);
    
    // El swap puede ser 0MB, lo cual es válido.
    assert(stats.total_swap_mem_mb >= 0);
    if (stats.total_swap_mem_mb > 0) {
        assert(stats.swap_mem_usage_percentage >= 0.0 && stats.swap_mem_usage_percentage <= 100.0);
    } else {
        assert(stats.swap_mem_usage_percentage == 0.0);
    }

    printf("test_get_mem_info_basic PASSED\n");
}

int main() {
    test_get_mem_info_basic();
    // Aquí se podrían añadir más funciones de prueba.
    return 0;
}
