#include <iostream>
using namespace std;
#include <fstream>
#include <cstdlib>

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr) {}
};

Nodo* insertar(Nodo* raiz, int val) {  // funcion para insertar elementos
    if (raiz == nullptr) {
        return new Nodo(val);
    }
    if (val < raiz->valor) {
        raiz->izquierdo = insertar(raiz->izquierdo, val);
    } else if (val > raiz->valor) {
        raiz->derecho = insertar(raiz->derecho, val);
    } else {
        cout << "El valor " << val << " ya existe en el árbol." << endl;// condiconal pare saber si el numero ya existe 
    }
    return raiz;
}

void mostrarImagen(const string& archivoImagen) {
    string comando = "start " + archivoImagen;
    system(comando.c_str());
}

void preorden(Nodo* raiz) {
    if (raiz != nullptr) {
        cout << raiz->valor << " ";
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

void generarDOT(Nodo* raiz, ofstream& archivo) {
    if (raiz == nullptr) return;
    if (raiz->izquierdo != nullptr) {
        archivo << "    " << raiz->valor << " -> " << raiz->izquierdo->valor << ";" << endl;
        generarDOT(raiz->izquierdo, archivo);
    }
    if (raiz->derecho != nullptr) {
        archivo << "    " << raiz->valor << " -> " << raiz->derecho->valor << ";" << endl;
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
void borrarTodo(Nodo* &raiz) {
    if (raiz == nullptr) {
        return;
    }

    // Primero borramos los subárboles izquierdo y derecho
    borrarTodo(raiz->izquierdo);
    borrarTodo(raiz->derecho);

    // Luego borramos el nodo actual
    cout << "Eliminando nodo con valor: " << raiz->valor << endl;
    delete raiz;
    raiz = nullptr;
}

Nodo* encontrarMinimo(Nodo* raiz) {
    while (raiz->izquierdo != nullptr) {
        raiz = raiz->izquierdo;
    }
    return raiz;
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
        if (raiz->izquierdo == nullptr) {
            Nodo* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == nullptr) {
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }
        Nodo* temp = encontrarMinimo(raiz->derecho);
        raiz->valor = temp->valor;
        raiz->derecho = eliminar(raiz->derecho, temp->valor);
    }
    return raiz;
}

int main() {
    Nodo* raiz = nullptr;
    int opcion, valor;

    raiz = insertar(raiz, 120);// valores del arbol ya hecho 
    raiz = insertar(raiz, 87);
    raiz = insertar(raiz, 140);
    raiz = insertar(raiz, 43);
    raiz = insertar(raiz, 99);

    do {
        cout << "\nMenu:\n";// menu de opciones 
        cout << "1. Insertar numero\n";
        cout << "2. Eliminar numero\n";
        cout << "3. Mostrar Preorden\n";
        cout << "4. Mostrar Inorden\n";
        cout << "5. Mostrar Posorden\n";
        cout << "6. Generar imagen del arbol\n";
        cout << "7. Borra todo el arbol\n";
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
                borrarTodo(raiz);  // Llamada a la función que borra todo el árbol
                cout << "El arbol ha sido eliminado completamente.\n";
                break;
        }
    } while(opcion != 8);

    return 0;
}
