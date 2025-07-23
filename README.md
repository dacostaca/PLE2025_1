# MotionWatch 🎥🟢

*MotionWatch* es una solución embebida diseñada para sistemas Linux que permite la *detección de movimiento* en tiempo real mediante una cámara USB, combinando procesamiento de imágenes básico y control físico a través de pines GPIO.

---
## Integrantes:
* Daniel Felipe Acosta Castro.
  CC: 1075309092

* Ivonne Tatiana Zapata Matínez.
  CC: 1002543377

-----


## ✨ Características

  * **Captura de Imágenes Continua**: Adquiere frames de video periódicamente.
  * **Detección de Movimiento**: Compara frames consecutivos para identificar cambios significativos en la escena.
  * **Umbral de Movimiento Configurable**: Permite ajustar la sensibilidad de la detección de movimiento (actualmente 1% de píxeles diferentes).
  * **Indicadores Visuales (LEDs)**:
      * Un LED indica cuando se está realizando una captura de imagen.
      * Otro LED se enciende momentáneamente cuando se detecta movimiento.
  * **Manejo de Señales**: Permite un apagado limpio del programa al recibir señales de interrupción (`SIGINT`, `SIGTERM`).
  * **Multithreading**: La lógica de captura y detección de movimiento se ejecuta en un hilo separado para no bloquear el proceso principal.
  * **Gestión de Directorios**: Crea automáticamente los directorios necesarios (`frames` y `logs`) si no existen.

-----

## ⚙️ Requisitos

Este proyecto está diseñado para ejecutarse en un sistema Linux embebido (como una Raspberry Pi) con capacidades de GPIO y acceso a cámara.

  * **Hardware**:
      * Una placa de desarrollo con pines GPIO (ej. Raspberry Pi).
      * Cámara compatible (ej. Raspberry Pi Camera Module o Webcam USB).
      * Dos LEDs y resistencias apropiadas.
      * Cables jumper para conectar los LEDs a los pines GPIO.
  * **Software (en el sistema operativo de destino)**:
      * **Compilador C** (GCC o Clang).
      * **Bibliotecas de desarrollo para POSIX Threads** (`pthread`).
      * **Bibliotecas para control de cámara**: Dependerá de tu hardware específico (ej., `libcamera-dev`, `fswebcam`, o librerías de OpenCV).
      * **Bibliotecas para GPIO**: Una implementación de bajo nivel como la proporcionada por `gpio.h`/`gpio.c`, o librerías como `wiringPi` o `libgpiod`.
      * **Bibliotecas para manipulación de imágenes**: Se asume el uso de OpenCV u otra librería similar para `detectar_movimiento`.

-----

## 📁 Estructura del Proyecto

El proyecto se compone de varios archivos C, organizados para modularidad:

```
MotionWatch/
├── app/                     # Flujo de ejecución principal
│   ├── main.c
│   ├── app.c
│   └── app.h
├── core/                    # Lógica central del sistema
│   ├── capture.c/h          # Captura de imágenes
│   ├── motion_engine.c/h    # Detección de movimiento
│   ├── gpio.c/h             # Control de GPIOs
│   └── utils.c/h            # Utilidades de imagen
├── tests/                   # Pruebas unitarias
│   └── test_motion.c
├── frames/                  # Almacenamiento de fotogramas en ejecución
├── test_frames/             # Imágenes de prueba para validación
├── scripts/
│   └── build.sh             # Script de compilación automatizada
├── Makefile                 # Sistema de construcción principal
└── README.md                # Este archivo
```


-----

## 🛠️ Configuración

Antes de compilar, asegúrate de tener instaladas todas las dependencias necesarias y de configurar el hardware.

  * **Pines GPIO**: Los LEDs (`LED_CAPTURA` y `LED_MOVIMIENTO`) deben estar definidos en la implementación de `gpio.c` (o `gpio.h`) para mapearse correctamente a los pines GPIO de tu hardware. Es crucial conectar resistencias adecuadas para proteger los LEDs.
  * **Configuración de la Cámara**: La función `capturar_frame` (en `capture.c`) debe ser compatible con tu cámara y guardar las imágenes en formato JPG.
  * **Umbral de Movimiento**: Puedes ajustar la sensibilidad de la detección de movimiento modificando el valor de `UMBRAL_MOVIMIENTO` en `app.c`:
    ```c
    #define UMBRAL_MOVIMIENTO 1 // Porcentaje de píxeles diferentes
    ```
    Un valor más bajo (`0.5`) hará que el sistema sea más sensible a movimientos sutiles, mientras que un valor más alto (`2` o `3`) ignorará pequeños cambios.

-----


## 🎮 Uso

Una vez que el programa esté en ejecución, realizará las siguientes acciones:

  * **Inicialización**: Se encenderán y apagarán brevemente los LEDs de verificación, y se asegurará la existencia de los directorios `frames` y `logs`.
  * **Captura Continua**: El LED de captura (`LED_CAPTURA`) se encenderá durante cada toma de foto.
  * **Detección de Movimiento**: Si se detecta movimiento (superando el `UMBRAL_MOVIMIENTO`), el LED de movimiento (`LED_MOVIMIENTO`) se encenderá durante 1 segundo como alerta visual.
  * **Apagado Limpio**: Para detener el programa de forma segura, presiona `Ctrl+C` en la terminal. El manejador de señales apagará los LEDs y permitirá que el programa finalice correctamente.

-----

## 🔌 Ejecución en Otros Embebidos

Aunque MotionWatch está diseñado específicamente para sistemas **Linux embebidos** (como la Raspberry Pi), su arquitectura modular permite una posible portabilidad a otras plataformas embebidas. La clave reside en la **abstracción de las capas de hardware**.

Para que MotionWatch funcione en otro tipo de embebido (por ejemplo, microcontroladores avanzados con RTOS o plataformas de System-on-Chip diferentes a Linux):

1.  **Sistema Operativo**:

      * **Linux Embebido**: El código actual es altamente compatible. Simplemente requiere que el nuevo hardware tenga un kernel Linux funcional y soporte para POSIX threads (`pthread`), que es estándar.
      * **RTOS (Real-Time Operating System)**: Si el sistema embebido usa un RTOS (como FreeRTOS, Zephyr, o mbed OS), las llamadas a funciones de POSIX threads (`pthread_create`, `pthread_join`) y manejo de señales (`sigaction`) tendrían que ser reemplazadas por las primitivas de concurrencia y manejo de eventos/tareas del RTOS específico. Las funciones de `sleep` también se adaptarían a las del RTOS (ej., `osDelay` o similar).

2.  **Capa de Hardware (GPIO)**:

      * El archivo `gpio.c` es la interfaz crucial para el control de los LEDs. Para otra plataforma, tendrías que **reimplementar las funciones `gpio_init` y `gpio_set`** utilizando las APIs o registros de hardware específicos de ese microcontrolador o SoC. Por ejemplo, en un STM32, usarías las librerías HAL o LL para configurar y manipular los pines.
      * Deberías mapear `LED_CAPTURA` y `LED_MOVIMIENTO` a los pines correctos de tu nuevo hardware.

3.  **Capa de Captura de Imágenes (`capture.c`)**:

      * Esta es la parte más compleja de portar. La forma en que se captura una imagen (`capturar_frame`) es altamente dependiente del hardware de la cámara y del controlador disponible.
      * Si el nuevo embebido tiene un sensor de cámara diferente o carece de una pila de software de cámara robusta como V4L2 en Linux, esta implementación deberá ser **reescrita por completo**. Esto podría implicar interactuar directamente con registros MIPI-CSI, controladores de sensor de imagen, o adaptadores de cámara específicos.

4.  **Capa de Detección de Movimiento (`motion_engine.c`)**:

      * Si esta capa usa bibliotecas multiplataforma (como OpenCV), la portabilidad es relativamente sencilla, siempre y cuando la biblioteca pueda compilarse y ejecutarse en el nuevo entorno embebido.
      * Si hay dependencias de hardware o aceleradores específicos (ej., una NPU o GPU en el SoC para procesamiento de imagen), se deberían adaptar o deshabilitar.

5.  **Sistema de Archivos y Utilidades (`utils.c`)**:

      * Funciones como `crear_directorio_si_no_existe` y las operaciones de archivo (`access`, `remove`, `rename`) dependen de un sistema de archivos accesible. Si el nuevo embebido no tiene un sistema de archivos robusto (ej., solo usa memoria Flash para el firmware), las operaciones de guardado de imágenes deberían adaptarse (ej., guardar en RAM, enviar por red, o no guardar frames).
      * Las impresiones a consola (`printf`, `fprintf`) son generalmente compatibles, pero podrían redirigirse a un puerto serie (UART) para depuración.

En resumen, la portabilidad de MotionWatch a diferentes sistemas embebidos requeriría la **reimplementación de las capas de abstracción de hardware (GPIO y Cámara)** y la **adaptación de las primitivas del sistema operativo (hilos y manejo de señales)** si no se usa Linux.

-----


