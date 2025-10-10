#include <iostream>
#include "Grafo.h"

int main() {
    Grafo grafo;
    std::string nomeArquivo = "GRAFO_3.txt";

    if (grafo.carregarArquivo(nomeArquivo)) {
        std::cout << "Questao 12: Determinar se um grafo e bipartido" << std::endl;
        std::cout << "Arquivo: " << nomeArquivo << std::endl;
        grafo.imprimirGrafo();
        
        if (grafo.ehBipartido()) {
            std::cout << "Resultado: O grafo E bipartido." << std::endl;
        } else {
            std::cout << "Resultado: O grafo NAO E bipartido." << std::endl;
        }
    }
    
    return 0;
}