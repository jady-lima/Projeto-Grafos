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

    // Função para excluir um vértice do grafo
    void excluirVertice(const std::string& vertice_a_excluir) {
        if (listaAdj.count(vertice_a_excluir) == 0) {
            std::cout << "Erro: Vertice '" << vertice_a_excluir << "' nao existe no grafo." << std::endl;
            return;
        }
        
        listaAdj.erase(vertice_a_excluir);

        for (auto& par : listaAdj) {
            auto& vizinhos = par.second;
            vizinhos.erase(std::remove(vizinhos.begin(), vizinhos.end(), vertice_a_excluir), vizinhos.end());
        }
        std::cout << "Vertice '" << vertice_a_excluir << "' foi excluido." << std::endl;
    }

    void imprimirGrafo() {
        std::cout << "GRAFO LISTA DE ADJACENCIA" << std::endl;
        for (const auto& par : listaAdj) {
            std::cout << par.first << " -> ";
            for (const std::string& vizinho : par.second) {
                std::cout << vizinho << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.txt>" << std::endl;
        return 1;
    }

    Grafo grafo;
    if (grafo.carregarArquivo(argv[1])) {
        std::cout << "Grafo antes da exclusao:" << std::endl;
        grafo.imprimirGrafo();
        
        std::string vertice_a_excluir;
        std::cout << "\nDigite o vertice a ser excluido: ";
        std::cin >> vertice_a_excluir;
        
        grafo.excluirVertice(vertice_a_excluir);

        std::cout << "\nGrafo apos a exclusao:" << std::endl;
        grafo.imprimirGrafo();
    }
    return 0;
}