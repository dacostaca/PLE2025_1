# Carpeta Fuente (`src`)

Esta carpeta contiene el código fuente principal del proyecto `resource_mon` y los módulos que utiliza.

## Contenido

* `cpuinfo_manip.h` y `cpuinfo_manip.c`: Módulo para obtener y procesar información de la CPU (modelo, núcleos, uso por núcleo). Lee de `/proc/cpuinfo` y `/proc/stat`.
* `meminfo_manip.h` y `meminfo_manip.c`: Módulo para obtener y procesar información de la memoria (física y swap, total y usada). Lee de `/proc/meminfo`.
* `tui.h` y `tui.c`: Módulo de Interfaz de Usuario en Texto. Utiliza `ncurses` para mostrar la información en la terminal de forma organizada y permitir actualizaciones en el mismo lugar.
* `resource_mon.c`: Archivo principal del programa. Contiene la función `main`, inicializa los módulos, y maneja el bucle principal de actualización y visualización de datos, así como la entrada del usuario para salir.
* `Makefile`: Define cómo compilar los archivos `.c` de esta carpeta a archivos objeto (`.o`) que se guardarán en la carpeta `../obj/`.

## Compilación (desde esta carpeta `src/`)

* Al ejecutar `make` o `make all` en esta carpeta (`Resource_Monitor/src/`):
    Se generarán los archivos objeto (`.o`) para todos los archivos `.c` listados en el `Makefile` de esta carpeta. Estos `.o` se colocarán en `../obj/`.
    Por ejemplo: `../obj/cpuinfo_manip.o`, `../obj/meminfo_manip.o`, `../obj/tui.o`, `../obj/resource_mon.o`.

* Al ejecutar `make clean` en esta carpeta:
    Se borrarán los archivos `.o` generados por este `Makefile` de la carpeta `../obj/`.

## Descripción Detallada de Módulos

### `cpuinfo_manip`
* **Estructuras:**
    * `cpu_core_info`: Almacena el porcentaje de uso (`usage_percentage`) y los tiempos brutos previos (`prev_idle_time`, `prev_total_time`) necesarios para calcular el uso de un núcleo/hilo específico.
    * `cpu_stats_t`: Agrupa la información general de la CPU: `model_name` (cadena de caracteres), `num_cores` (entero), y un array de `cpu_core_info` para cada núcleo/hilo (hasta `MAX_CORES`).
* **Funciones:**
    * `void get_cpu_model_and_cores(cpu_stats_t *stats)`: Parámetro: puntero a `cpu_stats_t`. Lee `/proc/cpuinfo` para obtener el nombre del modelo de la CPU y el número de procesadores (núcleos/hilos). Inicializa los campos correspondientes en la estructura `stats`, incluyendo los tiempos previos para el cálculo de uso.
    * `void get_cpu_usage(cpu_stats_t *stats)`: Parámetro: puntero a `cpu_stats_t`. Lee `/proc/stat` para obtener los tiempos de actividad de cada núcleo/hilo. Calcula el porcentaje de uso para cada uno comparando con los valores previos almacenados en `stats` y actualiza el campo `usage_percentage` para cada núcleo en la estructura `stats`. También actualiza los valores de `prev_idle_time` y `prev_total_time` para el siguiente cálculo.

### `meminfo_manip`
* **Estructuras:**
    * `mem_stats_t`: Almacena la información de memoria: `total_phys_mem_mb` (long), `phys_mem_usage_percentage` (double), `total_swap_mem_mb` (long), `swap_mem_usage_percentage` (double).
* **Funciones:**
    * `void get_memory_usage(mem_stats_t *stats)`: Parámetro: puntero a `mem_stats_t`. Lee `/proc/meminfo` para obtener los valores de memoria total, libre, buffers, cached, swap total y swap libre. Calcula la memoria física usada y el porcentaje de uso. Calcula la memoria swap usada y su porcentaje de uso. Actualiza todos los campos en la estructura `stats`. Las unidades de memoria total se convierten a MB.

### `tui`
* **Funciones:**
    * `void init_tui()`: Sin parámetros. Inicializa el modo `ncurses` (configura la terminal para `cbreak`, `noecho`, `keypad`, `nodelay`, oculta cursor).
    * `void end_tui()`: Sin parámetros. Restaura la configuración original de la terminal antes de salir del modo `ncurses`.
    * `void display_data(const cpu_stats_t *cpu, const mem_stats_t *mem)`: Parámetros: puntero constante a `cpu_stats_t` y puntero constante a `mem_stats_t`. Limpia la pantalla (`clear()`) y utiliza funciones de `ncurses` como `mvprintw()` para mostrar toda la información de CPU y memoria en posiciones fijas de la pantalla. Llama a `refresh()` para actualizar la pantalla física.
    * `int get_input_char()`: Sin parámetros. Utiliza `getch()` de `ncurses` para leer un carácter del teclado de forma no bloqueante. Retorna el carácter leído o `ERR` si no hay entrada.

### `resource_mon.c`
* Contiene la función `main(void)`.
* Proporciona la lógica principal del programa:
    1.  Configura un manejador de señales para `SIGINT` (Ctrl+C) para permitir una salida controlada.
    2.  Llama a `get_cpu_model_and_cores()` para obtener información estática de la CPU.
    3.  Realiza una lectura inicial de `get_cpu_usage()` para establecer los valores base.
    4.  Llama a `init_tui()` para configurar la interfaz de ncurses.
    5.  Entra en un bucle principal que se ejecuta mientras `keep_running` sea verdadero:
        a.  Procesa la entrada del teclado (`get_input_char()`), si es 'q', establece `keep_running` a falso.
        b.  Llama a `get_cpu_usage()` para actualizar los datos de uso de CPU.
        c.  Llama a `get_memory_usage()` para actualizar los datos de memoria.
        d.  Llama a `display_data()` para mostrar la información actualizada.
        e.  Espera 1 segundo usando `usleep(1000000)`.
    6.  Al salir del bucle, llama a `end_tui()` para restaurar la terminal.
    7.  Imprime un mensaje de salida y termina.
