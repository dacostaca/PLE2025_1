# Kernel Module: Controlador de Dispositivo de Caracteres para LED GPIO

**Nombre: Daniel Felipe Acosta Castro**  
**C.C.: 1075309092**

**Nombre: Ivonne Tatiana Zapata Martínez**
**C.C.: 1002543377**  

## Descripción
Este módulo de kernel implementa un controlador de dispositivo de caracteres para el manejo de un LED a través de un pin GPIO configurable en una Lichee RV Dock. Permite la interacción mediante operaciones estándar: `open`, `read`, `write` y `release`.

## Requisitos
- Kernel Linux 6.x con headers instalados.
- Acceso a privilegios de administrador (`sudo`).
- Plataforma: Lichee RV Dock con sistema basado en Linux.

## Estructura del código
- `src/gpio_led_driver.c`: Código fuente del módulo.
- `include/gpio_led_driver.h`: Cabecera del módulo.
- `build/`: Directorio donde se genera el `.ko` y archivos intermedios.
- `Makefile`: Compila el módulo y organiza la salida.

## Compilación
Desde la carpeta `kernel_module/`, ejecutar:

```bash
make
```

Esto generará los archivos del módulo en la carpeta build/

## Carga del módulo
```bash
sudo insmod build/gpio_led_driver.ko
```

verifica el mensaje en el kernel log:
```bash
dmesg | tail
```

## Creación del dispositivo
```bash
sudo mknod /dev/gpioled c <major_number> 0
sudo chmod 666 /dev/gpioled
```

Reemplaza <major_number> por el valor mostrado en el log.

## Descarga del módulo
```bash
sudo rmmod gpio_led_driver
```

## Parámetros
Puedes especificar el pin GPIO al cargar el módulo:
```bash
sudo insmod build/gpio_led_driver.ko gpioPin=114
```

## Licencia
GPL - General Public License
