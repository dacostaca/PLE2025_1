#include <stdio.h>
#include "../../src/tui.h"
#include <unistd.h>  // Para sleep()

int main() {
    // Inicializa el terminal en modo no canónico.
    tui_init();

    // Crea datos simulados para la prueba.
    CPUInfo cpu = {
        .num_threads = 4,
        .num_physical_cores = 2,
        .cpu_usages = {30.0, 50.0, 10.0, 70.0}
    };
    snprintf(cpu.cpu_model, sizeof(cpu.cpu_model), "Lichee RV RISC-V");

    MemInfo mem = {
        .total_mem_mb = 512,
        .used_mem_mb = 256,
        .total_swap_mb = 128,
        .used_swap_mb = 64
    };

    // Muestra la información cada segundo hasta que el usuario presione 'q'.
    while (!tui_should_exit()) {
        tui_display(&cpu, &mem);
        sleep(1);
    }

    // Restaura la terminal antes de salir.
    tui_cleanup();
    return 0;
}
