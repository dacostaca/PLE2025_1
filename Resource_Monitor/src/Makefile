# Resource_Monitor/src/Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.
OBJ_DIR = ../obj

# Lista de archivos fuente en src/
SRCS = cpuinfo_manip.c meminfo_manip.c tui.c resource_mon.c
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regla por defecto: compila todos los objetos definidos en SRCS
all: $(OBJS)

# Regla para compilar un archivo .c específico a .o en ../obj/
# Esto permite que el Makefile raíz llame, por ejemplo, 'make -C src cpuinfo_manip.o'
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR) # Crear el directorio obj si no existe
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los objetos generados por este Makefile
clean:
	rm -f $(OBJ_DIR)/cpuinfo_manip.o $(OBJ_DIR)/meminfo_manip.o $(OBJ_DIR)/tui.o $(OBJ_DIR)/resource_mon.o

.PHONY: all clean
