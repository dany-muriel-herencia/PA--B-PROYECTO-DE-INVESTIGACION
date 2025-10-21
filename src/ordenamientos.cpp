#include "ordenamientos.h"
#include <algorithm> 

// ------------------- HEAPSORT -------------------
void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    
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
   
    for (int i = size / 2 - 1; i >= 0; --i)
        heapify(arr, size, i);

    
    for (int i = size - 1; i >= 0; --i) {
        std::swap(arr[0], arr[i]); 
        heapify(arr, i, 0);        
    }
}

// ------------------- QUICKSORT -------------------
void quickSort(int A[], int inicio, int fin) {
    int i = inicio;
    int j = fin;

   
    int pivote = A[(inicio + fin) / 2];

   
    while (i <= j) {
        
        while (A[i] < pivote)
            i++;

       
        while (A[j] > pivote)
            j--;

        
        if (i <= j) {
            int aux = A[i];
            A[i] = A[j];
            A[j] = aux;
            i++;
            j--;
        }
    }

    if (inicio < j)
        quickSort(A, inicio, j);
    if (i < fin)
        quickSort(A, i, fin);
}