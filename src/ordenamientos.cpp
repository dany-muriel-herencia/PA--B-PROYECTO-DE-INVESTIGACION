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

// ------------------- QUICKSORT BIDIRECCIONAL (Reduce) -------------------
void Reduce(int A[], int inicio, int final) {
    int izq = inicio;
    int der = final;
    int pos = izq;
    int cen = 1;

    while (cen == 1) {
        cen = 0;

        // ---- Recorrido de derecha a izquierda ----
        while (A[pos] <= A[der] && pos != der)
            der--;

        if (pos != der) {
            int aux = A[pos];
            A[pos] = A[der];
            A[der] = aux;
            pos = der;

            // ---- Recorrido de izquierda a derecha ----
            while (A[pos] >= A[izq] && pos != izq)
                izq++;

            if (pos != izq) {
                aux = A[pos];
                A[pos] = A[izq];
                A[izq] = aux;
                pos = izq;
                cen = 1;
            }
        }

        // ---- Llamadas recursivas ----
        if (pos - 1 > inicio)
            Reduce(A, inicio, pos - 1);

        if (pos + 1 < final)
            Reduce(A, pos + 1, final);
    }
}
