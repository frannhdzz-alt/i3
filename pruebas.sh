#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Error: Faltan argumentos."
    echo "Uso: $0 <0|1> [nombre_del_test]"
    exit 1
fi

MODE=$1
TEST_NAME=$2

if [ "$MODE" -ne 0 ] && [ "$MODE" -ne 1 ]; then
    echo "Error: El primer argumento debe ser 0 (ejecución normal) o 1 (valgrind)."
    exit 1
fi

ejecutar_test() {
    local target=$1
    echo "========================================"
    echo "Compilando: $target"
    echo "========================================"
    
    make "$target"

    if [ $? -ne 0 ]; then
        echo "Error de compilación en $target. Saltando ejecución."
        return
    fi

    echo "--- Ejecutando $target ---"
    
    if [ "$MODE" -eq 0 ]; then
        ./"$target"
    else
        valgrind --leak-check=full ./"$target"
    fi
    echo ""
}

if [ -n "$TEST_NAME" ]; then
    ejecutar_test "$TEST_NAME"
else
    echo "No se especificó un test concreto. Buscando todas las pruebas..."
    
    for file in src/*_test.c; do
        if [ -f "$file" ]; then
            base_name=$(basename "$file" .c)
            ejecutar_test "$base_name"
        fi
    done
fi