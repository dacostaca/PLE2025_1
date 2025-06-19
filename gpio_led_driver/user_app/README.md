# Aplicación de Usuario para Controlar LED GPIO

## Descripción

Esta aplicación en C permite al usuario controlar el LED manejado por el módulo de kernel a través del archivo `/dev/gpioled`. El programa ofrece tres comandos: `on`, `off` y `state`.

## Estructura

- `src/gpio_led_user.c`: Código fuente principal.
- `include/gpio_led_user.h`: Declaraciones comunes.
- `build/`: Contiene el ejecutable generado.
- `Makefile`: Automatiza la compilación y organización de archivos.

## Compilación

Desde la carpeta `user_app/`, ejecuta:

```bash
make
```
El binario `gpio_led_user` se ubicará en `build/`.

## Uso
Aegúrate de haber cargado el módulo y creado el archivo `/dev/gpioled`.
```bash
./build/gpio_led_user on	# Enciende el LED
./build/gpio_led_user off 	# Apaga el LED
./build/gpio_led_user state	# Muestra el estado del LED
```

## Notas

- Verifica que el archivo `/dev/gpioled` exista y tenga permisos de escritura/lectura.
- Requiere el módulo cargado correctamente para funcionar
