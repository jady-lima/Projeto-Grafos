#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// Função para imprimir a lista de adjacência
void imprimirLista(const vector<vector<int>>& lista, const vector<string>& rotulos) {
    cout << "\nLista de Adjacência:\n";
    for (size_t i = 0; i < lista.size(); ++i) {
        cout << rotulos[i] << ": ";
        for (int v : lista[i])
            cout << rotulos[v] << " ";
        cout << "\n";
    }
}
// Função para imprimir a matriz de adjacência
void imprimirMatriz(const vector<vector<int>>& matriz, const vector<string>& rotulos) {
    cout << "\nMatriz de Adjacência:\n   ";
    for (auto& r : rotulos)
        cout << r << " ";
    cout << "\n";
    for (size_t i = 0; i < matriz.size(); ++i) {
        cout << rotulos[i] << ": ";
        for (int val : matriz[i])
            cout << val << " ";
        cout << "\n";
    }
}
// Converte uma lista de adjacência em uma matriz de adjacência
vector<vector<int>> listaParaMatriz(const vector<vector<int>>& lista, bool direcionado) {
    int n = lista.size();
    // Inicializa a matriz com zeros
    vector<vector<int>> matriz(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int v : lista[i]) {
            matriz[i][v] = 1; // Marca a aresta de i para v
            if (!direcionado)
                matriz[v][i] = 1; // Se não for direcionado, marca a aresta inversa
        }
    }
    return matriz;
}

// Converte uma matriz de adjacência em uma lista de adjacência
vector<vector<int>> matrizParaLista(const vector<vector<int>>& matriz) {
    int n = matriz.size();
    vector<vector<int>> lista(n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matriz[i][j] == 1)
                lista[i].push_back(j); // Adiciona vizinho j à lista do vértice i

    return lista;
}
int main() {
    bool direcionado;
    int opcao, n;
    // escolhe se é grafo ou dígrafo
    cout << "O grafo é direcionado? (1 - Sim, 0 - Não): ";
    cin >> direcionado;

    cout << "Digite o número de vértices: ";
    cin >> n;
    vector<string> rotulos(n);
    unordered_map<string, int> indice;

    cout << "Digite os rótulos dos vértices (ex: A B C ou 1 2 3 ...):\n";
    for (int i = 0; i < n; ++i) {
        cin >> rotulos[i];
        indice[rotulos[i]] = i; // Mapeia o nome do vértice para sua posição no vetor
    }

    cout << "\nEscolha uma opção:\n";
    cout << "1 - Converter Matriz de Adjacência para Lista de Adjacência\n";
    cout << "2 - Converter Lista de Adjacência para Matriz de Adjacência\n";
    cout << "Opção: ";
    cin >> opcao;

    if (opcao == 1) {
        // --- PARTE DA CONVERSÃO: MATRIZ - LISTA ---
        vector<vector<int>> matriz(n, vector<int>(n));

        cout << "Digite a matriz (" << n << "x" << n << "):\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> matriz[i][j];

        auto lista = matrizParaLista(matriz); // Converte
        imprimirLista(lista, rotulos);        // exibe a lista de adjacência
    } 
    else if (opcao == 2) {
        //  --- PARTE DA CONVERSÃO: LISTA PARA MATRIZ ---
        int m;
        cout << "Digite o número de arestas: ";
        cin >> m;

        vector<vector<int>> lista(n);
        cout << "Digite as arestas (formato: origem destino):\n";
        for (int i = 0; i < m; ++i) {
            string u, v;
            cin >> u >> v;
            // adiciona aresta origem - destino
            lista[indice[u]].push_back(indice[v]);
            // Se não for direcionado, adiciona também destino - origem
            if (!direcionado)
                lista[indice[v]].push_back(indice[u]);
        }

        auto matriz = listaParaMatriz(lista, direcionado); // faz a conversao
        imprimirMatriz(matriz, rotulos);                   // mostra a matriz de adjacência
    }

    return 0;
}
