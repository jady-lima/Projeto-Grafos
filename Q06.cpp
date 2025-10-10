#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

class Grafo {
public:
    std::map<std::string, std::vector<std::string>> listaAdj;

    // Carrega o grafo a partir de um arquivo
    bool carregarArquivo(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            std::cerr << "ERRO: Nao foi possivel abrir o arquivo " << nomeArquivo << std::endl;
            return false;
        }
        int numVertices;
        arquivo >> numVertices;
        std::string linha;
        std::getline(arquivo, linha); 

        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string u_str, v_str;
            if (std::getline(ss, u_str, ',') && std::getline(ss, v_str)) {
                 listaAdj[u_str].push_back(v_str);
                 listaAdj[v_str].push_back(u_str);
            }
        }
        arquivo.close();
        return true;
    }

    // Função para verificar se dois vértices são adjacentes
    bool saoAdjacentes(const std::string& u, const std::string& v) {
        if (listaAdj.count(u) == 0) return false;
        
        for (const std::string& vizinho : listaAdj.at(u)) {
            if (vizinho == v) return true;
        }
        return false;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.txt>" << std::endl;
        return 1;
    }

    Grafo grafo;
    if (grafo.carregarArquivo(argv[1])) {
        std::string vertice1, vertice2;
        
        std::cout << "Digite o primeiro vertice: ";
        std::cin >> vertice1;
        std::cout << "Digite o segundo vertice: ";
        std::cin >> vertice2;
        
        if (grafo.saoAdjacentes(vertice1, vertice2)) {
            std::cout << "Os vertices sao adjacentes" << std::endl;
        } else {
            std::cout << "Os vertices nao sao adjacentes." << std::endl;
        }
    }
    return 0;
}