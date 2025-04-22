#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <unistd.h>
#include <limits>
#include <map>

using namespace std;

// Función para leer archivos de /proc
string leerArchivoProc(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return "Error: No se pudo abrir " + ruta;
    }
    
    string contenido((istreambuf_iterator<char>(archivo)), 
                    istreambuf_iterator<char>());
    archivo.close();
    
    return contenido;
}

// Mostrar información de tiempo
void mostrarTiempo() {
    time_t ahora = time(nullptr);
    cout << "\nHora actual del sistema: " << ctime(&ahora);
    cout << "Tiempo en segundos desde epoch: " << ahora << endl;
}

// Mostrar información del stack
void mostrarStack() {
    string ruta_stack = "/proc/self/stack";
    cout << "\nInformación del stack (" << ruta_stack << "):\n";
    cout << leerArchivoProc(ruta_stack) << endl;
}

// Mostrar información de varios archivos en /proc
void mostrarInfoProc() {
    map<string, string> archivos_proc = {
        {"cpuinfo", "/proc/cpuinfo"},
        {"meminfo", "/proc/meminfo"},
        {"version", "/proc/version"},
        {"uptime", "/proc/uptime"},
        {"loadavg", "/proc/loadavg"}
    };
    
    cout << "\nInformación del sistema desde /proc:\n";
    for (const auto& [nombre, ruta] : archivos_proc) {
        cout << "\nContenido de " << nombre << " (" << ruta << "):\n";
        cout << leerArchivoProc(ruta) << endl;
    }
}

// Limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Menú principal
int main() {
    cout << string(50, '=') << endl;
    cout << "Monitor de Sistema - Información desde /proc" << endl;
    cout << string(50, '=') << endl;
    
    while (true) {
        cout << "\nOpciones disponibles:\n";
        cout << "1. Mostrar hora del sistema\n";
        cout << "2. Mostrar información del stack\n";
        cout << "3. Mostrar información de /proc\n";
        cout << "4. Salir\n";
        
        cout << "Seleccione una opción (1-4): ";
        int opcion;
        cin >> opcion;
        limpiarBuffer();
        
        switch (opcion) {
            case 1:
                mostrarTiempo();
                break;
            case 2:
                mostrarStack();
                break;
            case 3:
                mostrarInfoProc();
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opción no válida. Por favor seleccione 1-4." << endl;
        }
        
        cout << "\nPresione Enter para continuar...";
        limpiarBuffer();
    }
    
    return 0;
}