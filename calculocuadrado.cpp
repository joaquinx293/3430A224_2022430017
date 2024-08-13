#include <iostream>

int main() {
    int numero;

    std::cout << "Ingresa un número: ";
    std::cin >> numero;

    int cuadrado = numero * numero;

    std::cout << "El cuadrado de " << numero << " es " << cuadrado << std::endl;

    return 0;
}