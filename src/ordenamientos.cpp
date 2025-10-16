#include "ordenamientos.h"
#include <algorithm> // para std::swap

// ------------------- HEAPSORT -------------------
void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Verifica si el hijo izquierdo es mayor que la raíz
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // Verifica si el hijo derecho es mayor que el mayor actual
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // Si el mayor no es la raíz, intercambia y sigue heapificando
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    // Construye el heap (reorganiza el arreglo)
    for (int i = size / 2 - 1; i >= 0; --i)
        heapify(arr, size, i);

    // Extrae los elementos uno por uno del heap
    for (int i = size - 1; i >= 0; --i) {
        std::swap(arr[0], arr[i]); // mueve la raíz actual al final
        heapify(arr, i, 0);        // llama heapify sobre el heap reducido
    }
}

// ------------------- QUICKSORT PIVOTE EN EL MEDIO -------------------
void quickSort(int A[], int inicio, int fin) {
    int i = inicio;
    int j = fin;

    // Elegir el pivote como el elemento del medio
    int pivote = A[(inicio + fin) / 2];

    // Mientras los índices no se crucen
    while (i <= j) {
        // Avanza desde la izquierda mientras A[i] < pivote
        while (A[i] < pivote)
            i++;

        // Retrocede desde la derecha mientras A[j] > pivote
        while (A[j] > pivote)
            j--;

        // Si i <= j, intercambia los elementos
        if (i <= j) {
            int aux = A[i];
            A[i] = A[j];
            A[j] = aux;
            i++;
            j--;
        }
    }

    // Llamadas recursivas en las dos mitades
    if (inicio < j)
        quickSort(A, inicio, j);
    if (i < fin)
        quickSort(A, i, fin);
}