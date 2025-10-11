/**
 * Busca em Profundidade com determinação de arestas de retorno a partir de um vertice inicial
 * 
 * @author Jady Lima
 */

 /**
  * Entrada: Arquivo nomeado "digrafo.txt", com as arestas do grafo (separado por virgula) e um vertice inicial da busca
  * Saída: Impressão das arestas visitadas e arestas de retorno, junto ao status final de cada vértice do grafo (visitado, visitando ou nao visitado)
  */


#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

// Pede ao usuário as arestas do grafo
void recebe_arestas(const string& nome_arquivo, map<string, vector<string>>& matriz) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao ler o file." << endl;
        return;
    }

    // Ignora a primeira linha (quantidade de arestas)
    string linha;
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        replace(linha.begin(), linha.end(), ',', ' ');

        stringstream ss(linha);
        string u, v;
        ss >> u >> v;

        matriz[u].push_back(v);
        if (matriz.find(v) == matriz.end()) {
            matriz[v] = {};
        }
    }

    arquivo.close();
}

// Busca em Profundidade, com determinação de arestas de retorno
void dfs(string verticeInicial, map<string, vector<string>>& matriz, map<string, int>& visitado) {
    stack<pair<string, int>> pilha; 
    pilha.push({verticeInicial, 0});
    visitado[verticeInicial] = 0; // 0 = visitando, -1 = não visitado, 1 = visitado

    while(!pilha.empty()){
        auto &topo = pilha.top(); // referência ao topo da pilha
        string verticeAtual = topo.first;
        int &indiceVizinho = topo.second;

        if(indiceVizinho < matriz[verticeAtual].size()){
            string v = matriz[verticeAtual][indiceVizinho];
            indiceVizinho++; 

            if(visitado[v] == -1){
                // Se não visitado, marca como visitando e vai para os vizinhos
                visitado[v] = 0;
                pilha.push({v,0});
            } else if(visitado[v] == 0){
                //Se visitando (ainda na pilha), marca como aresta de retorno
                cout<<"Aresta de retorno: "<<verticeAtual<<" -> "<<v<<endl;
            }
        } else {
            // Se não tem mais vizinhos, marca como visitado e remove da pilha.
            visitado[verticeAtual] = 1;
            cout<<"Vertice " << verticeAtual << " visitado."<<endl;
            pilha.pop();
        }
    }

}

int main() {
    map<string, vector<string>> matriz;

    // Ler o arquivo de entrada
    string nome_arquivo = "DIGRAFO2.txt";
    recebe_arestas(nome_arquivo, matriz);

    // Inicializa todo o map como não visitado
    map<string, int> visitado;
    for (auto &[v, _] : matriz) {
        visitado[v] = -1;
    }

    // Recebe o vertice inicial da busca
    string verticeInicial;
    cout << "\nDigite o vertice inicial da busca: ";
    cin >> verticeInicial;

    // Chama a DFS para verificar o grafo, identificando as arestas de retorno
    dfs(verticeInicial, matriz, visitado);

    //Imprime os status de todos os vertices depois da dfs
    cout << "\nStatus final:\n";
    for (auto &[v, estado] : visitado) {
        cout << v << " -> ";
        if (estado == -1) {
            cout << "não visitado";
        } else if (estado == 0) {
            cout << "visitando";
        } else {
            cout << "visitado";
        }
        cout << endl;
    }

    return 0;
}
