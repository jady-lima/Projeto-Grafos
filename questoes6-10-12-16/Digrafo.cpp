#include "Digrafo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Digrafo::Digrafo() : V(0), contadorVertices(0) {}

int Digrafo::obterIndice(const std::string& nomeVertice) {
    if (mapaVertices.find(nomeVertice) == mapaVertices.end()) {
        mapaVertices[nomeVertice] = contadorVertices;
        nomesVertices.push_back(nomeVertice);
        contadorVertices++;
    }
    return mapaVertices[nomeVertice];
}

bool Digrafo::carregarArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo " << nomeArquivo << std::endl;
        return false;
    }
    arquivo >> this->V;
    if (V <= 0) return false;

    matrizAdj.assign(V, std::vector<int>(V, 0));
    nomesVertices.reserve(V);
    
    std::string linha;
    std::getline(arquivo, linha); 

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string u_str, v_str;
        if (std::getline(ss, u_str, ',') && std::getline(ss, v_str)) {
             adicionarArco(u_str, v_str);
        }
    }
    arquivo.close();
    return true;
}

// função para adicionar um arco (direcionado) entre dois vértices
void Digrafo::adicionarArco(const std::string& u_str, const std::string& v_str) {
    int u_id = obterIndice(u_str);
    int v_id = obterIndice(v_str);

    matrizAdj[u_id][v_id] = 1;
}

// Função para imprimir a Matriz de Adjacência e visualizar a representação
void Digrafo::imprimirMatrizAdjacencia() {
    std::cout << "--- Representacao do Digrafo (Matriz de Adjacencia) ---" << std::endl;
    std::cout << "   ";
    for (int i = 0; i < V; ++i) {
        std::cout << std::setw(3) << nomesVertices[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < V; ++i) {
        std::cout << std::setw(3) << nomesVertices[i];
        for (int j = 0; j < V; ++j) {
            std::cout << std::setw(3) << matrizAdj[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}