#include <iostream>
#include <vector>
#include <cstdlib>  
#include <chrono>   
#include <iomanip>  
#include <limits>   

using namespace std;
using namespace chrono;
void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << "a[" << i << "]=" << vec[i] << " ";
    }
    cout << endl;
}

// aqui se implemntan los dos metodos
void selectionSort(vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }
        swap(vec[i], vec[minIndex]);
    }
}

int partition(vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (vec[j] < pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quicksort(vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quicksort(vec, low, pi - 1);
        quicksort(vec, pi + 1, high);
    }
}

int main() {
    int N;
    char VER;

    // Preguntar por el valor de N y lo valida
    do {
        cout << "Ingrese el numero de elementos a ordenar (N > 0): ";
        cin >> N;

        // Validar si la entrada es un número válido y positivo
        if (cin.fail() || N <= 0) {
            cout << "Error: Debe ingresar un número entero positivo.\n";
            cin.clear();  // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        }
    } while (N <= 0);

    // Preguntar por el valor de VER y lo valida
    do {
        cout << "Desea mostrar el contenido del vector? (s/n): ";
        cin >> VER;

        // Validar si la entrada es válida  's' o 'n'
        if (VER != 's' && VER != 'n') {
            cout << "Error: Debe ingresar 's' para mostrar o 'n' para no mostrar.\n";
        }
    } while (VER != 's' && VER != 'n');

    bool mostrar = (VER == 's');  

  
    vector<int> vec(N);
    srand(time(0));  
    for (int i = 0; i < N; i++) {
        vec[i] = rand() % 10000;  
    }

    vector<int> vecSelection = vec;
    vector<int> vecQuicksort = vec;


    auto start = high_resolution_clock::now();
    selectionSort(vecSelection);
    auto end = high_resolution_clock::now();
    auto durationSelection = duration_cast<milliseconds>(end - start).count();

    start = high_resolution_clock::now();
    quicksort(vecQuicksort, 0, N - 1);
    end = high_resolution_clock::now();
    auto durationQuicksort = duration_cast<milliseconds>(end - start).count();

    // Aqui se muestra los resultado 
    if (mostrar) {
        cout << "Contenido del vector ordenado (Selection Sort):\n";
        printVector(vecSelection);
        cout << "Contenido del vector ordenado (Quicksort):\n";
        printVector(vecQuicksort);
    }


    cout << "Seleccion\t|" << durationSelection << " milisegundos\n";
    cout << "Quicksort\t|" << durationQuicksort << " milisegundos\n";

    return 0;
}
