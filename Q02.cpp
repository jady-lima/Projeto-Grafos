/**
 * Criação do Grafo a partir da matriz de adjacência
 * 
 * @author Jady Lima
 */

 /**
  * Entrada: Arquivo nomeado "matriz.txt" com a matriz de adjacência (sem indices)
  * Saída: Todas as arestas do grafo
  */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<int>> recebe_arestas(const string& nome_arquivo) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abri o file" << endl;
        return {};
    }

    string linha;
    // Pega a quantidade de vertices
    getline(arquivo, linha);
    int vertices = stoi(linha);

    vector<vector<int>> matriz(vertices, vector<int>(vertices, 0));

    // Recebe a matriz do arquvo
    for (int i = 0; i < vertices; i++) {
        getline(arquivo, linha);
        stringstream ss(linha);
        for (int j = 0; j < vertices; j++) {
            ss >> matriz[i][j];
        }
    }

    arquivo.close();
    return matriz;
}

int main() {
    string nome_arquivo = "matriz.txt";
    vector<vector<int>> matriz = recebe_arestas(nome_arquivo);

    int vertices = matriz.size();

    cout << "Grafo: " << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matriz[i][j] == 1) {
                cout <<  i+1 << "-" << j+1 << " " << endl;
            }
        }
    }

    return 0;
}
