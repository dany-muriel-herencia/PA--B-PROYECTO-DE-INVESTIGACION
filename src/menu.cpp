#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "ordenamientos.h"

using namespace std;
using namespace std::chrono;

void generarDatos(int* arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % n;
}

void mostrarArreglo(int* arr, int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    // 🔒 Semilla fija para generar siempre los mismos números
    srand(12345);  

    int opcionAlgoritmo, opcionTamano;

    do {
        cout << "\n==============================\n";
        cout << "      MENU DE ORDENAMIENTO     \n";
        cout << "==============================\n";
        cout << "1. HeapSort\n";
        cout << "2. QuickSort\n";
        cout << "3. Salir\n";
        cout << "Seleccione el algoritmo: ";
        cin >> opcionAlgoritmo;

        if (opcionAlgoritmo == 3) break;

        cout << "\nSeleccione el tamaño del arreglo:\n";
        cout << "1. 1,000 elementos\n";
        cout << "2. 10,000 elementos\n";
        cout << "3. 100,000 elementos\n";
        cout << "Opcion: ";
        cin >> opcionTamano;

        int n = (opcionTamano == 1) ? 1000 : (opcionTamano == 2) ? 10000 : 100000;

        // ✅ Mantiene el mismo conjunto aleatorio siempre
        int* arr = new int[n];
        srand(12345);  // ← Semilla fija para cada generación (reproducible)
        generarDatos(arr, n);

        cout << "\nArreglo original (primeros 20 elementos):\n";
        for (int i = 0; i < min(n,20); i++) cout << arr[i] << " ";
        cout << (n > 20 ? "...\n" : "\n");

        auto inicio = steady_clock::now();

        if (opcionAlgoritmo == 1)
            heapSort(arr, n);
        else if (opcionAlgoritmo == 2)
            quickSort(arr, 0, n - 1);

        auto fin = steady_clock::now();
        auto tiempo_ms = duration_cast<milliseconds>(fin - inicio).count();

        cout << "\nArreglo ordenado (primeros 20 elementos):\n";
        for (int i = 0; i < min(n,20); i++) cout << arr[i] << " ";
        cout << (n > 20 ? "...\n" : "\n");

        cout << "\nTiempo de ejecucion: " << tiempo_ms << " ms\n";

        delete[] arr;

    } while (opcionAlgoritmo != 3);

    cout << "\nPrograma finalizado.\n";
    return 0;
}
