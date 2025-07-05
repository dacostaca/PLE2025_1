CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -pthread
BIN_DIR = bin

# Archivos del proyecto
CORE_SRC = core/motion_engine.c
TEST_SRC = tests/test_motion.c
TEST_BIN = $(BIN_DIR)/test_motion

.PHONY: all clean test

all:
	@echo "Usa 'make test' para ejecutar pruebas."

# Compilar y ejecutar pruebas unitarias
test: $(TEST_BIN)
	@echo "🧪 Ejecutando pruebas de motion_engine..."
	@./$(TEST_BIN)

# Compilar binario de pruebas
$(TEST_BIN): $(TEST_SRC) $(CORE_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Limpiar binarios
clean:
	@rm -rf $(BIN_DIR)
