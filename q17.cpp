#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <iomanip>
using namespace std;


 // Recebe um conjunto de arestas e um indicador de direcionamento, constrói e imprime a matriz de incidência do grafo.
void gerarMatrizIncidencia(const vector<pair<string, string>>& arestas, bool direcionado) {
    // Coletar todos os vértices únicos
    set<string> verticesSet;
    for (auto& a : arestas) {
        verticesSet.insert(a.first);
        verticesSet.insert(a.second);
    }
    // Converter o conjunto para vetor (continua em ordem alfabética)
    vector<string> vertices(verticesSet.begin(), verticesSet.end());
    unordered_map<string, int> idx;
    for (int i = 0; i < (int)vertices.size(); ++i)
        idx[vertices[i]] = i;

    int V = vertices.size();
    int E = arestas.size();
    // Criar matriz V x E inicializada com zeros
    vector<vector<int>> matriz(V, vector<int>(E, 0));

    // Preencher matriz de incidência
    for (int e = 0; e < E; ++e) {
        string origem = arestas[e].first;
        string destino = arestas[e].second;
        int i = idx[origem];
        int j = idx[destino];

        if (direcionado) {
            if (i == j)
                matriz[i][e] = 2; // Laço no mesmo vértice
            else {
                matriz[i][e] = -1; // Origem
                matriz[j][e] = 1;  // Destino
            }
        } else {
            if (i == j)
                matriz[i][e] = 2; // Laço em grafo não direcionado
            else {
                matriz[i][e] = 1;
                matriz[j][e] = 1;
            }
        }
    }
    cout << "\nMatriz de Incidência (" << V << " x " << E << "):\n\n";
    cout << setw(6) << " ";
    for (int e = 0; e < E; ++e)
        cout << setw(5) << "e" << e + 1;
    cout << "\n";

    for (int i = 0; i < V; ++i) {
        cout << setw(5) << vertices[i] << " ";
        for (int e = 0; e < E; ++e)
            cout << setw(5) << matriz[i][e];
        cout << "\n";
    }
    cout << "\nLegenda das Arestas:\n";
    for (int e = 0; e < E; ++e)
        cout << "e" << e + 1 << ": " << arestas[e].first << " -> " << arestas[e].second << "\n";

    cout << "\n(Obs: valor '2' indica um laço no vértice correspondente)\n";
}

int main() {
    bool direcionado;
    //escolhe se é grafo ou dígrafo, como pede na questão que seja dígrafo, vamos sempre escolher dígrafo
    cout << "O grafo é direcionado? (1 - Sim, 0 - Não): ";
    cin >> direcionado;
    cout << "Digite as arestas (formato: origem destino, use 0 0 para encerrar):\n";

    vector<pair<string, string>> arestas;
    string u, v;
    while (true) {
        cin >> u >> v;
        if (u == "0" && v == "0") break;
        arestas.push_back({u, v});
    }
    // Chama a função modularizada
    gerarMatrizIncidencia(arestas, direcionado);

    return 0;
}
