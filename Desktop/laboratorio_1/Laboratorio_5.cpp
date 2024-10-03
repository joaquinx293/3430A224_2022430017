#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
// basicamente use el codigo de arbol que ya tenia y lo fucione con lo que esta en educandus
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;
    int altura;

    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr), padre(nullptr), altura(1) {}
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

int altura(Nodo* nodo) {// esta parte la saque de el ejemplo del profesor 
    return nodo ? nodo->altura : 0;
}

int obtenerFactorEquilibrio(Nodo* nodo) {
    return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
}


void actualizarAltura(Nodo* nodo) {
    if (nodo) {
        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));
    }
}
Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;
    x->derecho = y;
    y->izquierdo = T2;
    actualizarAltura(y);
    actualizarAltura(x);

    return x; 
}
Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;
    y->izquierdo = x;
    x->derecho = T2;
    actualizarAltura(x);
    actualizarAltura(y);
    return y; 
}
Nodo* equilibrar(Nodo* nodo) {
    if (!nodo) return nullptr;

    actualizarAltura(nodo);

    int balance = obtenerFactorEquilibrio(nodo);
    if (balance > 1 && obtenerFactorEquilibrio(nodo->izquierdo) >= 0) {
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && obtenerFactorEquilibrio(nodo->derecho) <= 0) {
        return rotacionIzquierda(nodo);
    }
    if (balance > 1 && obtenerFactorEquilibrio(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && obtenerFactorEquilibrio(nodo->derecho) > 0) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}
Nodo* insertar(Nodo* raiz, int val) {
    if (raiz == nullptr) {
        return new Nodo(val);
    }

    if (val < raiz->valor) {
        raiz->izquierdo = insertar(raiz->izquierdo, val);
        raiz->izquierdo->padre = raiz;
    } else if (val > raiz->valor) {
        raiz->derecho = insertar(raiz->derecho, val);
        raiz->derecho->padre = raiz;
    } else {
        cout << "El valor " << val << " ya existe en el árbol." << endl;
        return raiz;
    }

    return equilibrar(raiz);
}
Nodo* eliminar(Nodo* raiz, int val) {
    if (raiz == nullptr) {
        return raiz;
    }

    if (val < raiz->valor) {
        raiz->izquierdo = eliminar(raiz->izquierdo, val);
    } else if (val > raiz->valor) {
        raiz->derecho = eliminar(raiz->derecho, val);
    } else {
        if (raiz->izquierdo == nullptr || raiz->derecho == nullptr) {
            Nodo* temp = raiz->izquierdo ? raiz->izquierdo : raiz->derecho;
            if (!temp) {
                temp = raiz;
                raiz = nullptr;
            } else {
                *raiz = *temp;
            }
            delete temp;
        } else {
            Nodo* temp = raiz->derecho;
            while (temp->izquierdo) {
                temp = temp->izquierdo;
            }
            raiz->valor = temp->valor;
            raiz->derecho = eliminar(raiz->derecho, temp->valor);
        }
    }

    if (!raiz) return raiz;

    return equilibrar(raiz); 
}
void preorden(Nodo* raiz) {
    if (raiz != nullptr) {
        cout << raiz->valor << " ";
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

void inorden(Nodo* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierdo);
        cout << raiz->valor << " ";
        inorden(raiz->derecho);
    }
}

void posorden(Nodo* raiz) {
    if (raiz != nullptr) {
        posorden(raiz->izquierdo);
        posorden(raiz->derecho);
        cout << raiz->valor << " ";
    }
}

void generarDOT(Nodo* raiz, ofstream& archivo) {
    if (raiz == nullptr) return;
    archivo << raiz->valor << " [label=\"" << raiz->valor << " (FE=" << obtenerFactorEquilibrio(raiz) << ")\"];\n";
    if (raiz->izquierdo != nullptr) {
        archivo << raiz->valor << " -> " << raiz->izquierdo->valor << ";\n";
        generarDOT(raiz->izquierdo, archivo);
    }
    if (raiz->derecho != nullptr) {
        archivo << raiz->valor << " -> " << raiz->derecho->valor << ";\n";
        generarDOT(raiz->derecho, archivo);
    }
}

void generarArchivoDOT(Nodo* raiz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    archivo << "digraph G {" << endl;
    archivo << "    node [style=filled, fillcolor=yellow];" << endl;
    if (raiz != nullptr) {
        generarDOT(raiz, archivo);
    }
    archivo << "}" << endl;
    archivo.close();
    cout << "Archivo DOT generado: " << nombreArchivo << endl;
}

void generarImagen(const string& archivoDOT, const string& archivoImagen) {
    string comando = "dot -Tpng " + archivoDOT + " -o " + archivoImagen;
    system(comando.c_str());
    cout << "Imagen generada: " << archivoImagen << endl;
}

void mostrarImagen(const string& archivoImagen) {
    string comando = "start " + archivoImagen;
    system(comando.c_str());
}

int main() {
    Nodo* raiz = nullptr;
    int opcion, valor;
    raiz = insertar(raiz, 60);
    raiz = insertar(raiz, 40);
    raiz = insertar(raiz, 45);
    raiz = insertar(raiz, 75);
    raiz = insertar(raiz, 90);
    raiz = insertar(raiz, 68);
    raiz = insertar(raiz, 97);

    do {
        cout << "\nMenu:\n";
        cout << "1. Insertar numero\n";
        cout << "2. Eliminar numero\n";
        cout << "3. Mostrar Preorden\n";
        cout << "4. Mostrar Inorden\n";
        cout << "5. Mostrar Posorden\n";
        cout << "6. Generar imagen del arbol\n";
        cout << "7. Borrar todo el arbol\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese el valor a insertar: ";
                cin >> valor;
                raiz = insertar(raiz, valor);
                break;
            case 2:
                cout << "Ingrese el valor a eliminar: ";
                cin >> valor;
                raiz = eliminar(raiz, valor);
                break;
            case 3:
                preorden(raiz);
                cout << endl;
                break;
            case 4:
                inorden(raiz);
                cout << endl;
                break;
            case 5:
                posorden(raiz);
                cout << endl;
                break;
            case 6:
                generarArchivoDOT(raiz, "arbol.dot");
                generarImagen("arbol.dot", "arbol.png");
                mostrarImagen("arbol.png");
                break;
            case 7:
                break;
        }
    } while(opcion != 8);

    return 0;
}
