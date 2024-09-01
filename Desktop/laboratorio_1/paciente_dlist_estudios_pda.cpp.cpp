#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> // Para std::fixed y std::setprecision

struct Paciente {
    std::string nombre;
    int edad;
    float altura;
    int peso;
    float AC1;
    float imc;
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
    class ColaDePrioridad {
    private:
    Nodo* cabeza;
    Nodo* cola;

    // Función para comparar la prioridad entre pacientes
    bool esMayorPrioridad(const Paciente& p1, const Paciente& p2) {
        if (p1.imc == p2.imc) {
            return p1.AC1 > p2.AC1; // Si el IMC es igual, compara el A1C
        }
        return p1.imc > p2.imc; // Comparar por IMC
    }

public:
    ColaDePrioridad() : cabeza(nullptr), cola(nullptr) {}

    void encolarPaciente(const Paciente& paciente) {
        Nodo* nuevo_nodo = new Nodo(paciente);

        // Si la cola está vacía
        if (cabeza == nullptr) {
            cabeza = cola = nuevo_nodo;
            return;
        }

        // Insertar en la posición correcta según la prioridad
        Nodo* temp = cabeza;
        while (temp != nullptr && esMayorPrioridad(temp->paciente, paciente)) {
            temp = temp->siguiente;
        }

        if (temp == nullptr) {
            // Insertar al final
            cola->siguiente = nuevo_nodo;
            nuevo_nodo->anterior = cola;
            cola = nuevo_nodo;
        } else if (temp == cabeza) {
            // Insertar al inicio
            nuevo_nodo->siguiente = cabeza;
            cabeza->anterior = nuevo_nodo;
            cabeza = nuevo_nodo;
        } else {
            // Insertar en el medio
            Nodo* anterior = temp->anterior;
            anterior->siguiente = nuevo_nodo;
            nuevo_nodo->anterior = anterior;
            nuevo_nodo->siguiente = temp;
            temp->anterior = nuevo_nodo;
        }
    }

    Paciente desencolarPaciente() {
        if (cabeza == nullptr) {
            throw std::runtime_error("La cola está vacía.");
        }

        Nodo* temp = cabeza;
        Paciente paciente = temp->paciente;

        cabeza = cabeza->siguiente;
        if (cabeza != nullptr) {
            cabeza->anterior = nullptr;
        } else {
            cola = nullptr; // La lista quedó vacía
        }

        delete temp;
        return paciente;
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    size_t tamano() const {
        size_t tam = 0;
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            tam++;
            temp = temp->siguiente;
        }
        return tam;
    }

    ~ColaDePrioridad() {
        while (cabeza != nullptr) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

    void imprimirDesdeInicio() const {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            const Paciente& p = temp->paciente;
            std::cout << "Nombre: " << p.nombre << ", Edad: " << p.edad
                      << ", Peso: " << p.peso << ", Altura: " << p.altura <<",AC1="<< p.AC1 << std::endl;
            temp = temp->siguiente;
        }
    }

    void imprimirDesdeFinal() const {
        Nodo* temp = cola;
        while (temp != nullptr) {
            const Paciente& p = temp->paciente;
            std::cout << "Nombre: " << p.nombre << ", Edad: " << p.edad
                      << ", Peso: " << p.peso << ", Altura: " << p.altura << ",AC1=" <<p.AC1 << std::endl;
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

    void actualizar(const std::string& nombre, const Paciente& nuevo_paciente) {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            if (temp->paciente.nombre == nombre) {
                temp->paciente = nuevo_paciente;
                return;
            }
            temp = temp->siguiente;
        }
        std::cout << "Paciente con nombre " << nombre << " no encontrado." << std::endl;
    }

    void cargarDesdeArchivo(const std::string& nombre_archivo) {
        std::ifstream archivo(nombre_archivo);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo: " << nombre_archivo << std::endl;
            return;
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string nombre;
            int edad;
            float altura;
            int peso;
            float AC1;
            std::getline(ss, nombre, ',');
            ss >> edad;
            ss.ignore(); 
            ss >> altura;
            ss.ignore(); 
            ss >> peso;
            ss.ignore(); 
            ss >> AC1;



            Paciente paciente = {nombre, edad,altura, peso,AC1};
            agregar(paciente);
        }
        archivo.close();
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

void mostrarMenu() {
    std::cout << "Menu de opciones:" << std::endl;
    std::cout << "Para crear la lista de riego se tomara en cuenta los factores de riesgo de el IMC y la Azucar en sangre" << std::endl;
    std::cout << "1. Agregar paciente" << std::endl;
    std::cout << "2. Eliminar paciente" << std::endl;
    std::cout << "3. Imprimir lista desde el inicio" << std::endl;
    std::cout << "4. Imprimir lista desde el final" << std::endl;
    std::cout << "5. Actualizar paciente" << std::endl;
    std::cout << "6. Cargar pacientes desde archivo" << std::endl;
    std::cout << "7. Calcular promedios e IMC" << std::endl;
    std::cout << "8. Generar lista de prioridad para pacientes en riegos" << std::endl;
    std::cout << "9. Mostrar la lista de riesgo" << std::endl;
    std::cout << "10. Limpiar lista de riesgo" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Para que se muestre algo primero tiene que ingresar personas en la lista" << std::endl;
}

int main() {
    ListaDobleEnlazada lista;
    int opcion;


    do {
        mostrarMenu();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(); 

        switch (opcion) {
            case 1: {
                Paciente paciente;
                std::cout << "Nombre: ";
                std::getline(std::cin, paciente.nombre);
                std::cout << "Edad: ";
                std::cin >> paciente.edad;
                std::cout << "Peso: ";
                std::cin >> paciente.peso;
                std::cout << "Altura: ";
                std::cin >> paciente.altura;
                std::cin.ignore(); 
                lista.agregar(paciente);
                break;
            }
            case 2: {
                std::string nombre;
                std::cout << "Nombre del paciente a eliminar: ";
                std::getline(std::cin, nombre);
                lista.eliminar(nombre);
                break;
            }
            case 3: {
                lista.imprimirDesdeInicio();
                break;
            }
            case 4: {
                lista.imprimirDesdeFinal();
                break;
            }
            case 5: {
                std::string nombre;
                Paciente nuevo_paciente;
                std::cout << "Nombre del paciente a actualizar: ";
                std::getline(std::cin, nombre);
                std::cout << "Nuevo nombre: ";
                std::getline(std::cin, nuevo_paciente.nombre);
                std::cout << "Nueva edad: ";
                std::cin >> nuevo_paciente.edad;
                std::cout << "Nuevo peso: ";
                std::cin >> nuevo_paciente.peso;
                std::cout << "Nueva altura: ";
                std::cin >> nuevo_paciente.altura;
                std::cin.ignore(); // Ignorar el salto de línea restante
                lista.actualizar(nombre, nuevo_paciente);
                break;
            }
            case 6: {
                std::string archivo;
                std::cout << "Nombre del archivo CSV: ";
                std::getline(std::cin, archivo);
                lista.cargarDesdeArchivo(archivo);
                break;
            }
            case 7: {
                lista.calcularPromediosYIMC();
                break;
            }
            case 8:{
                  std::cout << "Saliendo del programa." << std::endl;


            }
            case 9: {
                std::cout << "Saliendo del programa." << std::endl;

            }
            case 10: {
                std::cout << "Saliendo del programa." << std::endl;

            }
            case 0:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Por favor, intente de nuevo." << std::endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}
