#include <iostream>
#include <cstdlib>
using namespace std;

int particionar(int arreglo[], int indiceInicial, int indiceFinal) {
    int pivote = arreglo[indiceFinal];
    int indiceMenor = indiceInicial - 1;

    for (int i = indiceInicial; i < indiceFinal; i++) {
        if (arreglo[i] <= pivote) {
            indiceMenor++;
            swap(arreglo[indiceMenor], arreglo[i]);
        }
    }
    swap(arreglo[indiceMenor + 1], arreglo[indiceFinal]);
    return indiceMenor + 1;
}

void quickSort(int arreglo[], int indiceInicial, int indiceFinal) {
    if (indiceInicial < indiceFinal) {
        int posicionPivote = particionar(arreglo, indiceInicial, indiceFinal);
        quickSort(arreglo, indiceInicial, posicionPivote - 1);
        quickSort(arreglo, posicionPivote + 1, indiceFinal);
    }
}

void mostrarArreglo(int arreglo[], int tamanio) {
    for (int i = 0; i < tamanio; i++)
        cout << arreglo[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cin>>n ;
    int arreglo[n];
       for (int i = 0; i < n; i++) {
        arreglo[i] = rand() % n;
    }

    cout << "Arreglo original:\n";
    mostrarArreglo(arreglo, n);

    quickSort(arreglo, 0, n - 1);

    cout << "\nArreglo ordenado con Quick Sort:\n";
    mostrarArreglo(arreglo, n);

    return 0;
}
