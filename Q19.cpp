// Arquivo: questao19.cpp
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

class Digrafo {
private:
    int totalVertices;
    vector<list<int>> listaAdj;
    map<string, int> posicaoVertice;
    vector<string> nomeVertice;

    void adicionarVertice(const string& nome) {
        if (posicaoVertice.find(nome) == posicaoVertice.end()) {
            posicaoVertice[nome] = totalVertices++;
            nomeVertice.push_back(nome);
            listaAdj.resize(totalVertices);
        }
    }

public:
    Digrafo() {
        totalVertices = 0;
    }

    // add um arco 
    void adicionarLigacao(const string& origem, const string& destino) {
        adicionarVertice(origem);
        adicionarVertice(destino);
        int u = posicaoVertice[origem];
        int v = posicaoVertice[destino];
        listaAdj[u].push_back(v);
    }

  
    void carregarArquivo(const string& nomeArquivo) {
        totalVertices = 0;
        listaAdj.clear();
        posicaoVertice.clear();
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
                adicionarLigacao(a, b);
            }
        }
        arq.close();
    }

    
    void buscaLargura(const string& inicio) {
        if (posicaoVertice.find(inicio) == posicaoVertice.end()) {
            cout << "  Vértice inicial '" << inicio << "' não encontrado." << endl;
            return;
        }

        int s = posicaoVertice[inicio];
        vector<bool> visitado(totalVertices, false);
        queue<int> fila;

        visitado[s] = true;
        fila.push(s);

        cout << "  Ordem de visitação (BFS) a partir de '" << inicio << "': ";
        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();
            cout << nomeVertice[atual] << " ";

            for (int vizinho : listaAdj[atual]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    fila.push(vizinho);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    cout << "--- Questão 19: Busca em Largura (BFS) para Digrafos ---" << endl;

    Digrafo d;
    vector<pair<string, string>> testes = {
        {"DIGRAFO_0.txt", "a"},
        {"DIGRAFO1.txt", "1"},
        {"DIGRAFO2.txt", "1"},
        {"DIGRAFO3.txt", "a"}
    };

    for (auto& t : testes) {
        cout << "\n> Lendo arquivo: " << t.first << endl;
        d.carregarArquivo(t.first);
        d.buscaLargura(t.second);
    }

    return 0;
}
