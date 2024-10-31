#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <limits>

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 20;// aqui es el tamaño de la tabla en el caso del codigo 20 

    struct Hashvacio {// aqui se establece la estructura que almacena cada entrada 
        int key;
        bool isOccupied;

        Hashvacio() : key(0), isOccupied(false) {}
    };

    Hashvacio table[TABLE_SIZE];
    list<int> chainTable[TABLE_SIZE];
    char collisionMethod;

    int Hash(int key) {
        return key % TABLE_SIZE;
    }
    // Segunda función hash para el método D 
    int Hash2(int key) {
        return 7 - (key % 7);// 7 es un número primo menor que el tamaño de la tabla
    }

public:
    HashTable(char method) : collisionMethod(method) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].isOccupied = false;
        }
    }

    void insert(int key) {
        int originalPos = Hash(key);
        cout << "\nIntentando insertar " << key << " en la posicion " << originalPos << endl;

        switch (collisionMethod) {
            case 'L':
                insertLinearProbing(key, originalPos);
                break;
            case 'C':
                insertQuadraticProbing(key, originalPos);
                break;
            case 'D':
                insertDoubleHashing(key, originalPos);
                break;
            case 'E':
                insertChaining(key, originalPos);
                break;
            default:
                cout << "Metodo de colision no valido." << endl;
        }

        displayTable();
    }

    bool remove(int key) {
        int originalPos = Hash(key);
        cout << "\nIntentando eliminar " << key << endl;

        switch (collisionMethod) {
            case 'L':
                return removeLinearProbing(key, originalPos);
            case 'C':
                return removeQuadraticProbing(key, originalPos);
            case 'D':
                return removeDoubleHashing(key, originalPos);
            case 'E':
                return removeChaining(key, originalPos);
            default:
                cout << "Metodo de colision no valido." << endl;
                return false;
        }
    }

private:
    void insertLinearProbing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;

        while (table[pos].isOccupied) {
            cout << "Colision en posicion " << pos << endl;
            pos = (pos + 1) % TABLE_SIZE;
            displacement++;

            if (displacement >= TABLE_SIZE) {
                cout << "Error: Tabla llena" << endl;
                return;
            }
        }

        table[pos].key = key;
        table[pos].isOccupied = true;

        if (displacement > 0) {
            cout << "Desplazamiento final: " << displacement << " posiciones" << endl;
        }
    }

    void insertQuadraticProbing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;

        while (table[pos].isOccupied) {
            cout << "Colision en posicion " << pos << endl;
            displacement++;
            pos = (originalPos + displacement * displacement) % TABLE_SIZE;

            if (displacement >= TABLE_SIZE) {
                cout << "Error: Tabla llena" << endl;
                return;
            }
        }

        table[pos].key = key;
        table[pos].isOccupied = true;

        if (displacement > 0) {
            cout << "Desplazamiento final: " << displacement << " posiciones" << endl;
        }
    }

    void insertDoubleHashing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;
        int step = Hash2(key);

        while (table[pos].isOccupied) {
            cout << "Colision en posicion " << pos << endl;
            displacement++;
            pos = (originalPos + displacement * step) % TABLE_SIZE;

            if (displacement >= TABLE_SIZE) {
                cout << "Error: Tabla llena" << endl;
                return;
            }
        }

        table[pos].key = key;
        table[pos].isOccupied = true;

        if (displacement > 0) {
            cout << "Desplazamiento final: " << displacement << " posiciones" << endl;
        }
    }

    void insertChaining(int key, int pos) {
        chainTable[pos].push_back(key);
    }

    bool removeLinearProbing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;

        while (table[pos].isOccupied && displacement < TABLE_SIZE) {
            if (table[pos].key == key) {
                table[pos].isOccupied = false;
                cout << "Valor eliminado de la posicion " << pos << endl;
                displayTable();
                return true;
            }
            pos = (pos + 1) % TABLE_SIZE;
            displacement++;
        }
        cout << "Valor no encontrado" << endl;
        return false;
    }

    bool removeQuadraticProbing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;

        while (table[pos].isOccupied && displacement < TABLE_SIZE) {
            if (table[pos].key == key) {
                table[pos].isOccupied = false;
                cout << "Valor eliminado de la posicion " << pos << endl;
                displayTable();
                return true;
            }
            displacement++;
            pos = (originalPos + displacement * displacement) % TABLE_SIZE;
        }
        cout << "Valor no encontrado" << endl;
        return false;
    }

    bool removeDoubleHashing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;
        int step = Hash2(key);

        while (table[pos].isOccupied && displacement < TABLE_SIZE) {
            if (table[pos].key == key) {
                table[pos].isOccupied = false;
                cout << "Valor eliminado de la posicion " << pos << endl;
                displayTable();
                return true;
            }
            displacement++;
            pos = (originalPos + displacement * step) % TABLE_SIZE;
        }
        cout << "Valor no encontrado" << endl;
        return false;
    }

    bool removeChaining(int key, int pos) {
        auto& chain = chainTable[pos];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (*it == key) {
                chain.erase(it);
                cout << "Valor eliminado de la posicion " << pos << endl;
                displayTable();
                return true;
            }
        }
        cout << "Valor no encontrado" << endl;
        return false;
    }

public:
    void search(int key) {
        int originalPos = Hash(key);// de aqui a abajo es para identificar el metodo que la persona ingrese
        cout << "\nBuscando " << key << ". Posicion inicial de busqueda: " << originalPos << endl;

        switch (collisionMethod) {
            case 'L':
                searchLinearProbing(key, originalPos);
                break;
            case 'C':
                searchQuadraticProbing(key, originalPos);
                break;
            case 'D':
                searchDoubleHashing(key, originalPos);
                break;
            case 'E':
                searchChaining(key, originalPos);
                break;
            default:
                cout << "Metodo de colision no valido." << endl;
        }
    }

private:
    void searchLinearProbing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;

        while (table[pos].isOccupied) {
            if (table[pos].key == key) {
                cout << "Encontrado en posicion " << pos << endl;
                if (displacement > 0) {
                    cout << "Desplazamiento final: " << displacement << " posiciones" << endl;
                }
                return;
            }
            pos = (pos + 1) % TABLE_SIZE;
            displacement++;

            if (displacement >= TABLE_SIZE) break;
        }
        cout << "No encontrado" << endl;
    }

    void searchQuadraticProbing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;

        while (table[pos].isOccupied) {
            if (table[pos].key == key) {
                cout << "Encontrado en posicion " << pos << endl;
                if (displacement > 0) {
                    cout << "Desplazamiento final: " << displacement << " posiciones" << endl;
                }
                return;
            }
            displacement++;
            pos = (originalPos + displacement * displacement) % TABLE_SIZE;

            if (displacement >= TABLE_SIZE) break;
        }
        cout << "No encontrado" << endl;
    }

    void searchDoubleHashing(int key, int originalPos) {
        int pos = originalPos;
        int displacement = 0;
        int step = Hash2(key);

        while (table[pos].isOccupied) {
            if (table[pos].key == key) {
                cout << "Encontrado en posicion " << pos << endl;
                if (displacement > 0) {
                    cout << "Desplazamiento final: " << displacement << " posiciones" << endl;
                }
                return;
            }
            displacement++;
            pos = (originalPos + displacement * step) % TABLE_SIZE;

            if (displacement >= TABLE_SIZE) break;
        }
        cout << "No encontrado" << endl;
    }

    void searchChaining(int key, int pos) {
        for (int value : chainTable[pos]) {
            if (value == key) {
                cout << "Encontrado en la posicion " << pos << " de la lista" << endl;
                return;
            }
        }
        cout << "No encontrado" << endl;
    }

    void displayTable() {
        cout << "\nContenido de la tabla:" << endl;

        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            if (collisionMethod == 'E') {
                if (chainTable[i].empty()) {
                    cout << "[]";
                } else {
                    cout << "[ ";
                    for (int value : chainTable[i]) {
                        cout << value << " ";
                    }
                    cout << "]";
                }
            } else {
                if (table[i].isOccupied) {
                    cout << table[i].key;
                } else {
                    cout << "-";
                }
            }
            cout << endl;
        }
    }
};

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(int argc, char* argv[]) {
    if (argc != 2 || string(argv[1]).length() != 1 ||
        string("LCDE").find(argv[1][0]) == string::npos) {
        cout << "Uso: " << argv[0] << " {L|C|D|E}" << endl;
        cout << "L: Prueba Lineal" << endl;
        cout << "C: Prueba Cuadratica" << endl;
        cout << "D: Doble Hash" << endl;
        cout << "E: Encadenamiento" << endl;
        return 1;
    }

    HashTable hashTable(argv[1][0]);
    int values[] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};// valores que dice la guia 
    int n = sizeof(values) / sizeof(values[0]);

    cout << "Insertando valores iniciales..." << endl;
    for (int i = 0; i < n; i++) {
        hashTable.insert(values[i]);
    }

    int value;
    char option;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Insertar nuevo valor" << endl;
        cout << "2. Eliminar valor" << endl;
        cout << "3. Buscar valor" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> option;
        limpiarBuffer();

        switch(option) {
            case '1':
                cout << "Ingrese el valor a insertar: ";
                cin >> value;
                hashTable.insert(value);
                break;
                
            case '2':
                cout << "Ingrese el valor a eliminar: ";
                cin >> value;
                hashTable.remove(value);
                break;
                
            case '3':
                cout << "Ingrese el valor a buscar: ";
                cin >> value;
                hashTable.search(value);
                break;
                
            case '4':
                cout << "Programa finalizado." << endl;
                break;
                
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (option != '4');

    return 0;
}