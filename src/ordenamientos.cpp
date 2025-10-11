#include "ordenamientos.h"
#include <algorithm> // para swap

// ------------------- HEAPSORT -------------------
void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;
    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    for (int i = size/2 - 1; i >= 0; --i)
        heapify(arr, size, i);

    for (int i = size - 1; i >= 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ------------------- QUICKSORT -------------------
int particionar(int arreglo[], int indiceInicial, int indiceFinal) {
    int pivote = arreglo[indiceFinal];
    int indiceMenor = indiceInicial - 1;

    for (int i = indiceInicial; i < indiceFinal; i++) {
        if (arreglo[i] <= pivote) {
            indiceMenor++;
            std::swap(arreglo[indiceMenor], arreglo[i]);
        }
    }
    std::swap(arreglo[indiceMenor + 1], arreglo[indiceFinal]);
    return indiceMenor + 1;
}

void quickSort(int arreglo[], int indiceInicial, int indiceFinal) {
    if (indiceInicial < indiceFinal) {
        int posicionPivote = particionar(arreglo, indiceInicial, indiceFinal);
        quickSort(arreglo, indiceInicial, posicionPivote - 1);
        quickSort(arreglo, posicionPivote + 1, indiceFinal);
    }
}
