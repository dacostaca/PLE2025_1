```c
#include <stdio.h>
#include <assert.h>
#include <string.h> // Para strcmp
#include "cpuinfo_manip.h" // Se espera que el Makefile maneje las rutas de inclusión

// Prueba básica: verifica que se obtienen datos y se calcula el uso sin crash.
void test_get_cpu_info_basic() {
    printf("--- Running test_get_cpu_info_basic ---\n");
    cpu_stats_t stats;

    get_cpu_model_and_cores(&stats);
    printf("CPU Model: %s\n", stats.model_name);
    printf("Num Cores: %d\n", stats.num_cores);

    assert(stats.num_cores > 0 && stats.num_cores <= MAX_CORES); // Debe haber al menos un core
    assert(strlen(stats.model_name) > 0 && strcmp(stats.model_name, "N/A") != 0); // Debe obtener un nombre de modelo

    // Primera llamada para inicializar prev_times
    get_cpu_usage(&stats); 
    // En una prueba real, podríamos necesitar un sleep o mockear /proc/stat para un delta.
    // Por ahora, solo verificamos que no crashea y los porcentajes son plausibles.
    printf("Initial CPU Usage (Core 0): %.2f%%\n", stats.cores[0].usage_percentage);

    // Segunda llamada para ver un posible delta (aunque en un test rápido puede ser 0)
    // usleep(100000); // Opcional: esperar un poco para que haya un cambio de estado
    get_cpu_usage(&stats);
    for (int i = 0; i < stats.num_cores; ++i) {
        printf("CPU Usage (Core %d): %.2f%%\n", i, stats.cores[i].usage_percentage);
        assert(stats.cores[i].usage_percentage >= 0.0 && stats.cores[i].usage_percentage <= 100.0);
    }
    printf("test_get_cpu_info_basic PASSED\n");
}

int main() {
    test_get_cpu_info_basic();
    // Aquí se podrían añadir más funciones de prueba.
    return 0;
}
