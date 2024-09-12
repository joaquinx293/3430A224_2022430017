#include <iostream>
using namespace std;

const int MAX = 50; 

class Pila {
private:
    int elementos[MAX];
    int tope; 

public:
    Pila() {
        tope = -1; 
    }

   
    bool pilaVacia() {
        return tope == -1;
    }

    
    bool pilaLlena() {
        return tope == MAX - 1;
    }

   
    void push(int valor) {
        if (pilaLlena()) {
            cout << "Error: Pila llena. No se puede insertar." << endl;
        } else {
            tope++;
            elementos[tope] = valor;
            cout << "Elemento " << valor << " insertado." << endl;
        }
    }

   
    void pop() {
        if (pilaVacia()) {
            cout << "Error: Pila vacía. No se puede eliminar." << endl;
        } else {
            cout << "Elemento " << elementos[tope] << " eliminado." << endl;
            tope--;
        }
    }

   
    void mostrarPila() {
        if (pilaVacia()) {
            cout << "Pila vacía." << endl;
        } else {
            cout << "Contenido de la pila:" << endl;
            for (int i = tope; i >= 0; i--) {
                cout << "| " << elementos[i] << " |" << endl;
            }
        }
    }
};

void mostrarMenu() {
    std::cout << "Menu de opciones:" << std::endl;
    std::cout << "Tienes que agregar un elemento para mostrar valores " << std::endl;
    std::cout << "1. 1. Agregar elemento (Push)\n" << std::endl;
    std::cout << "2. Eliminar elemento (Pop)\n" << std::endl;
    std::cout << "3. Ver pila\n" << std::endl;
    std::cout << "0. Salir\n" << std::endl;
    }

int main() {
    Pila pila;
    int opcion, valor;
    mostrarMenu();
    std::cout << "Seleccione una opción: ";
    std::cin >> opcion;
    std::cin.ignore(); 
    do {
        cout << "\nMenu de opciones:\n";
        cout << "1. Agregar elemento (Push)\n";
        cout << "2. Eliminar elemento (Pop)\n";
        cout << "3. Ver pila\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        switch (opcion) {
        case 1:
            cout << "Ingrese valor: ";
            cin >> valor;
            pila.push(valor);
            break;
        case 2:
            pila.pop();
            break;
        case 3:
            pila.mostrarPila();
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
