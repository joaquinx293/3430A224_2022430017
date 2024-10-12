#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
using namespace std;

// Constante para representar distancias infinitas
const int INF = INT_MAX;

// Función para imprimir el grafo en formato .dot y generar la imagen con Graphviz
void imprimir_grafo(const vector<vector<int>>& grafo, int N, const vector<char>& nodos) {
    ofstream archivo("grafo.dot");
    archivo << "digraph G {\n";
    archivo << "graph [rankdir=LR];\n";
    archivo << "node [style=filled, fillcolor=yellow];\n";

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grafo[i][j] != INF && i != j) {
                archivo << nodos[i] << " -> " << nodos[j] << " [label=" << grafo[i][j] << "];\n";
            }
        }
    }
    archivo << "}\n";
    archivo.close();
    // Comando para generar la imagen y abrirla (Windows)
    system("dot -Tpng -ografo.png grafo.dot");
    system("start grafo.png");
}

// Función para imprimir la matriz de distancias
void imprimir_matriz(const vector<vector<int>>& grafo, int N, const vector<char>& nodos) {
    cout << "\nMatriz de distancias:\n    ";  // Imprimir encabezado con los nombres de los nodos
    for (int i = 0; i < N; i++) {
        cout << nodos[i] << "  ";  // Imprimir nombres de los nodos en la fila superior
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << nodos[i] << " ";  // Imprimir el nombre del nodo en la columna izquierda
        for (int j = 0; j < N; j++) {
            if (grafo[i][j] == INF) {
                cout << "INF ";  // Si no hay conexión, imprimir "INF"
            } else {
                cout << grafo[i][j] << "   ";  // Imprimir la distancia si existe
            }
        }
        cout << endl;
    }
}

// Implementación del algoritmo de Dijkstra
void dijkstra(const vector<vector<int>>& grafo, int N, int inicio, vector<char>& nodos) {
    vector<int> dist(N, INF);  // Vector para almacenar las distancias mínimas
    vector<bool> visitado(N, false);  // Vector para marcar los nodos ya visitados
    dist[inicio] = 0;  // La distancia al nodo de inicio es 0

    for (int i = 0; i < N; i++) {
        int u = -1;
        // Buscar el nodo no visitado con la distancia más pequeña
        for (int j = 0; j < N; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;  // Si no hay más nodos alcanzables, terminar

        visitado[u] = true;

        // Actualizar las distancias a los nodos vecinos de u
        for (int v = 0; v < N; v++) {
            if (grafo[u][v] != INF && !visitado[v] && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }

    // Imprimir las distancias desde el nodo de inicio
    cout << "\nDistancias desde el nodo " << nodos[inicio] << ":\n";
    for (int i = 0; i < N; i++) {
        if (dist[i] == INF)
            cout << nodos[i] << ": INF ";
        else
            cout << nodos[i] << ": " << dist[i] << " ";
    }
    cout << endl;

    imprimir_grafo(grafo, N, nodos);
}

int main() {
    int N;
    cout << "Ingrese el número de nodos: ";
    cin >> N;

    vector<vector<int>> grafo(N, vector<int>(N, INF));  // Matriz de distancias
    vector<char> nodos(N);  // Vector para almacenar los nombres de los nodos

    cout << "Ingrese los nombres de los nodos (por ejemplo A B C D):\n";
    for (int i = 0; i < N; i++) {
        cin >> nodos[i];
    }

    cout << "Ingrese las distancias entre los nodos. Si no hay conexión, ingrese -1.\n";
    
    // Llenar la matriz de distancias preguntando nodo por nodo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                grafo[i][j] = 0;  // La distancia de un nodo consigo mismo es 0
                continue;
            }
            int distancia;
            cout << "Ingrese la distancia de " << nodos[i] << " a " << nodos[j] << ": ";
            cin >> distancia;

            if (distancia == -1) {
                grafo[i][j] = INF;  // Si no hay conexión, se usa "INF"
            } else {
                grafo[i][j] = distancia;
            }
        }
    }

    // Imprimir la matriz de distancias ingresada
    imprimir_matriz(grafo, N, nodos);

    // Leer el nodo de origen para el algoritmo de Dijkstra
    char inicio;
    cout << "Ingrese el nodo de origen: ";
    cin >> inicio;

    int inicio_idx = -1;
    for (int i = 0; i < N; i++) {
        if (nodos[i] == inicio) {
            inicio_idx = i;
            break;
        }
    }

    if (inicio_idx == -1) {
        cout << "Nodo de origen no válido." << endl;
        return 1;
    }

    // Ejecutar el algoritmo de Dijkstra
    dijkstra(grafo, N, inicio_idx, nodos);

    return 0;
}
