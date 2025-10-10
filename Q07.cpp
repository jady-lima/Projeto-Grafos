/**
 * Função que determina o número total de vértices
 * 
 * @author Jady Lima
 */

 /**
  * Entrada: Arquivo nomeado "arestas.txt", com a quantidade de arestas e os valores dos vertices n, m separados por virgula
  * Saída: Impressão de todos os vertices e quantidade total de vértices no grafo
  */

#include <iostream>
#include <set>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

set<string> vertices;

void recebe_arestas(const string& nome_arquivo) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo." << endl;
        return;
    }

    // Ignora a primeira linha (quantidade de arestas)
    string linha;
    getline(arquivo, linha);

    // Ler as arestas (demais linhas do arquivo)
    while (getline(arquivo, linha)) {
        replace(linha.begin(), linha.end(), ',', ' ');

        stringstream ss(linha);
        string n, m;
        ss >> n >> m;

        vertices.insert(n);
        vertices.insert(m);
    }

    arquivo.close();
}

// Função para imprimir todos os vértices do grafo
void imprime_vertices() {
    for (string v : vertices) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    // Leitura das arestas do arquivo
    string nome_arquivo = "arestas.txt";
    recebe_arestas(nome_arquivo);

    // Imprime os vértices
    imprime_vertices();

    // Determina o número de vértices
    int numero_vertices = vertices.size();
    cout << "Numero de vertices: " << numero_vertices << endl;

    return 0;
}
