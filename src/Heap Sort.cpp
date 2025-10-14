#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// --------------------- QUICK SORT BIDIRECCIONAL ---------------------
void quickSort(int A[], int inicio, int final) {
    int izq = inicio;
    int der = final;
    int pos = izq;
    int cen = 1;

    while (cen == 1) {
        cen = 0;

        // Recorrido de derecha a izquierda
        while (A[pos] <= A[der] && pos != der)
            der--;

        if (pos != der) {
            int aux = A[pos];
            A[pos] = A[der];
            A[der] = aux;
            pos = der;

            // Recorrido de izquierda a derecha
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

        // Llamadas recursivas
        if (pos - 1 > inicio)
            quickSort(A, inicio, pos - 1);

        if (pos + 1 < final)
            quickSort(A, pos + 1, final);
    }
}


void printArray(int A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

// --------------------- MAIN ---------------------
int main() {
    srand(time(0));

    int n;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (n*2); 

    cout << "Arreglo original (primeros 20 elementos): ";
    for (int i = 0; i < min(n,20); i++) cout << arr[i] << " ";
    cout << endl;

    auto inicio = high_resolution_clock::now();

    quickSort(arr, 0, n - 1);

    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<milliseconds>(fin - inicio);

    cout << "Arreglo ordenado (primeros 20 elementos): ";
    for (int i = 0; i < min(n,20); i++) cout << arr[i] << " ";
    cout << endl;

    cout << "Tiempo de ejecucion: " << duracion.count() << " ms" << endl;

    delete[] arr;
    return 0;
}
