// Questão 12 - Determinar se um grafo é bipartido
// Sebastião

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <queue>

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

    // Função para verificar se o grafo é bipartido
    bool ehBipartido() {
        // Mapa para guardar as cores dos vértices: -1 (sem cor), 0 (cor A), 1 (cor B)
        std::map<std::string, int> cores;

        for (const auto& par : listaAdj) {
            const std::string& vertice_inicial = par.first;
            
            // Se o vértice ainda não foi colorido, inicia uma busca BFS a partir dele
            if (cores.find(vertice_inicial) == cores.end()) {
                std::queue<std::string> fila;
                
                cores[vertice_inicial] = 0;
                fila.push(vertice_inicial);

                while (!fila.empty()) {
                    std::string u = fila.front();
                    fila.pop();

                    for (const std::string& v : listaAdj.at(u)) {
                        if (cores.find(v) == cores.end()) {
                            cores[v] = 1 - cores[u]; // se nao tem cor, pinta com a cor oposta
                            fila.push(v);
                        } else if (cores.at(v) == cores.at(u)) {
                            return false; // se o vizinho tem a mesma cor, nao e bipartido
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.txt>" << std::endl;
        return 1;
    }

    Grafo grafo;
    if (grafo.carregarArquivo(argv[1])) {
        if (grafo.ehBipartido()) {
            std::cout << "Resultado: O grafo e bipartido." << std::endl;
        } else {
            std::cout << "Resultado: O grafo nao e bipartido." << std::endl;
        }
    }
    return 0;
}