# Proyecto Resource Monitor (Raspberry Pi 3)

Este proyecto implementa un monitor de recursos en línea de comandos (`resource_mon`) para sistemas Linux, diseñado y probado para una placa de desarrollo Raspberry Pi 3. Muestra información en tiempo real sobre el uso de CPU (general y por núcleo/hilo) y memoria (física y de intercambio).

## Integrantes
*Edwin Efren Moran Goyes
`C.C.:` 1123333760
*Daniel Felipe Acosta Castro
`C.C.:` 1075309092
*Ivonne Tatiana Zapata Matínez
`C.C.:` 1002543377
*Diego Alejandro Arboleda Cuero
`C.C.:` 1087834596

## Descripción Funcional

`resource_mon` es una aplicación de terminal que:

* Muestra el nombre/fabricante de la CPU, el número de núcleos y el número de hilos.
* Muestra el porcentaje de uso individual de cada hilo (núcleo en la Raspberry Pi 3).
* Muestra la memoria física total instalada y su porcentaje de uso.
* Muestra la memoria de intercambio (swap) total instalada y su porcentaje de uso.
* Actualiza la información de uso de CPU cada segundo.
* La información se presenta en la misma posición de la pantalla, sin generar nuevas líneas para las actualizaciones (utilizando la biblioteca `ncurses`).
* El programa termina al presionar la tecla `q` o con `Ctrl+C`.

## Estructura del Proyecto

El proyecto está organizado en las siguientes carpetas principales:

* `src/`: Contiene el código fuente de la aplicación principal (`resource_mon.c`) y sus módulos (`cpuinfo_manip.c`, `meminfo_manip.c`, `tui.c`) junto con sus cabeceras (`.h`). También incluye un `Makefile` para compilar estos fuentes a archivos objeto.
* `test/src/`: Contiene el código fuente de las pruebas unitarias para los módulos. Incluye un `Makefile` para compilar las pruebas a archivos objeto.
* `obj/`: Carpeta donde se almacenan todos los archivos objeto (`.o`) generados durante la compilación. Es creada automáticamente por los `Makefile`.
* `bin/`: Carpeta donde se almacenan todos los ejecutables finales (la aplicación principal `resource_mon` y los ejecutables de prueba). Es creada automáticamente por el `Makefile` principal.
* `README.md`: Archivos de documentación en formato Markdown en la raíz, `src/` y `test/`.

## Compilación y Ejecución

Desde la carpeta raíz del proyecto (`Resource_Monitor/`):

* **Compilar todo (aplicación y pruebas):**
    ```bash
    make all
    ```
    o simplemente:
    ```bash
    make
    ```
* **Compilar solo la aplicación principal:**
    ```bash
    make resource_mon
    ```
* **Compilar solo las pruebas:**
    ```bash
    make tests
    ```
* **Ejecutar la aplicación principal:**
    ```bash
    ./bin/resource_mon
    ```
* **Ejecutar una prueba específica (ej. cpuinfo_test):**
    ```bash
    ./bin/cpuinfo_test
    ```
* **Limpiar archivos compilados (objetos y ejecutables):**
    ```bash
    make clean
    ```

## Requisitos de Software (para Raspberry Pi 3)

* GCC (GNU Compiler Collection)
* GNU Make
* Git
* libncurses-dev (Biblioteca Ncurses para desarrollo)

Estos pueden instalarse en Raspberry Pi OS con:
`sudo apt update && sudo apt install build-essential git libncurses-dev`
