#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>
#include <list>
#include <map>

class Grafo {
private:
    int V;
    std::map<std::string, int> mapaVertices;
    std::vector<std::string> nomesVertices;
    int contadorVertices;
    std::vector<std::vector<int>> matrizAdj;
    std::vector<std::list<int>> listaAdj;
    std::vector<bool> verticeAtivo;
    int obterIndice(const std::string& nomeVertice);
public:
    Grafo();
    bool carregarArquivo(const std::string& nomeArquivo);
    void adicionarAresta(const std::string& u_str, const std::string& v_str);
    bool saoVerticesAdjacentesMatriz(const std::string& u_str, const std::string& v_str); // questão 6
    bool saoVerticesAdjacentesLista(const std::string& u_str, const std::string& v_str);  // questão 6
    void excluirVertice(const std::string& vertice_str); // questão 10
    bool ehBipartido(); // questão 12
    void imprimirGrafo();
};

#endif // GRAFO_H