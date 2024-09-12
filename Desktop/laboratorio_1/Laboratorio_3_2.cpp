#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <iomanip> // esto para hacer la salida como tabla
using namespace std;


class Contenedor {
public:
    int numero;
    string empresa;

    Contenedor(int n, string e) : numero(n), empresa(e) {}
};


class Puerto {
private:
    vector<stack<Contenedor>> pilas; 
    int maxContenedoresPorPila;

public:
    
    Puerto(int m, int n) : maxContenedoresPorPila(n) {
        pilas.resize(m); 
    }

   
    bool agregarContenedor(Contenedor contenedor) {
        for (auto& pila : pilas) {
            if (pila.size() < maxContenedoresPorPila) {
                pila.push(contenedor);
                cout << "Contenedor " << contenedor.numero << " de la empresa " 
                     << contenedor.empresa << " agregado.\n";
                return true;
            }
        }
        cout << "No hay espacio en las pilas para más contenedores.\n";
        return false;
    }

    
    void retirarContenedor(int numero) {
        bool encontrado = false;
        for (auto& pila : pilas) {
            stack<Contenedor> tempPila;

            
            while (!pila.empty()) {
                Contenedor top = pila.top();
                pila.pop();

                if (top.numero == numero) {
                    cout << "Contenedor " << top.numero << " de la empresa " 
                         << top.empresa << " retirado.\n";
                    encontrado = true;
                    break;
                } else {
                    tempPila.push(top);
                }
            }

            
            while (!tempPila.empty()) {
                pila.push(tempPila.top());
                tempPila.pop();
            }

            if (encontrado) return;
        }

        if (!encontrado) {
            cout << "El contenedor " << numero << " no se encontró.\n";
        }
    }

    
    void moverContenedor(int numero, int pilaOrigen, int pilaDestino) {
        if (pilaOrigen < 1 || pilaDestino < 1 || 
            pilaOrigen > pilas.size() || pilaDestino > pilas.size()) {
            cout << "Pilas inválidas.\n";
            return;
        }

        pilaOrigen--; 
        pilaDestino--;

        stack<Contenedor> tempPila;
        bool encontrado = false;

        
        while (!pilas[pilaOrigen].empty()) {
            Contenedor top = pilas[pilaOrigen].top();
            pilas[pilaOrigen].pop();

            if (top.numero == numero) {
                if (pilas[pilaDestino].size() < maxContenedoresPorPila) {
                    pilas[pilaDestino].push(top);
                    cout << "Contenedor " << numero << " movido de Pila " 
                         << pilaOrigen + 1 << " a Pila " << pilaDestino + 1 << ".\n";
                } else {
                    cout << "La pila destino está llena. No se pudo mover el contenedor.\n";
                    pilas[pilaOrigen].push(top);
                }
                encontrado = true;
                break;
            } else {
                tempPila.push(top);
            }
        }

        
        while (!tempPila.empty()) {
            pilas[pilaOrigen].push(tempPila.top());
            tempPila.pop();
        }

        if (!encontrado) {
            cout << "El contenedor " << numero << " no se encontró en la pila de origen.\n";
        }
    }

    
    void mostrarEstado() {
        cout << "\nEstado del puerto (Pilas):\n";
        
        
        for (int i = 0; i < pilas.size(); i++) {
            cout << " Pila " << setw(3) << i + 1 << " ";
        }
        cout << "\n";

        
        vector<stack<Contenedor>> tempPilas = pilas;

        
        for (int nivel = maxContenedoresPorPila; nivel > 0; nivel--) {
            for (int i = 0; i < tempPilas.size(); i++) {
                if (tempPilas[i].size() >= nivel) {
                    Contenedor cont = tempPilas[i].top();
                    tempPilas[i].pop();
                    cout << "| " << setw(2) << cont.numero << "/" << setw(5) << cont.empresa << " ";
                } else {
                    cout << "| " << setw(10) << " ";
                }
            }
            cout << "|\n";
        }
        cout << "\n";
    }
};

int main() {
    int m, n;
    cout << "Ingrese el número máximo de pilas: ";
    cin >> m;
    cout << "Ingrese el número máximo de contenedores por pila: ";
    cin >> n;

    Puerto puerto(m, n);

    int opcion;
    do {
        cout << "tenga cuidado con agregar valores que sean letras como numero de contenedor\n";
        cout << "Use un metodo donde tu creas una tabla y tu agregas los valores\n";
        cout << "\n1. Agregar contenedor\n";
        cout << "2. Retirar contenedor\n";
        cout << "3. Mover contenedor\n";
        cout << "4. Mostrar estado del puerto\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int numero;
            string empresa;
            cout << "Ingrese el número del contenedor: ";
            cin >> numero;
            cout << "Ingrese el nombre de la empresa: ";
            cin >> empresa;
            puerto.agregarContenedor(Contenedor(numero, empresa));
            puerto.mostrarEstado();
            break;
        }
        case 2: {
            int numero;
            cout << "Ingrese el número del contenedor a retirar: ";
            cin >> numero;
            puerto.retirarContenedor(numero);
            puerto.mostrarEstado();
            break;
        }
        case 3: {
            int numero, origen, destino;
            cout << "Ingrese el número del contenedor a mover: ";
            cin >> numero;
            cout << "Ingrese el número de la pila de origen: ";
            cin >> origen;
            cout << "Ingrese el número de la pila de destino: ";
            cin >> destino;
            puerto.moverContenedor(numero, origen, destino);
            puerto.mostrarEstado();
            break;
        }
        case 4:
            puerto.mostrarEstado();
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 0);

    return 0;
}
