#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

// Função que executa a Busca em Largura (BFS)
void buscaPorLargura(const unordered_map<string, vector<string>>& grafo, const string& inicio) {
    unordered_map<string, bool> visitado; // Marca os vértices já visitados
    queue<string> fila;

    cout << "\nOrdem de visita a partir do vértice " << inicio << ":\n";

    visitado[inicio] = true; //marca o vértice inicial como visitado
    fila.push(inicio);

    while (!fila.empty()) {
        string atual = fila.front();
        fila.pop();
        cout << atual << " ";

        // Verifica se o vértice existe no grafo
        if (grafo.count(atual)) {
            // Percorre todos os vizinhos do vértice atual
            for (const string& vizinho : grafo.at(atual)) {
                // Se ainda não foi visitado, marca e adiciona à fila
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    fila.push(vizinho);
                }
            }
        }
    }
}

int main() {
    string u, v;
    unordered_map<string, vector<string>> grafo; // Estrutura de armazenamento do grafo

    cout << "Digite as arestas (formato: origem destino, ex: A B ou 1 2). Use 0 0 para encerrar:\n";
    
    while (true) {
        cin >> u >> v;
        if (u == "0" && v == "0") break; // condição de parada
        grafo[u].push_back(v);
        grafo[v].push_back(u); // grafo não direcionado — para digrafo, basta remover esta linha
    }

    string inicio;
    cout << "\nDigite o vértice inicial para a busca: ";
    cin >> ws; // limpa possíveis espaços ou enter pendentes
    cin >> inicio;

    buscaPorLargura(grafo, inicio); // executa a BFS

    return 0;
}

