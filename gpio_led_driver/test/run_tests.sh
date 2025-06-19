#!/bin/bash

APP=../user_app/build/gpio_led_user
DEVICE=/dev/gpioled
RESULTS_DIR=results
LOGS_DIR=logs

mkdir -p "$RESULTS_DIR" "$LOGS_DIR"

# Contadores
pass=0
fail=0

log_test_result() {
    local name=$1
    local status=$2
    if [ "$status" -eq 0 ]; then
        echo "[✔] $name" | tee -a "$RESULTS_DIR/summary.txt"
        ((pass++))
    else
        echo "[✘] $name" | tee -a "$RESULTS_DIR/summary.txt"
        ((fail++))
    fi
}

run_test() {
    local name=$1
    shift
    echo "→ Ejecutando: $name"
    "$APP" "$@" > "$LOGS_DIR/$name.out" 2> "$LOGS_DIR/$name.err"
    local status=$?
    log_test_result "$name" "$status"
}

# Limpiar resultados anteriores
echo "== Iniciando pruebas ==" > "$RESULTS_DIR/summary.txt"

run_test "Encender_LED"     on
run_test "Consultar_LED_on" state
run_test "Apagar_LED"       off
run_test "Consultar_LED_off" state
run_test "Comando_invalido"  invalid_command

# Mostrar resumen
echo "============================"
echo "Pruebas exitosas: $pass" | tee -a "$RESULTS_DIR/summary.txt"
echo "Pruebas fallidas : $fail" | tee -a "$RESULTS_DIR/summary.txt"

exit $fail
