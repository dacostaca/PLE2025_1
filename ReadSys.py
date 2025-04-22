import os
import time
from datetime import datetime

def leer_archivo_proc(ruta):
    """Función para leer archivos de /proc y devolver su contenido"""
    try:
        with open(ruta, 'r') as archivo:
            contenido = archivo.read()
        return contenido
    except IOError as e:
        return f"Error al leer el archivo {ruta}: {str(e)}"

def mostrar_tiempo():
    """Muestra la hora actual del sistema"""
    ahora = datetime.now()
    print(f"\nHora actual del sistema: {ahora.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"Tiempo en segundos desde epoch: {time.time()}")

def mostrar_stack():
    """Muestra información del stack desde /proc/self/stack"""
    ruta_stack = "/proc/self/stack"
    print(f"\nInformación del stack ({ruta_stack}):")
    print(leer_archivo_proc(ruta_stack))

def mostrar_info_proc():
    """Muestra información de varios archivos en /proc"""
    archivos_proc = {
        "cpuinfo": "/proc/cpuinfo",
        "meminfo": "/proc/meminfo",
        "version": "/proc/version",
        "uptime": "/proc/uptime",
        "loadavg": "/proc/loadavg"
    }
    
    print("\nInformación del sistema desde /proc:")
    for nombre, ruta in archivos_proc.items():
        print(f"\nContenido de {nombre} ({ruta}):")
        print(leer_archivo_proc(ruta))

def main():
    print("="*50)
    print("Monitor de Sistema - Información desde /proc")
    print("="*50)
    
    while True:
        print("\nOpciones disponibles:")
        print("1. Mostrar hora del sistema")
        print("2. Mostrar información del stack")
        print("3. Mostrar información de /proc")
        print("4. Salir")
        
        opcion = input("Seleccione una opción (1-4): ")
        
        if opcion == "1":
            mostrar_tiempo()
        elif opcion == "2":
            mostrar_stack()
        elif opcion == "3":
            mostrar_info_proc()
        elif opcion == "4":
            print("Saliendo del programa...")
            break
        else:
            print("Opción no válida. Por favor seleccione 1-4.")
        
        input("\nPresione Enter para continuar...")

if __name__ == "__main__":
    main()