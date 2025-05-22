#include "tui.h"
#include <stdio.h>
#include <termios.h>   // Para manipular configuración del terminal.
#include <unistd.h>    // Para STDIN_FILENO, read, etc.
#include <fcntl.h>     // Para configurar lectura no bloqueante.

static struct termios orig_termios;  // Guarda la configuración original del terminal.

// Desactiva el modo canónico (entrada por línea completa) y echo del terminal.
// Configura el stdin como no bloqueante (read no se queda esperando).
void tui_init() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

// Limpia la pantalla y muestra información formateada de CPU y memoria.
void tui_display(const CPUInfo* cpu, const MemInfo* mem) {
    printf("\033[H\033[J"); // Secuencia ANSI para limpiar la pantalla.
    printf("CPU: %s\n", cpu->cpu_model);
    printf("Núcleos físicos: %d | Hilos: %d\n", cpu->num_physical_cores, cpu->num_threads);
    
    for (int i = 0; i < cpu->num_threads; ++i) {
        printf("Hilo %d: %.2f%%\n", i, cpu->cpu_usages[i]);
    }

    printf("\nMemoria: %d MB usada / %d MB total\n", mem->used_mem_mb, mem->total_mem_mb);
    printf("Swap:    %d MB usada / %d MB total\n", mem->used_swap_mb, mem->total_swap_mb);
}

// Retorna 1 si el usuario presionó la tecla 'q', 0 en otro caso.
int tui_should_exit() {
    char ch;
    if (read(STDIN_FILENO, &ch, 1) > 0) {
        return (ch == 'q' || ch == 'Q');
    }
    return 0;
}

// Restaura la configuración original del terminal al salir.
void tui_cleanup() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
