#include "Digrafo.h"
#include <iostream>

int main() {
    Digrafo digafro;
    std::string nomeArquivo = "DIGRAFO1.txt"; 

    if (digafro.carregarArquivo(nomeArquivo)) {
        std::cout << "Questao 16: Representacao do Digrafo a partir da Matriz de Adjacencias." << std::endl;
        digafro.imprimirMatrizAdjacencia();
    }
    
    return 0;
}