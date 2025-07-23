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

## 🚀 Ejecución en una nueva placa embebida

Si deseas ejecutar el proyecto `MotionWatch` en una placa diferente (por ejemplo, una Raspberry Pi distinta, una BeagleBone o cualquier sistema embebido con Linux), sigue estos pasos:

### 1. Requisitos previos

- Sistema embebido con distribución Linux (por ejemplo, Raspbian, Debian, Yocto, etc.).
- Paquetes esenciales instalados: `gcc`, `make`, `libjpeg-dev`, `libv4l-dev`, entre otros.
- Acceso a la terminal del sistema embebido.
- Una cámara compatible con V4L2 conectada a la placa.
- Acceso a los pines GPIO desde el sistema.


## 🚀 Cómo clonar, compilar y ejecutar el proyecto

```bash
# 📥 Clonar el repositorio
git clone https://github.com/tu-usuario/MotionWatch.git
cd MotionWatch

# 🛠️ Compilar para la placa actual
make

# 🧩 Compilar para otra arquitectura (ej. Raspberry Pi)
# 1. Edita el Makefile y cambia el compilador:
#    CC = arm-linux-gnueabihf-gcc
# 2. Luego compila:
make clean
make

# 3. Transfiere el binario a la placa:
scp bin/motion_app usuario@IP_DE_LA_PLACA:/ruta/destino

# 4. En la placa, ejecuta el binario:
./motion_app
```

## 📦 Dependencias necesarias en la placa

Antes de ejecutar el programa en la placa (como una Raspberry Pi), asegúrate de instalar estas dependencias:

```bash
sudo apt update
sudo apt install -y libjpeg-dev libv4l-dev libopencv-dev
```

> Estas bibliotecas permiten capturar imágenes, manipular video y realizar procesamiento de imágenes en tiempo real.

## ⚙️ ¿Cómo funciona el sistema?

El proyecto **MotionWatch** realiza detección de movimiento en tiempo real utilizando una cámara y reacciona mediante señales en los pines GPIO:

1. 📷 Captura continua de imágenes desde una cámara.
2. 🧠 Compara cada nueva imagen con la anterior usando un algoritmo de diferencia.
3. ⚠️ Si detecta movimiento:
   - Enciende un LED.
   - Dispara una alarma (por ejemplo, mediante un zumbador conectado al GPIO).
4. 📤 Guarda una imagen de evidencia si se detectó movimiento.

## 🧪 ¿Cómo hacer pruebas?

Puedes probar el sistema de dos formas:

### A. En un entorno de desarrollo (PC)

1. Compila con `make`.
2. Ejecuta con imágenes estáticas para simular movimiento:
   ```bash
   ./motion_app test/img1.jpg test/img2.jpg
   ```
3. Observa si se detecta movimiento correctamente.

### B. En la placa (modo producción)

1. Conecta una cámara compatible (como una cámara USB o CSI).
2. Ejecuta el binario:
   ```bash
   ./motion_app
   ```
3. Genera movimiento frente a la cámara y verifica la activación del LED/alarma.

## 📁 Estructura del Proyecto

```plaintext
MotionWatch/
├── core/                 # Lógica principal del sistema
│   ├── capture.c         # Captura imágenes desde la cámara
│   ├── gpio.c            # Control del GPIO (LED, alarma)
│   ├── motion_engine.c   # Detecta movimiento en las imágenes
│   └── utils.c           # Funciones auxiliares
│
├── include/              # Archivos de cabecera (.h)
│   ├── capture.h
│   ├── gpio.h
│   ├── motion_engine.h
│   └── utils.h
│
├── test/                 # Pruebas del sistema
│   └── test_main.c       # Código de prueba principal
│
├── Makefile              # Script de compilación del proyecto
└── README.md             # Documentación del proyecto
```

