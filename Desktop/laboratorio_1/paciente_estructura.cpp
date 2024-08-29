#include <iostream>
#include <string>


struct Paciente {
    std::string nombre;
    int edad;
    int peso;
    float altura;
};
int main() {
    // Aqui creo las personas que son pacientes, los nombres son una referencia a Deadpool y Wolverine 
    Paciente persona1;
    Paciente persona2;
    Paciente persona3;


    persona1.nombre = "Logan";
    persona1.edad = 30;
    persona1.peso = 70;
    persona1.altura = 1.75;

    persona2.nombre= "Cassandra";
    persona2.edad = 50;
    persona2.peso = 40;
    persona2.altura = 1.90;

    persona3.nombre = "Wead";
    persona3.edad = 100;
    persona3.peso = 80;
    persona3.altura = 3.10;


    std::cout << "Nombre: " << persona1.nombre << std::endl;
    std::cout << "Edad: " << persona1.edad << std::endl;
    std::cout << "peso: " << persona1.peso << std::endl;
    std::cout << "altura: " << persona1.altura << std::endl;
    

    std::cout << "Nombre: " << persona2.nombre << std::endl;
    std::cout << "Edad: " << persona2.edad << std::endl;
    std::cout << "peso: " << persona2.peso << std::endl;
    std::cout << "altura: " << persona2.altura << std::endl;
    


    std::cout << "Nombre: " << persona3.nombre << std::endl;
    std::cout << "Edad: " << persona3.edad << std::endl;
    std::cout << "peso: " << persona3.peso << std::endl;
    std::cout << "altura: " << persona3.altura << std::endl;
    


    return 0;
}

