#include <iostream>
#include <string>

struct Paciente {
    std::string nombre;
    int edad;
    int peso;
    float altura;
};

int main() {
    // Crear los pacientes
    Paciente paciente1 = {"Logan", 30, 70, 1.75};
    Paciente paciente2 = {"Cassandra", 50, 60, 1.71};
    Paciente paciente3 = {"Wead", 100, 74, 1.78};

    // Crear un arreglo de pacientes
    Paciente pacientes[3] = {paciente1, paciente2, paciente3};

    // Recorrer el arreglo de pacientes e imprimir los datos
    for (int i = 0; i < 3; ++i) {
        std::cout << "Datos del paciente " << i + 1 << ":" << std::endl;
        std::cout << "Nombre: " << pacientes[i].nombre << std::endl;
        std::cout << "Edad: " << pacientes[i].edad << std::endl;
        std::cout << "Peso: " << pacientes[i].peso << std::endl;
        std::cout << "Altura: " << pacientes[i].altura << std::endl;
        std::cout << std::endl;
    }

    return 0;
}