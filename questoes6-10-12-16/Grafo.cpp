#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

// Construtor da classe Grafo. É executado quando um objeto Grafo é criado
Grafo::Grafo() : V(0), contadorVertices(0) {}

int Grafo::obterIndice(const std::string& nomeVertice) {
    if (mapaVertices.find(nomeVertice) == mapaVertices.end()) {
        mapaVertices[nomeVertice] = contadorVertices;
        nomesVertices.push_back(nomeVertice);
        contadorVertices++;
    }
    // mapaVertices: { "c": 0, "a": 1, "b": 2 } - buscar o indice pelo nome
    // nomesVertices: [ "c", "a", "b" ] - buscar o nome pelo indice
    // contadorVertices: 3 - índice do próximo vertice a ser adicionado
    return mapaVertices[nomeVertice];
}

// Função para ler um grafo de um arquivo de texto e popular as estruturas de dados
bool Grafo::carregarArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo " << nomeArquivo << std::endl;
        return false;
    }
    arquivo >> this->V;
    if (V <= 0) return false;

    
    matrizAdj.assign(V, std::vector<int>(V, 0));
    listaAdj.assign(V, std::list<int>());
    nomesVertices.reserve(V);
    verticeAtivo.assign(V, true);

    std::string linha;
    std::getline(arquivo, linha); 

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string u_str, v_str;
        if (std::getline(ss, u_str, ',') && std::getline(ss, v_str)) {
             adicionarAresta(u_str, v_str);
        }
    }
    arquivo.close();
    return true;
}

// Função para adicionar uma aresta (não direcionada) entre dois vértices
void Grafo::adicionarAresta(const std::string& u_str, const std::string& v_str) {
    int u_id = obterIndice(u_str);
    int v_id = obterIndice(v_str);

    matrizAdj[u_id][v_id] = 1;
    matrizAdj[v_id][u_id] = 1;

    listaAdj[u_id].push_back(v_id);
    listaAdj[v_id].push_back(u_id);
}

// QUESTÃO 6
bool Grafo::saoVerticesAdjacentesMatriz(const std::string& u_str, const std::string& v_str) {
    if (mapaVertices.count(u_str) == 0 || mapaVertices.count(v_str) == 0) return false;
    int u_id = mapaVertices.at(u_str);
    int v_id = mapaVertices.at(v_str);
    return verticeAtivo[u_id] && verticeAtivo[v_id] && matrizAdj[u_id][v_id] == 1;
}

// QUESTÃO 6
bool Grafo::saoVerticesAdjacentesLista(const std::string& u_str, const std::string& v_str) {
    if (mapaVertices.count(u_str) == 0 || mapaVertices.count(v_str) == 0) return false;
    int u_id = mapaVertices.at(u_str);
    int v_id = mapaVertices.at(v_str);
    if (!verticeAtivo[u_id] || !verticeAtivo[v_id]) return false;

    for (int vizinho_id : listaAdj[u_id]) {
        if (vizinho_id == v_id) return true;
    }
    return false;
}

// QUESTÃO 10
void Grafo::excluirVertice(const std::string& vertice_str) {
    if (mapaVertices.count(vertice_str) == 0) {
        std::cout << "Vertice '" << vertice_str << "' nao existe." << std::endl;
        return;
    }
    int v_id = mapaVertices[vertice_str];

    if (!verticeAtivo[v_id]) {
        std::cout << "Vertice '" << vertice_str << "' ja foi excluido." << std::endl;
        return;
    }
    verticeAtivo[v_id] = false;

    for (int i = 0; i < V; ++i) {
        matrizAdj[v_id][i] = 0;
        matrizAdj[i][v_id] = 0;
    }

    std::list<int> vizinhos = listaAdj[v_id];
    listaAdj[v_id].clear();

    for (int vizinho_id : vizinhos) {
        if (verticeAtivo[vizinho_id]) {
            listaAdj[vizinho_id].remove(v_id);
        }
    }
    std::cout << "Vertice '" << vertice_str << "' foi logicamente excluido." << std::endl;
}

// QUESTÃO 12
bool Grafo::ehBipartido() {
    std::vector<int> cores(V, -1);

    for (int i = 0; i < V; ++i) {
        if (verticeAtivo[i] && cores[i] == -1) {
            std::queue<int> fila;
            
            cores[i] = 0;
            fila.push(i);

            // BFS
            while (!fila.empty()) {
                int u = fila.front();
                fila.pop();

                for (int v : listaAdj[u]) {
                    if (verticeAtivo[v]) {
                        if (cores[v] == -1) {
                            cores[v] = 1 - cores[u];
                            fila.push(v);
                        } else if (cores[v] == cores[u]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Grafo::imprimirGrafo() {
    std::cout << "Representacao do Grafo (Matriz de Adjacencia)" << std::endl;
    std::cout << "  ";
    for (int i = 0; i < V; ++i) {
        std::cout << nomesVertices[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < V; ++i) {
        std::cout << nomesVertices[i] << " ";
        for (int j = 0; j < V; ++j) {
            std::cout << matrizAdj[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Representacao do Grafo (Lista de Adjacencia)" << std::endl;
    for (int i = 0; i < V; ++i) {
        if (verticeAtivo[i]) {
            std::cout << nomesVertices[i] << " -> ";
            for (int vizinho_id : listaAdj[i]) {
                 std::cout << nomesVertices[vizinho_id] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "--------------------" << std::endl;
}