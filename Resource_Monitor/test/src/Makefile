# Resource_Monitor/test/src/Makefile
CC = gcc
# -I../../src to find headers like cpuinfo_manip.h
# -I. for any local test headers
CFLAGS = -Wall -Wextra -std=c11 -I. -I../../src
OBJ_DIR = ../../obj

# Lista de archivos fuente de prueba
SRCS_TEST = cpuinfo_test.c meminfo_test.c tui_test.c
OBJS_TEST = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_TEST))

# Regla por defecto: compila todos los objetos de test
all: $(OBJS_TEST)

# Regla para compilar un archivo .c de test específico a .o en ../../obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los objetos generados por este Makefile
clean:
	rm -f $(OBJ_DIR)/cpuinfo_test.o $(OBJ_DIR)/meminfo_test.o $(OBJ_DIR)/tui_test.o

.PHONY: all clean
