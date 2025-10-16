#include "ordenamientos.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream> 

using namespace std;

long long comparaciones = 0;
long long intercambios = 0;
int profundidad = 0;

string nombrePatron(int opcionSemilla) {
    switch(opcionSemilla) {
        case 1: return "Aleatorio uniforme";
        case 2: return "Ordenado ascendente";
        case 3: return "Ordenado descendente";
        case 4: return "Casi ordenado 5%";
        case 5: return "Duplicados 10-20";
        default: return "Desconocido";
    }
}

// Funciones de generación de arreglos
vector<int> generarArreglo(int size, int tipoSemilla) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    
    switch(tipoSemilla) {
        case 1: { // Aleatorio uniforme
            uniform_int_distribution<> dis(1, 100000);
            for (int i = 0; i < size; ++i) arr[i] = dis(gen);
            break;
        }
        case 2: // Ordenado ascendente
            for (int i = 0; i < size; ++i) arr[i] = i+1;
            break;
        case 3: // Ordenado descendente
            for (int i = 0; i < size; ++i) arr[i] = size-i;
            break;
        case 4: { // Casi ordenado (5% aleatorio)
            for (int i = 0; i < size; ++i) arr[i] = i+1;
            uniform_int_distribution<> dis(0, size-1);
            for (int i = 0; i < size*0.05; ++i) {
                swap(arr[dis(gen)], arr[dis(gen)]);
            }
            break;
        }
        case 5: { // Con duplicados (10–20 valores únicos)
            uniform_int_distribution<> dis(1, 20);
            for (int i = 0; i < size; ++i) arr[i] = dis(gen);
            break;
        }
        default:
            break;
    }
    return arr;
}

// Función menú
void menu() {
    int opcionAlgoritmo, opcionTamano, opcionSemilla;
    vector<int> tamanos = {1000, 10000, 100000};

    cout << "=== MENÚ DE ORDENAMIENTO ===\n";
    cout << "1. QuickSort\n";
    cout << "2. HeapSort\n";
    cout << "Elige algoritmo (1 o 2): ";
    cin >> opcionAlgoritmo;

    cout << "Tamaño del arreglo:\n";
    for (int i = 0; i < tamanos.size(); i++) {
        cout << i+1 << ". " << tamanos[i] << "\n";
    }
    cout << "Elige opción (1-3): ";
    cin >> opcionTamano;
    if(opcionTamano < 1 || opcionTamano > 3) {
        cout << "Opción inválida, usando tamaño 1000 por defecto.\n";
        opcionTamano = 1;
    }
    int N = tamanos[opcionTamano-1];

    cout << "Tipo de semilla:\n";
    cout << "1. Aleatorio uniforme\n2. Ordenado ascendente\n3. Ordenado descendente\n";
    cout << "4. Casi ordenado (5%)\n5. Con duplicados (10-20 valores únicos)\nElige opción (1-5): ";
    cin >> opcionSemilla;
    if(opcionSemilla < 1 || opcionSemilla > 5) {
        cout << "Opción inválida, usando semilla Aleatorio uniforme por defecto.\n";
        opcionSemilla = 1;
    }

    ofstream archivo("resultados_ordenamiento.txt", ios::out);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar resultados.\n";
        return;
    }

    archivo << "Iteración,Algoritmo,N,Patrón,Tiempo(ms),Comparaciones,Intercambios,Profundidad,CommitHash\n";

    // Ejecutar 30 veces
    for (int iter = 0; iter < 30; ++iter) {
        vector<int> arr = generarArreglo(N, opcionSemilla);

        comparaciones = 0;
        intercambios = 0;
        profundidad = 0;

        auto inicio = chrono::high_resolution_clock::now();

        if (opcionAlgoritmo == 1) {
            quickSort(arr.data(), 0, N-1);
        } else {
            heapSort(arr.data(), N);
        }

        auto fin = chrono::high_resolution_clock::now();
        auto tiempo = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

        string algoritmo = (opcionAlgoritmo==1 ? "QuickSort" : "HeapSort");
        string patron = nombrePatron(opcionSemilla);
        string commitHash = "ABC123";

        cout << "Iteración " << iter+1 << ": "
             << "Algoritmo=" << algoritmo
             << ", N=" << N
             << ", Patrón=" << patron
             << ", Tiempo=" << tiempo << "ms"
             << ", Comparaciones=" << comparaciones
             << ", Intercambios=" << intercambios
             << ", Profundidad=" << profundidad
             << ", CommitHash=" << commitHash << "\n";

        archivo << iter+1 << "," << algoritmo << "," << N << "," << patron << "," 
                << tiempo << "," << comparaciones << "," << intercambios << "," 
                << profundidad << "," << commitHash << "\n";
    }

    archivo.close();
    cout << "\nResultados guardados en 'resultados_ordenamiento.txt'\n";
}

int main() {
    menu();
    return 0;
}

