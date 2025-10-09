//Criação do Grafo a partir da Lista de Adjacências
//Gabrielle

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(){
    map<string, vector<string>> adj; //Lista de adjacência 
    set<tuple<string, string>> arestas; //Set de arestas do grafo (não permite repetições)

    int v;
    cout << "Digite o número de vértices: ";
    cin >> v;

    //Loop para guardar vértices e seus adjacentes
    for (int i=0; i<v; i++){
        string name = "";
        vector<string> list;

        cout << "Digite o nome do vértice " << (i+1) << ": ";
        cin >> name;
        
        string v_0 = "";
        cout << "Digite a lista de vértices adjacentes: ('fim' para acabar)\n";
        while(true){
            v_0 = "";
            cin >> v_0;
            if (v_0 == "fim") break;
            list.push_back(v_0);
        }
        adj[name] = list; //Cada item da lista adj tem um nome(vértice) e uma lista(vizinhos)
    }

    //Função para garantir que a ordem não importe nas arestas (grafo não direcionado)
    auto add_edge = [&](string u, string v) {
        if (u > v) swap(u, v);
        arestas.insert({u, v});
    };

    //Loop para adicionar as arestas no set
    for (auto &[vertice, vizinhos] : adj) {
        for (int j=0; j<vizinhos.size(); j++){
            add_edge(vertice, vizinhos[j]);
        }
    }

    //Impressão do grafo final
    cout << "\nGrafo a partir da Lista de Adjacência: \n";
    for (auto [u, v] : arestas){
        cout << u << " - " << v << "\n";
    }
    cout << "\n";

    return 0;
}