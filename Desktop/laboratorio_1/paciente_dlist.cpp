#include <iostream>
#include <string>

struct Paciente {
    std::string nombre;
    int edad;
    int peso;
    float altura;
};


struct Nodo {
    Paciente paciente; 
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const Paciente& p) : paciente(p), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDobleEnlazada {
public:
    ListaDobleEnlazada() : cabeza(nullptr), cola(nullptr) {}

    // Agregar un elemento al final de la lista
    void agregar(const Paciente& paciente) {
        Nodo* nuevo_nodo = new Nodo(paciente);
        if (cabeza == nullptr) {
            cabeza = nuevo_nodo;
            cola = nuevo_nodo;
        } else {
            cola->siguiente = nuevo_nodo;
            nuevo_nodo->anterior = cola;
            cola = nuevo_nodo;
        }
    }

    // Imprimir los elementos de la lista desde el inicio
    void imprimirDesdeInicio() const {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            const Paciente& p = temp->paciente;
            std::cout << "Nombre: " << p.nombre << ", Edad: " << p.edad
                      << ", Peso: " << p.peso << ", Altura: " << p.altura << std::endl;
            temp = temp->siguiente;
        }
    }

    
    void imprimirDesdeFinal() const {
        Nodo* temp = cola;
        while (temp != nullptr) {
            const Paciente& p = temp->paciente;
            std::cout << "Nombre: " << p.nombre << ", Edad: " << p.edad
                      << ", Peso: " << p.peso << ", Altura: " << p.altura << std::endl;
            temp = temp->anterior;
        }
    }

    ~ListaDobleEnlazada() {
        Nodo* temp;
        while (cabeza != nullptr) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

private:
    Nodo* cabeza;
    Nodo* cola;
};

int main() {
    ListaDobleEnlazada lista;

    // Crear pacientes
    Paciente paciente1 = {"Logan", 30, 70, 1.75};
    Paciente paciente2 = {"Cassandra", 50, 60, 1.71};
    Paciente paciente3 = {"Wead", 100, 74, 1.78};

    // Agregar pacientes a la lista
    lista.agregar(paciente1);
    lista.agregar(paciente2);
    lista.agregar(paciente3);

    std::cout << "Elementos de la lista doblemente enlazada desde el inicio:" << std::endl;
    lista.imprimirDesdeInicio();

    std::cout << "Elementos de la lista doblemente enlazada desde el final:" << std::endl;
    lista.imprimirDesdeFinal();

    return 0;
}
