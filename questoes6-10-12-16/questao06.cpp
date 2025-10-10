#include <iostream>
#include "Grafo.h"

int main() {
    Grafo grafo;
    std::string nomeArquivo = "GRAFO_2.txt";

    if (grafo.carregarArquivo(nomeArquivo)) {
        std::cout << "Questao 06: Funcao que determina se dois vertices sao adjacentes." << std::endl;
        std::cout << "Arquivo: " << nomeArquivo << std::endl;
        grafo.imprimirGrafo();
        
        std::cout << "'1' e '3' sao adjacentes? " 
                  << (grafo.saoVerticesAdjacentesMatriz("1", "3") ? "Sim" : "Nao") << std::endl;
    }
    return 0;
}