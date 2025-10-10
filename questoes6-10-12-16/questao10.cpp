#include <iostream>
#include "Grafo.h"

int main() {
    Grafo grafo;
    std::string nomeArquivo = "GRAFO_2.txt";

    if (grafo.carregarArquivo(nomeArquivo)) {
        std::cout << "Questao 10: Exclusao de um vertice existente usando Lista de Adjacencias e Matriz de Adjacencias." << std::endl;
        std::cout << "Arquivo: " << nomeArquivo << std::endl;
        grafo.imprimirGrafo();

        std::cout << "Antes da exclusao, '8' e '11' sao adjacentes? "
                  << (grafo.saoVerticesAdjacentesLista("8", "11") ? "Sim" : "Nao") << std::endl;

        grafo.excluirVertice("8");

        std::cout << "Depois da exclusao de '8', '8' e '11' sao adjacentes? "
                  << (grafo.saoVerticesAdjacentesLista("8","11") ? "Sim" : "Nao") << std::endl;
        
          grafo.imprimirGrafo();        
    }
    return 0;
}