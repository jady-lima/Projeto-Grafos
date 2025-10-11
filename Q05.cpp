// Arquivo: questao5.cpp
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Grafo {
private:
    int totalVertices;
    vector<list<int>> listaAdj;
    map<string, int> posVertice;
    vector<string> nomeVertice;

    void adicionarVertice(const string& nome) {
        if (posVertice.find(nome) == posVertice.end()) {
            posVertice[nome] = totalVertices++;
            nomeVertice.push_back(nome);
            listaAdj.resize(totalVertices);
        }
    }

public:
    Grafo() {
        totalVertices = 0;
    }

    void adicionarAresta(const string& origem, const string& destino) {
        adicionarVertice(origem);
        adicionarVertice(destino);
        int u = posVertice[origem];
        int v = posVertice[destino];
        listaAdj[u].push_back(v);
        listaAdj[v].push_back(u);
    }

    void carregarArquivo(const string& nomeArquivo) {
        totalVertices = 0;
        listaAdj.clear();
        posVertice.clear();
        nomeVertice.clear();

        ifstream arq(nomeArquivo);
        if (!arq.is_open()) {
            cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
            return;
        }

        string linha;
        getline(arq, linha); 
        while (getline(arq, linha)) {
            stringstream ss(linha);
            string a, b;
            getline(ss, a, ',');
            getline(ss, b);
            if (!a.empty() && !b.empty()) {
                adicionarAresta(a, b);
            }
        }
        arq.close();
    }

    void mostrarGraus() {
        cout << "  Grau de cada vértice:" << endl;
        for (int i = 0; i < totalVertices; i++) {
            cout << "    " << nomeVertice[i] << " -> " << listaAdj[i].size() << endl;
        }
    }
};

int main() {
    cout << "--- Questão 5: Grau dos Vértices ---" << endl;

    Grafo g;
    vector<string> arquivos = {"GRAFO_0.txt", "GRAFO_1.txt", "GRAFO_2.txt", "GRAFO_3.txt"};

    for (auto& nome : arquivos) {
        cout << "\n> Lendo arquivo: " << nome << endl;
        g.carregarArquivo(nome);
        g.mostrarGraus();
    }

    return 0;
}
