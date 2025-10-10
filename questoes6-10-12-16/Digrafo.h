#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <string>
#include <vector>
#include <map>
#include <list>

class Digrafo {
private:
    int V;
    std::map<std::string, int> mapaVertices;
    std::vector<std::string> nomesVertices;
    int contadorVertices;

    std::vector<std::vector<int>> matrizAdj;

    int obterIndice(const std::string& nomeVertice);

public:
    Digrafo();
    bool carregarArquivo(const std::string& nomeArquivo);
    void adicionarArco(const std::string& u_str, const std::string& v_str);
    void imprimirMatrizAdjacencia();
};

#endif