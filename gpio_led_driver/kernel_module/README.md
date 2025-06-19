# Kernel Module – gpio_led_driver

Este módulo del kernel implementa un controlador de dispositivo de caracteres para controlar un LED conectado a un pin GPIO en la plataforma Lichee RV Dock. Proporciona una interfaz en `/dev/gpioled` para interactuar con el LED desde el espacio de usuario.

## Archivos Principales

| Archivo                | Descripción                                                      |
|------------------------|------------------------------------------------------------------|
| `Makefile`             | Reglas para compilar el módulo del kernel.                      |
| `src/gpio_led_driver.c`| Código fuente principal del módulo.                             |
| `include/gpio_led_driver.h` | Encabezado del módulo con definiciones y prototipos.         |
| `build/`               | Carpeta generada que contiene archivos de compilación como `.ko`|

---

## Funcionalidad

El módulo:

- Solicita un GPIO (por defecto `gpioPin=112`).
- Registra un dispositivo de caracteres con número mayor dinámico.
- Implementa las operaciones estándar:
  - `open()`
  - `release()`
  - `read()` – Devuelve `'1'` si el LED está encendido o `'0'` si está apagado.
  - `write()` – Recibe `'1'` para encender o `'0'` para apagar el LED.
- Crea un nodo de dispositivo en `/dev/gpioled`.

También incluye trazas vía `printk` para depuración.

## Compilación

Desde esta carpeta:

```bash
make
```
Esto genera el archivo del módulo en `build/gpio_led_driver.ko`.

## Carga del Módulo

Insertar el módulo:
```bash
sudo insmod build/gpio_led_driver.ko
```

Verifica con dmesg:
```bash
dmesg | tail
```

Crea el nodo del dispositivo (si no existe automáticamente):
```bash
sudo mknod /dev/gpioled c <major_number> 0
sudo chmod 666 /dev/gpioled
```

El `major_number` lo puedes obtener del mensaje que imprime `dmesg` al cargar el módulo.

## Descarga del Módulo
```bash
sudo rmmod gpio_led_driver
```
Esto liberará el GPIO y limpiará la clase de dispositivo.

## Pruebas
El módulo puede probarse con la aplicación de usuario ubicada en `../user_app/`, o automáticamente con los scripts en `../test/`.

