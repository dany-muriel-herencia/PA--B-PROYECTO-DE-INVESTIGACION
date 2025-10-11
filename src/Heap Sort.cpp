#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// ---------- Función heapify ----------
void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;
    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

// ---------- Algoritmo HeapSort ----------
void heapSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; --i)
        heapify(arr, size, i);

    for (int i = size - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ---------- Función para imprimir el arreglo ----------
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

// ---------- Programa principal ----------
int main() {
    srand(42); // Semilla fija para reproducibilidad

    int tamanios[] = {1000, 10000, 100000};

    for (int t = 0; t < 3; t++) {
        int n = tamanios[t];
        int* arr = new int[n];

        // Generar datos aleatorios
        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;

        cout << "\n==============================\n";
        cout << "HeapSort con " << n << " elementos\n";
        cout << "==============================\n";

        // Medir tiempo de ejecución
        auto inicio = high_resolution_clock::now();
        heapSort(arr, n);
        auto fin = high_resolution_clock::now();

        auto duracion = duration_cast<milliseconds>(fin - inicio);
        cout << "Tiempo de ejecucion: " << duracion.count() << " ms" << endl;

        delete[] arr; 
    }

    return 0;
}
