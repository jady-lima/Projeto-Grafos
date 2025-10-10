// Arquivo: questao11.cpp
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

    void carregarArquivo(const string& arquivoNome) {
        totalVertices = 0;
        listaAdj.clear();
        posVertice.clear();
        nomeVertice.clear();

        ifstream arq(arquivoNome);
        if (!arq.is_open()) {
            cout << "Erro ao abrir o arquivo " << arquivoNome << endl;
            return;
        }

        string linha;
        getline(arq, linha); // ignora a primeira linha (quantidade de vértices)
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

    bool verificarConexo() {
        if (totalVertices == 0) return true;

        vector<bool> visitado(totalVertices, false);
        queue<int> fila;

        visitado[0] = true;
        fila.push(0);

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();

            for (int vizinho : listaAdj[atual]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    fila.push(vizinho);
                }
            }
        }

        for (int i = 0; i < totalVertices; i++) {
            if (!visitado[i]) return false;
        }
        return true;
    }
};

int main() {
    cout << "--- Questão 11: Verificar se um Grafo é Conexo ---" << endl;

    Grafo g;
    vector<string> arquivos = {"GRAFO_0.txt", "GRAFO_1.txt", "GRAFO_2.txt", "GRAFO_3.txt"};

    for (auto& nome : arquivos) {
        cout << "\n> Lendo arquivo: " << nome << endl;
        g.carregarArquivo(nome);
        if (g.verificarConexo()) {
            cout << "  Resultado: O grafo é conexo." << endl;
        } else {
            cout << "  Resultado: O grafo não é conexo." << endl;
        }
    }

    return 0;
}
