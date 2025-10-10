// questao 15 - Determinação de articulações e blocos (biconectividade), utilizando obrigatoriamente a função lowpt.
// Gabrielle

/*
Entrada: 
    - Número de vértices (int), para cada vértice: 
        - nome do vértice (string)
        - lista de vértices adjacentes a ele (strings, um por vez, até o comando 'fim')
    - nome do vértice inicial para a busca (string)
Saída:
    - Blocos biconexos encontrados (arestas e vértices de cada bloco)
    - Pontos de articulação do grafo
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <set>
#include <stack>
using namespace std;

int main(){
    map<string, vector<string>> adj; //Lista de adjacência 

    int v;
    cout << "Digite o número de vértices: ";
    cin >> v;

    set<string> all_vertices;
    for (int i=0; i<v; i++){
        string name = "";
        vector<string> list;

        cout << "Digite o nome do vértice " << (i+1) << ": ";
        cin >> name;
        all_vertices.insert(name);
        string v_0 = "";
        cout << "Digite a lista de vértices adjacentes: ('fim' para acabar)\n";
        set<string> vizinhos;
        while(true){
            v_0 = "";
            cin >> v_0;
            if (v_0 == "fim") break;
            if (v_0 == name) continue; // ignora laço
            if (vizinhos.count(v_0)) continue; // ignora repetidos
            list.push_back(v_0);
            vizinhos.insert(v_0);
            all_vertices.insert(v_0);
        }
        adj[name] = list; //Cada item da lista adj tem um nome(vértice) e uma lista(vizinhos)
    }

    string first;
    cout << "Digite o primeiro vértice da busca: ";
    cin >> first;

    stack<pair<string, string>> pilhaDeArestas;
    map<string, int> discovery; // tempo de descoberta
    map<string, int> lowpt;     // menor tempo alcançável
    map<string, string> parent; // pai na DFS
    set<string> articulacoes;   // pontos de articulação
    int tempo = 0;

    // Inicializa discovery, lowpt e parent para todos os vértices
    for (const auto& vert : all_vertices) {
        discovery[vert] = 0;
        lowpt[vert] = 0;
        parent[vert] = "";
        if (adj.find(vert) == adj.end()) adj[vert] = vector<string>();
    }

    // Função recursiva para DFS e cálculo de lowpt
    function<void(const string&)> dfs = [&](const string& u) {
        discovery[u] = lowpt[u] = ++tempo;
        int filhos = 0;
        for (const string& v : adj[u]) {
            if (discovery.find(v) == discovery.end()) continue; // ignora vértices não cadastrados
            if (!discovery[v]) {
                filhos++;
                parent[v] = u;
                pilhaDeArestas.push({u, v});
                dfs(v);
                lowpt[u] = min(lowpt[u], lowpt[v]);

                // Verifica ponto de articulação
                if ((parent[u] == "" && filhos > 1) ||
                    (parent[u] != "" && lowpt[v] >= discovery[u])) {
                    articulacoes.insert(u);
                    // Desempilha as arestas para formar o bloco biconexo
                    vector<pair<string, string>> bloco;
                    pair<string, string> aresta;
                    do {
                        aresta = pilhaDeArestas.top(); pilhaDeArestas.pop();
                        bloco.push_back(aresta);
                    } while (!(aresta.first == u && aresta.second == v) && !pilhaDeArestas.empty());
                    // Exibe o bloco
                    cout << "Bloco biconexo: ";
                    set<string> verticesBloco;
                    for (const auto& e : bloco) {
                        cout << "(" << e.first << "," << e.second << ") ";
                        verticesBloco.insert(e.first);
                        verticesBloco.insert(e.second);
                    }
                    cout << " | Vértices: ";
                    for (const auto& vert : verticesBloco) cout << vert << " ";
                    cout << endl;
                }
            } else if (v != parent[u] && discovery[v] < discovery[u]) {
                lowpt[u] = min(lowpt[u], discovery[v]);
                pilhaDeArestas.push({u, v});
            }
        }
    };

    dfs(first);

    // Olhar para outros blocos na pilha se o grafo for desconexo
    if (!pilhaDeArestas.empty()) {
        vector<pair<string, string>> bloco;
        while (!pilhaDeArestas.empty()) {
            bloco.push_back(pilhaDeArestas.top());
            pilhaDeArestas.pop();
        }
        cout << "Bloco biconexo final: ";
        set<string> verticesBloco;
        for (const auto& e : bloco) {
            cout << "(" << e.first << "," << e.second << ") ";
            verticesBloco.insert(e.first);
            verticesBloco.insert(e.second);
        }
        cout << " | Vértices: ";
        for (const auto& vert : verticesBloco) cout << vert << " ";
        cout << endl;
    }

    // Exibe pontos de articulação
    cout << "Pontos de articulação:\n";
    for (const auto& art : articulacoes) cout << art << endl;

}
