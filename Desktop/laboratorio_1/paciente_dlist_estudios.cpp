#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // Para std::fixed y std::setprecision

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

    void calcularPromediosYIMC() const {
        Nodo* temp = cabeza;
        int totalEdad = 0;
        int totalPeso = 0;
        int count = 0;

        while (temp != nullptr) {
            const Paciente& p = temp->paciente;
            totalEdad += p.edad;
            totalPeso += p.peso;
            count++;

            float imc = calcularIMC(p.peso, p.altura);
            std::cout << "Nombre: " << p.nombre << ", IMC: " << std::fixed << std::setprecision(2) << imc << std::endl;

            temp = temp->siguiente;
        }

        if (count > 0) {
            std::cout << "Promedio de Edad: " << static_cast<float>(totalEdad) / count << std::endl;
            std::cout << "Promedio de Peso: " << static_cast<float>(totalPeso) / count << std::endl;
        } else {
            std::cout << "No hay pacientes para calcular promedios." << std::endl;
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

    float calcularIMC(int peso, float altura) const {
        return altura > 0 ? static_cast<float>(peso) / (altura * altura) : 0.0f;
    }
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

    // Imprimir lista desde el inicio y el final
    std::cout << "Elementos de la lista doblemente enlazada desde el inicio:" << std::endl;
    lista.imprimirDesdeInicio();

    std::cout << "Elementos de la lista doblemente enlazada desde el final:" << std::endl;
    lista.imprimirDesdeFinal();

    // Calcular promedios y IMC
    std::cout << "Cálculo de promedios e IMC:" << std::endl;
    lista.calcularPromediosYIMC();

    return 0;
}
