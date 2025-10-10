#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

// Função para imprimir a lista de adjacência do grafo
void imprimirLista(const vector<vector<int>>& lista, const vector<string>& rotulos) {
    cout << "\nLista de Adjacência:\n";
    for (size_t i = 0; i < lista.size(); ++i) {
        cout << rotulos[i] << ": ";
        // Percorre todos os vizinhos do vértice
        for (int viz : lista[i])
            cout << rotulos[viz] << " ";
        cout << "\n";
    }
}
// Função para imprimir a matriz de adjacência do grafo
void imprimirMatriz(const vector<vector<int>>& matriz, const vector<string>& rotulos) {
    cout << "\nMatriz de Adjacência:\n   ";
    // Cabeçalho com os rótulos
    for (auto& r : rotulos)
        cout << r << " ";
    cout << "\n";
    // percorre  matriz exibindo 0 e 1 conforme a existência de arestas
    for (size_t i = 0; i < matriz.size(); ++i) {
        cout << rotulos[i] << ": ";
        for (int val : matriz[i])
            cout << val << " ";
        cout << "\n";
    }
}
// Converte lista de adjacência em uma matriz de adjacência
vector<vector<int>> listaParaMatriz(const vector<vector<int>>& lista, bool direcionado) {
    int n = lista.size();
    vector<vector<int>> matriz(n, vector<int>(n, 0)); // Inicializa matriz n x n com zeros

    for (int i = 0; i < n; ++i)
        for (int viz : lista[i]) {
            matriz[i][viz] = 1; // Cria a aresta i -> viz
            if (!direcionado)
                matriz[viz][i] = 1; // Se não for direcionado, cria a aresta inversa viz → i
        }

    return matriz;
}

int main() {
    bool direcionado;
    int m;
    // pergunta se é grafo ou dígrafo
    cout << "O grafo é direcionado? (1 - Sim, 0 - Não): ";
    cin >> direcionado;

    cout << "\nDigite o número de arestas: ";
    cin >> m;

    // Usa map para manter os vértices ordenados alfabeticamente (ou numericamente)
    map<string, vector<string>> listaOriginal;

    cout << "Digite as arestas (formato: origem destino):\n";
    for (int i = 0; i < m; ++i) {
        string u, v;
        cin >> u >> v;
        listaOriginal[u].push_back(v); // Adiciona aresta u -> v
        if (!direcionado)
            listaOriginal[v].push_back(u); // Se não direcionado, também v -> u
    }

    // Mapeia cada vértice (string) para um índice inteiro
    unordered_map<string, int> idx;
    vector<string> rotulos;
    int index = 0;

    // Percorre todos os vértices e vizinhos para garantir que todos estejam mapeados
    for (auto& [v, vizinhos] : listaOriginal) {
        if (!idx.count(v)) { // Se o vértice ainda não tiver índice
            idx[v] = index++;
            rotulos.push_back(v);
        }
        for (auto& viz : vizinhos) {
            if (!idx.count(viz)) { // Se o vizinho ainda não tiver índice
                idx[viz] = index++;
                rotulos.push_back(viz);
            }
        }
    }
    // Cria lista de adjacência numérica (baseada em índices)
    vector<vector<int>> lista(idx.size());
    for (auto& [v, vizinhos] : listaOriginal)
        for (auto& viz : vizinhos)
            lista[idx[v]].push_back(idx[viz]);

    cout << "\nGrafo inicial:";
    imprimirLista(lista, rotulos);

    // --- PARTE DE INCLUSÃO DE NOVO VÉRTICE ---
    string novoVertice;
    cout << "\nDigite o rótulo do novo vértice: ";
    cin >> novoVertice;

    // Adiciona o novo vértice aos vetores de controle
    rotulos.push_back(novoVertice);
    idx[novoVertice] = lista.size();
    lista.push_back({}); // Cria lista vazia para o novo vértice

    int qntArestas;
    cout << "Quantas arestas o novo vértice possui? ";
    cin >> qntArestas;
    cout << "Digite as arestas (formato: origem destino) envolvendo o novo vértice:\n";
    for (int i = 0; i < qntArestas; ++i) {
        string u, v;
        cin >> u >> v;
        // Garante que os vértices informados existam no mapeamento
        if (!idx.count(u)) {
            idx[u] = lista.size();
            rotulos.push_back(u);
            lista.push_back({});
        }
        if (!idx.count(v)) {
            idx[v] = lista.size();
            rotulos.push_back(v);
            lista.push_back({});
        }
        // Adiciona aresta u -> v
        lista[idx[u]].push_back(idx[v]);
        if (!direcionado)
            lista[idx[v]].push_back(idx[u]); // Aresta inversa se não direcionado
    }

    // Exibe lista final
    cout << "\nLista de Adjacência após inclusão:\n";
    imprimirLista(lista, rotulos);
    // Converte a lista atualizada para matriz e exibe
    auto matriz = listaParaMatriz(lista, direcionado);
    imprimirMatriz(matriz, rotulos);

    return 0;
}
