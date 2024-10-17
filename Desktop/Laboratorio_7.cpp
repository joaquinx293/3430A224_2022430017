#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
using namespace std;

const int INF = INT_MAX;

// Función para generar el archivo .dot para Graphviz
void generar_dot(const vector<vector<int>>& grafo, int N, const vector<char>& nodos, const string& nombre_archivo) {
    ofstream archivo(nombre_archivo);
    archivo << "graph G {\n";
    archivo << "graph [rankdir=LR];\n";
    archivo << "node [style=filled, fillcolor=yellow];\n";

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (grafo[i][j] != INF) {
                archivo << nodos[i] << " -- " << nodos[j] << " [label=" << grafo[i][j] << "];\n";
            }
        }
    }
    archivo << "}\n";
    archivo.close();
}

// Función para imprimir la matriz de distancias
void imprimir_matriz(const vector<vector<int>>& grafo, int N, const vector<char>& nodos) {
    cout << "\nMatriz de distancias:\n    ";
    for (int i = 0; i < N; i++) {
        cout << nodos[i] << "  ";
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << nodos[i] << " ";
        for (int j = 0; j < N; j++) {
            if (grafo[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << grafo[i][j] << "   ";
            }
        }
        cout << endl;
    }
}

// Implementación del algoritmo de Prim para encontrar el árbol de expansión mínima
vector<vector<int>> algoritmo_prim(const vector<vector<int>>& grafo, int N) {
    vector<vector<int>> arbol_minimo(N, vector<int>(N, INF)); // Matriz para el árbol de expansión mínima
    vector<bool> en_arbol(N, false); // Marcar nodos ya incluidos en el árbol
    vector<int> min_cost(N, INF); // Almacenar el costo mínimo para llegar a cada nodo
    vector<int> padre(N, -1); // Almacenar el nodo padre

    min_cost[0] = 0; // Empezamos desde el nodo 0

    for (int i = 0; i < N; i++) {
        int u = -1;

        // Encontrar el nodo no incluido con el costo mínimo
        for (int j = 0; j < N; j++) {
            if (!en_arbol[j] && (u == -1 || min_cost[j] < min_cost[u])) {
                u = j;
            }
        }

        en_arbol[u] = true; // Añadir el nodo al árbol

        // Actualizar las distancias mínimas de los nodos vecinos
        for (int v = 0; v < N; v++) {
            if (grafo[u][v] != INF && !en_arbol[v] && grafo[u][v] < min_cost[v]) {
                min_cost[v] = grafo[u][v];
                padre[v] = u; // Actualizar el padre del nodo
            }
        }
    }

    // Crear el árbol de expansión mínima
    for (int i = 1; i < N; i++) {
        if (padre[i] != -1) {
            arbol_minimo[i][padre[i]] = arbol_minimo[padre[i]][i] = grafo[i][padre[i]];
        }
    }

    return arbol_minimo; // Retornar la matriz del árbol mínimo
}

int main() {
    int N;
    cout << "Ingrese el número de nodos: ";
    cin >> N;

    vector<vector<int>> grafo(N, vector<int>(N, INF));
    vector<char> nodos(N);

    // Asignar automáticamente nombres de nodos en orden alfabético
    for (int i = 0; i < N; i++) {
        nodos[i] = 'A' + i;  // Asignar 'A', 'B', 'C', etc.
    }

    cout << "Ingrese las distancias entre los nodos. Si no hay conexión, ingrese 0.\n";
    
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int distancia;
            cout << "Ingrese la distancia entre " << nodos[i] << " y " << nodos[j] << ": ";
            cin >> distancia;

            if (distancia == 0) {
                grafo[i][j] = grafo[j][i] = INF;  // Si no hay conexión, se usa "INF"
            } else {
                grafo[i][j] = grafo[j][i] = distancia;  // Asignar el mismo valor en ambas direcciones
            }
        }
    }

    // Imprimir la matriz original
    imprimir_matriz(grafo, N, nodos);

    // Generar el archivo .dot para el grafo original
    generar_dot(grafo, N, nodos, "grafo_original.dot");

    // Ejecutar el algoritmo de Prim
    vector<vector<int>> arbol_minimo = algoritmo_prim(grafo, N);

    // Imprimir la matriz del árbol de expansión mínima
    cout << "\nMatriz del árbol de expansión mínima:\n";
    imprimir_matriz(arbol_minimo, N, nodos);

    // Generar el archivo .dot para el árbol de expansión mínima
    generar_dot(arbol_minimo, N, nodos, "arbol_minimo.dot");

    // Crear las imágenes con Graphviz
    system("dot -Tpng -ografo_original.png grafo_original.dot");
    system("dot -Tpng -oarbol_minimo.png arbol_minimo.dot");
    system("start grafo_original.png");
    system("start arbol_minimo.png");

    return 0;
}
