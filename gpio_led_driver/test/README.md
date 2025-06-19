# Pruebas Automatizadas para el Controlador LED GPIO

## Descripción

Este directorio contiene herramientas y scripts automatizados para probar la funcionalidad del módulo del kernel y su correspondiente aplicación de usuario.

## Estructura

- `run_tests.sh`: Script principal que automatiza todas las pruebas.
- `results/`: Archivos con los resultados de las pruebas.
- `logs/`: Archivos de salida estándar y de error para cada prueba.
- `assert.sh`: Funciones auxiliares para validación (si se desea ampliar).

## Pruebas Incluidas

1. Encender el LED (`on`)
2. Apagar el LED (`off`)
3. Leer el estado (`state`)
4. Validar comportamiento ante comandos inválidos
5. Probar errores si el módulo no está cargado

## Ejecución de las pruebas

```bash
chmod +x run_tests.sh
./run_tests.sh
```

se generarán resultados en `results/` y detalles de ejecución en `logs/`.

## Requisitos

- Haber compilado y cargado el módulo (`gpio_led_driver.ko`).
- Tener creado el dispositivo `/dev/gpioled`.
- Tener la app de usuario `gpio_led_user` compilada.

## Notas

Puedes extender el script para incluir pruebas de rendimiento, estrés o integración.

