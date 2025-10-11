/**
 * Determinação de Grafo Subjacente
 * 
 * @author Jady Lima
 */

 /**
  * Entrada: Arquivo nomeado "digrafo.txt", com as arestas do grafo (separado por virgula)
  * Saída: Impressão do grafo subjacente, ou seja, não direcionado
  */

/**
 * Grafo subjacente: Grafo não-direcionado obtido dado um grafo direcionado
 */

#include <iostream>
#include <set>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

set<string> vertices;
set<pair<string, string>> arestas_subjacentes;

// Ler as arestas do file (digrafo.txt)
void recebe_arestas(const string& nome_arquivo) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo) {
        cout << "Erro ao ler arquivo" << endl;
        return;
    }

    // Ignora o número, primeira linha do arquivo
    string linha;
    getline(arquivo, linha);

    // Leitura das arestas
    string n, m;
    while (getline(arquivo, linha)) {
        // pega linha e remoove vígula por espaço
        replace(linha.begin(), linha.end(), ',', ' ');
        stringstream ss(linha);
        ss >> n >> m;

        vertices.insert(n);
        vertices.insert(m);

        // Insere aresta subjacente, sempre do menor para o maior
        arestas_subjacentes.insert({min(n, m), max(n, m)});
    }

    arquivo.close();
}

// Imprime os vértices digitados/em arquivo
void imprime_vertices() {
    cout << "Vertices digitados: ";
    for (string v : vertices) {
        cout << v << " ";
    }
    cout << endl;
}

// Imprime o grafo como arestas subjacentes
void imprime_arestas() {
    cout << "Grafo subjacente:" << endl;
    for (auto e : arestas_subjacentes) {
        cout << e.first << " - " << e.second << endl;
    }
}

int main() {
    // Leitura das arestas do grafo
    recebe_arestas("DIGRAFO3.txt");

    // Imprime os vértices
    imprime_vertices();

    // Imprime as arestas subjacentes
    imprime_arestas();

    return 0;
}
