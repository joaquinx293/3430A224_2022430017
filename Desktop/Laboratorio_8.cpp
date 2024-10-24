#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <limits>
#include <algorithm>  
#include <random>    

using namespace std;
using namespace chrono;

void Mostrar_vector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << "a[" << i << "]=" << vec[i] << " ";
    }
    cout << endl;
}
// aqui estan los distintos metodos de ordenamiento
void Selecion_sort(vector<int>& vec) {
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

int Validar() {// valida que los valores que se entregran esten correctos
    int N;
    do {
        cout << "Ingrese el numero de elementos a ordenar (N > 0): ";
        cin >> N;
        if (cin.fail() || N <= 0) {
            cout << "Error: Debe ingresar un numero entero positivo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (N <= 0);
    return N;
}

bool Preguntas() {
    char VER;
    do {
        cout << "Desea mostrar el contenido del vector? (s/n): ";
        cin >> VER;
        if (VER != 's' && VER != 'n') {
            cout << "Error: Debe ingresar 's' para mostrar o 'n' para no mostrar.\n";
        }
    } while (VER != 's' && VER != 'n');
    return (VER == 's');
}

int main() {
    int N = Validar();
    bool mostrar = Preguntas();

    vector<int> vec(N);
    random_device rd;
    mt19937 g(rd());
    iota(vec.begin(), vec.end(), 0);
    shuffle(vec.begin(), vec.end(), g);

    vector<int> vecSelection = vec;
    vector<int> vecQuicksort = vec;

    auto start = high_resolution_clock::now();
    Selecion_sort(vecSelection);
    auto end = high_resolution_clock::now();
    auto durationSelection = duration_cast<milliseconds>(end - start).count();

    start = high_resolution_clock::now();
    quicksort(vecQuicksort, 0, N - 1);
    end = high_resolution_clock::now();
    auto durationQuicksort = duration_cast<milliseconds>(end - start).count();

    if (mostrar) {// muestras el tiempo y el metodo 
        cout << "Contenido del vector ordenado (Selection Sort):\n";
        Mostrar_vector(vecSelection);
        cout << "Contenido del vector ordenado (Quicksort):\n";
        Mostrar_vector(vecQuicksort);
    }

    cout << "Seleccion\t|" << durationSelection << " milisegundos\n";
    cout << "Quicksort\t|" << durationQuicksort << " milisegundos\n";
    return 0;
}

