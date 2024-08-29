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

    void eliminar(const std::string& nombre) {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            if (temp->paciente.nombre == nombre) {
                if (temp->anterior != nullptr) {
                    temp->anterior->siguiente = temp->siguiente;
                } else {
                    cabeza = temp->siguiente;
                }
                if (temp->siguiente != nullptr) {
                    temp->siguiente->anterior = temp->anterior;
                } else {
                    cola = temp->anterior;
                }
                delete temp;
                return;
            }
            temp = temp->siguiente;
        }
        std::cout << "Paciente con nombre " << nombre << " no encontrado." << std::endl;
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

    Paciente paciente1 = {"Logan", 30, 70, 1.75};
    Paciente paciente2 = {"Cassandra", 50, 60, 1.71};
    Paciente paciente3 = {"Wead", 100, 74, 1.78};

    lista.agregar(paciente1);
    lista.agregar(paciente2);
    lista.agregar(paciente3);

    std::cout << "Elementos de la lista doblemente enlazada desde el inicio:" << std::endl;
    lista.imprimirDesdeInicio();

    std::cout << "Elementos de la lista doblemente enlazada desde el final:" << std::endl;
    lista.imprimirDesdeFinal();

    // Eliminar un paciente
    std::cout << "Eliminando paciente con nombre 'Cassandra':" << std::endl;
    lista.eliminar("Cassandra");

    // Imprimir lista después de la eliminación
    std::cout << "Elementos de la lista doblemente enlazada después de la eliminación:" << std::endl;
    lista.imprimirDesdeInicio();

    return 0;
}
