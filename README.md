# MotionWatch 🎥🟢

**MotionWatch** es una solución embebida diseñada para sistemas Linux que permite la **detección de movimiento** en tiempo real mediante una cámara USB, combinando procesamiento de imágenes básico y control físico a través de pines GPIO.

---
Integrantes:
* Daniel Felipe Acosta Castro.
  CC: 1075309092

* Ivonne Tatiana Zapata Matínez.
  CC: 1002543377

## 🧠 Resumen del Proyecto

Este proyecto se desarrolló como parte del curso **Sistemas Embebidos en Linux (PLE2025)**, con el objetivo de integrar múltiples aspectos del desarrollo sobre plataformas Linux embebidas:

- Captura y procesamiento de imágenes.
- Control de periféricos GPIO.
- Modularidad en C.
- Ejecución basada en hilos (`pthreads`).

Al detectar movimiento en la escena, el sistema **activa un indicador físico (LED)** mediante GPIO y registra el evento por consola.

---

## 📸 Características Principales

✅ Captura periódica de imágenes desde una cámara USB  
✅ Detección de movimiento por comparación de fotogramas consecutivos  
✅ Activación visual mediante LED cuando se detecta movimiento  
✅ Control preciso mediante hilos y señales POSIX  
✅ Modularidad y escalabilidad del código  
✅ Compatible con Raspberry Pi u otras plataformas embebidas Linux

---

## 🗂️ Estructura del Proyecto

```bash
MotionWatch/
├── core/                    # Lógica principal del sistema
│   ├── capture.c            # Captura imágenes desde la cámara
│   ├── gpio.c               # Controla el GPIO (LED/alarma)
│   ├── motion_engine.c      # Procesamiento para detectar movimiento
│   └── utils.c              # Funciones auxiliares de soporte
│
├── include/                 # Archivos de cabecera (.h)
│   ├── capture.h
│   ├── gpio.h
│   ├── motion_engine.h
│   └── utils.h
│
├── test/                    # Código para pruebas del sistema
│   └── test_main.c
│
├── Makefile                 # Script para compilar todo el proyecto
└── README.md                # Documentación general del proyecto
