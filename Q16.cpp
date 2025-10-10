// Questão 16 - Representação do Digrafo a partir da Matriz de Adjacências
// Sebastião

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>

class Digrafo {
public:
    std::map<std::string, std::vector<std::string>> listaAdj;
    std::vector<std::string> vertices;
    std::map<std::string, bool> verticeExiste;

    // Carrega o digrafo a partir de um arquivo
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
                 if (!verticeExiste[u_str]) {
                     vertices.push_back(u_str);
                     verticeExiste[u_str] = true;
                 }
                 if (!verticeExiste[v_str]) {
                     vertices.push_back(v_str);
                     verticeExiste[v_str] = true;
                 }
            }
        }
        arquivo.close();
        return true;
    }

    // Função para imprimir a matriz de adjacência do digrafo
    void imprimirMatrizAdjacencia() {
        int numV = vertices.size();
        std::map<std::string, int> nomeParaId;
        for(int i = 0; i < numV; ++i) {
            nomeParaId[vertices[i]] = i;
        }

        std::vector<std::vector<int>> matriz(numV, std::vector<int>(numV, 0));

        for (const auto& par : listaAdj) {
            std::string u_nome = par.first;
            int u_id = nomeParaId[u_nome];
            for (const std::string& v_nome : par.second) {
                int v_id = nomeParaId[v_nome];
                matriz[u_id][v_id] = 1;
            }
        }

        std::cout << "DIGRAFO MATRIZ DE ADJACENCIA" << std::endl;
        std::cout << "   ";
        for (const auto& nome : vertices) {
            std::cout << std::setw(3) << nome;
        }
        std::cout << std::endl;

        for (int i = 0; i < numV; ++i) {
            std::cout << std::setw(3) << vertices[i];
            for (int j = 0; j < numV; ++j) {
                std::cout << std::setw(3) << matriz[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_digrafo.txt>" << std::endl;
        return 1;
    }

    Digrafo digrafo;
    if (digrafo.carregarArquivo(argv[1])) {
        digrafo.imprimirMatrizAdjacencia();
    }
    
    return 0;
}