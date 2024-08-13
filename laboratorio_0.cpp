#include <iostream>
#include <string>  

bool esPar(int numero) {
    return numero % 2 == 0;
}

int longitudString(const std::string& str) {
    return str.length();
}

int main() {
    int numero;
    std::string texto;

   
    std::cout << "Ingresa un número: ";
    std::cin >> numero;

   
    std::cout << "El número ingresado es: " << numero << std::endl;

   
    if (esPar(numero)) {
        std::cout << numero << " es un número par." << std::endl;
    } else {
        std::cout << numero << " es un número impar." << std::endl;
    }

   
    std::cout << "Paridad de los números del 1 al 10:" << std::endl;
    for (int i = 1; i <= 10; i++) {
        if (esPar(i)) {
            std::cout << i << " es par." << std::endl;
        } else {
            std::cout << i << " es impar." << std::endl;
        }
    }

   
    std::cout << "Ingresa un string: ";
    std::cin.ignore();  
    std::getline(std::cin, texto);

  
    int longitud = longitudString(texto);
    std::cout << "La longitud del string ingresado es: " << longitud << std::endl;

   
    std::string textoDefinido = "C++ es genial!";
    longitud = longitudString(textoDefinido);
    std::cout << "La longitud del string \"" << textoDefinido << "\" es: " << longitud << std::endl;

    return 0; 
}
