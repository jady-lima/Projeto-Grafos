//questão 20 - Busca em profundidade, com determinação de profundidade de entrada e de saída de
//cada vértice, e arestas de árvore, retorno, avanço e cruzamento.
//Gabrielle

/*
Entrada: 
    - Número de vértices do dígrafo (int).
    - Número de arestas do dígrafo (int).
    - Para cada aresta: o vértice de origem e o vértice de destino (dois inteirow), 
      separados por espaço. Os vértices devem ser informados como números 
      inteiros de 0 a (V-1), onde V é o número total de vértices

Saída:
    - classificação de cada aresta do dígrafo em uma das quatro categorias (Árvore, Retorno, Avanço ou Cruzamento)
    - Para cada vértice: o tempo de descoberta (entrada na busca) e o tempo de finalização (saída da busca)
*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// Enum para representar as cores dos vértices durante a busca
enum Cor { BRANCO, CINZA, PRETO };

class Grafo {
private:
    int V; // Número de vértices
    std::list<int> *adj; // Lista de adjacências

    // Vetores para armazenar informações da DFS
    std::vector<Cor> cor;
    std::vector<int> d; // Tempo de descoberta (entrada)
    std::vector<int> f; // Tempo de finalização (saída)
    std::vector<int> pai;
    
    // Contadores para descoberta e finalização
    int tempo_d; 
    int tempo_f;

    // Função auxiliar 
    void DFS_Visit(int u);

public:
    Grafo(int V);
    ~Grafo();
    void adicionarAresta(int v, int w);
    void DFS_Completo();
};

Grafo::Grafo(int V) {
    this->V = V;
    adj = new std::list<int>[V];
}

Grafo::~Grafo() {
    delete[] adj;
}

void Grafo::adicionarAresta(int v, int w) {
    adj[v].push_back(w); // Adiciona w à lista de vertices adjacentes a v
}

/**
 * função principal da DFS.
 * Prepara as estruturas de dads e inicia a busca.
 */
void Grafo::DFS_Completo() {
    cor.assign(V, BRANCO);
    d.assign(V, 0);
    f.assign(V, 0);
    pai.assign(V, -1);
    
    tempo_d = 0;
    tempo_f = 0;

    std::cout << "Iniciando Busca em Profundidade (DFS)" << std::endl;
    std::cout << "--- Classificacao das Arestas ---" << std::endl;

    for (int u = 0; u < V; ++u) {
        if (cor[u] == BRANCO) {
            DFS_Visit(u);
        }
    }
    
    std::cout << "\n--- Tempos de Descoberta e Finalizacao ---" << std::endl;
    for (int i = 0; i < V; ++i) {
        std::cout << "Vertice " << i << ": "
                  << "Descoberta = " << d[i]
                  << ", Finalizacao = " << f[i] << std::endl;
    }
}

/**
 * função recursiva da lógica principal da DFS.
 * u = vértice sendo visitado.
 */
void Grafo::DFS_Visit(int u) {
    cor[u] = CINZA; 
    
    // Incrementa o contador de descoberta e atribui o tempo
    tempo_d++;
    d[u] = tempo_d;

    for (int v : adj[u]) {
        if (cor[v] == BRANCO) {
            std::cout << "(" << u << " - " << v << ") - Aresta de Arvore" << std::endl;
            pai[v] = u;
            DFS_Visit(v);
        }
        else if (cor[v] == CINZA) {
            std::cout << "(" << u << " - " << v << ") - Aresta de Retorno (ciclo)" << std::endl;
        }
        else if (cor[v] == PRETO) {
            if (d[u] < d[v]) {
                std::cout << "(" << u << " - " << v << ") - Aresta de Avanço" << std::endl;
            } else {
                std::cout << "(" << u << " - " << v << ") - Aresta de Cruzamento" << std::endl;
            }
        }
    }

    cor[u] = PRETO;
    
    // Incrementa o contador de finalização e atribui o tempo
    tempo_f++;
    f[u] = tempo_f;
}

int main() {
    int numVertices, numArestas;
    
    std::cout << "Digite o numero total de vertices: ";
    std::cin >> numVertices;

    // Cria o digrafo com o tamanho dado pelo usuário
    Grafo g(numVertices);

    std::cout << "Digite o numero total de arestas: ";
    std::cin >> numArestas;

    std::cout << "Digite as arestas (formato origem -> destino)." << std::endl;
    std::cout << "** os vertices serao numerado de 0 a " << numVertices - 1 << "." << std::endl;

    // Ler cada aresta em um laço
    for (int i = 0; i < numArestas; ++i) {
        int origem, destino;
        std::cout << "Aresta " << i + 1 << ": ";
        std::cin >> origem >> destino;

        // garantir que os vértices da aresta estão no intervalo correto
        while (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
            std::cout << "Entrada invalida. Vertices devem estar entre 0 e " << numVertices - 1 << "." << std::endl;
            std::cout << "Digite a aresta " << i + 1 << " novamente: ";
            std::cin >> origem >> destino;
        }

        g.adicionarAresta(origem, destino);
    }

    std::cout << "\n Grafo criado com sucesso!" << std::endl;

    // 4. Executar a DFS no digrafo criado
    g.DFS_Completo();

    return 0;
}