#ifndef TUI_H
#define TUI_H

// Estructura que representa la información de la CPU a mostrar en pantalla.
typedef struct {
    float cpu_usages[16];       // Porcentaje de uso por hilo (hasta 16 hilos).
    int num_threads;            // Número total de hilos.
    char cpu_model[128];        // Nombre del modelo de CPU.
    int num_cores;              // Número total de núcleos (puede incluir lógicos).
    int num_physical_cores;     // Número de núcleos físicos.
} CPUInfo;

// Estructura que representa la información de la memoria a mostrar en pantalla.
typedef struct {
    int total_mem_mb;           // Memoria física total (en MB).
    int used_mem_mb;            // Memoria física usada (en MB).
    int total_swap_mb;          // Memoria de intercambio total (en MB).
    int used_swap_mb;           // Memoria de intercambio usada (en MB).
} MemInfo;

// Inicializa la interfaz TUI, desactivando el modo canónico y echo del terminal.
void tui_init();

// Dibuja en pantalla toda la información de CPU y memoria recibida.
void tui_display(const CPUInfo* cpu_info, const MemInfo* mem_info);

// Captura si el usuario desea salir (tecla 'q').
int tui_should_exit();

// Restaura el estado original del terminal.
void tui_cleanup();

#endif

