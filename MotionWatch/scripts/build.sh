#!/bin/bash

# Cambiar al directorio del proyecto
cd "$(dirname "$0")/.."

# Crear directorios necesarios
mkdir -p bin frames logs

# Limpiar compilaciones anteriores
make clean

# Compilar
make all

# Dar permisos de ejecución
chmod +x bin/*
