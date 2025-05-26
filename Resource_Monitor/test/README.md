# Carpeta de Pruebas (`test`)

Esta carpeta y su subcarpeta `src/` contienen el código fuente para las pruebas unitarias de los diferentes módulos del proyecto `resource_mon`.

## Contenido de `test/src/`

* `cpuinfo_test.c`: Pruebas para el módulo `cpuinfo_manip`.
* `meminfo_test.c`: Pruebas para el módulo `meminfo_manip`.
* `tui_test.c`: Pruebas (o stubs de prueba) para el módulo `tui`.
* `Makefile`: Define cómo compilar los archivos de prueba `.c` de esta carpeta a archivos objeto (`.o`) que se guardarán en la carpeta `../../obj/`.

## Compilación de Pruebas (desde `test/src/`)

* Al ejecutar `make` o `make all` en la carpeta `Resource_Monitor/test/src/`:
    Se generarán los archivos objeto (`.o`) para todos los archivos `.c` de prueba listados en el `Makefile` de esta carpeta. Estos `.o` se colocarán en `../../obj/`.
    Por ejemplo: `../../obj/cpuinfo_test.o`, `../../obj/meminfo_test.o`, `../../obj/tui_test.o`.

* Al ejecutar `make clean` en esta carpeta:
    Se borrarán los archivos `.o` de prueba generados por este `Makefile` de la carpeta `../../obj/`.

## Ejecución de Pruebas

Los ejecutables de prueba se construyen usando el `Makefile` principal en la raíz del proyecto (`make tests`) y se colocan en la carpeta `Resource_Monitor/bin/`.

Por ejemplo, para ejecutar la prueba de `cpuinfo`:
```bash
./bin/cpuinfo_test
