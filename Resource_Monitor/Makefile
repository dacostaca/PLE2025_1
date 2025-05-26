# Resource_Monitor/Makefile (Principal)
CC = gcc
CFLAGS_LINK = -Wall
LDFLAGS = -lncurses

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_SRC_DIR = test/src

# --- Objetos para el programa principal ---
OBJS_APP = $(OBJ_DIR)/cpuinfo_manip.o $(OBJ_DIR)/meminfo_manip.o $(OBJ_DIR)/tui.o $(OBJ_DIR)/resource_mon.o
TARGET_APP = $(BIN_DIR)/resource_mon

# --- Objetos y Ejecutables para Pruebas ---
OBJ_TEST_CPU = $(OBJ_DIR)/cpuinfo_test.o
TARGET_TEST_CPU = $(BIN_DIR)/cpuinfo_test

OBJ_TEST_MEM = $(OBJ_DIR)/meminfo_test.o
TARGET_TEST_MEM = $(BIN_DIR)/meminfo_test

OBJ_TEST_TUI = $(OBJ_DIR)/tui_test.o
TARGET_TEST_TUI = $(BIN_DIR)/tui_test

# --- Reglas Principales ---
all: resource_mon tests

resource_mon: $(OBJS_APP)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS_LINK) $^ -o $(TARGET_APP) $(LDFLAGS)
	@echo "$(TARGET_APP) construido."

tests: $(TARGET_TEST_CPU) $(TARGET_TEST_MEM) $(TARGET_TEST_TUI)
	@echo "Todos los tests construidos en $(BIN_DIR)/"

# --- Reglas para construir tests individuales ---
$(TARGET_TEST_CPU): $(OBJ_TEST_CPU) $(OBJ_DIR)/cpuinfo_manip.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS_LINK) $^ -o $@
	@echo "$(TARGET_TEST_CPU) construido."

$(TARGET_TEST_MEM): $(OBJ_TEST_MEM) $(OBJ_DIR)/meminfo_manip.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS_LINK) $^ -o $@
	@echo "$(TARGET_TEST_MEM) construido."

$(TARGET_TEST_TUI): $(OBJ_TEST_TUI) $(OBJ_DIR)/tui.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS_LINK) $^ -o $@ $(LDFLAGS)
	@echo "$(TARGET_TEST_TUI) construido."

# --- Dependencias para asegurar que los .o se construyan antes de enlazar ---
# Si los .o no existen, intenta construirlos ejecutando make en sus respectivos directorios.
# Esta regla asegura que el Makefile del subdirectorio correspondiente sea invocado para crear el .o
$(OBJ_DIR)/%.o:
	@if echo $@ | grep -qE 'cpuinfo_manip.o|meminfo_manip.o|tui.o|resource_mon.o'; then \
		$(MAKE) -C $(SRC_DIR) $(notdir $@); \
	elif echo $@ | grep -qE 'cpuinfo_test.o|meminfo_test.o|tui_test.o'; then \
		$(MAKE) -C $(TEST_SRC_DIR) $(notdir $@); \
	else \
		echo "Error: No rule to make target `$@` from this Makefile. Object should be in $(OBJ_DIR)"; \
	fi

# --- Limpieza ---
clean:
	@echo "Limpiando archivos compilados..."
	rm -rf $(BIN_DIR)/*
	rm -rf $(OBJ_DIR)/*
	@echo "Limpieza completa."

.PHONY: all resource_mon tests clean
