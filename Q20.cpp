//questão 20 - Busca em profundidade, com determinação de profundidade de entrada e de saída de
//cada vértice, e arestas de árvore, retorno, avanço e cruzamento.
//Gabrielle

/*
Entrada: 
    - Número de vértices do dígrafo (int).
    - Número de arestas do dígrafo (int).
    - Para cada aresta: o vértice de origem e o vértice de destino (dois inteiros), 
      separados por espaço. Os vértices devem ser informados como números 
      inteiros de 1 a V, onde V é o número total de vértices. 

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

    std::cout << "\nIniciando Busca em Profundidade (DFS)" << std::endl;
    std::cout << "--- Classificacao das Arestas ---" << std::endl;

    for (int u = 0; u < V; ++u) {
        if (cor[u] == BRANCO) {
            DFS_Visit(u);
        }
    }
    
    std::cout << "\n--- Tempos de Descoberta e Finalizacao ---" << std::endl;
    for (int i = 0; i < V; ++i) {
        std::cout << "Vertice " << i + 1 << ": " 
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
    
    tempo_d++;
    d[u] = tempo_d;

    for (int v : adj[u]) {
        if (cor[v] == BRANCO) {
            // Mostra os vértices como 'u + 1' e 'v + 1'
            std::cout << "(" << u + 1 << " -> " << v + 1 << ") - Aresta de Arvore" << std::endl;
            pai[v] = u;
            DFS_Visit(v);
        }
        else if (cor[v] == CINZA) {
            std::cout << "(" << u + 1 << " -> " << v + 1 << ") - Aresta de Retorno (ciclo)" << std::endl; 
        }
        else if (cor[v] == PRETO) {
            if (d[u] < d[v]) {
                std::cout << "(" << u + 1 << " -> " << v + 1 << ") - Aresta de Avanco" << std::endl; 
            } else {
                std::cout << "(" << u + 1 << " -> " << v + 1 << ") - Aresta de Cruzamento" << std::endl; 
            }
        }
    }

    cor[u] = PRETO;
    
    tempo_f++;
    f[u] = tempo_f;
}

int main() {
    int numVertices, numArestas;
    
    std::cout << "Digite o numero total de vertices: ";
    std::cin >> numVertices;
    
    if (numVertices <= 0) {
        std::cout << "Numero de vertices deve ser positivo." << std::endl;
        return 1;
    }

    // Cria o digrafo com o tamanho dado pelo usuário
    Grafo g(numVertices);

    std::cout << "Digite o numero total de arestas: ";
    std::cin >> numArestas;

    std::cout << "Digite as arestas (formato origem -> destino)." << std::endl;
    // Informa ao usuário para usar a numeração de 1 a N
    std::cout << "** Os vertices devem ser nomeados de 1 a " << numVertices << ".**" << std::endl; 

    // Ler cada aresta em um laço
    for (int i = 0; i < numArestas; ++i) {
        int origem, destino;
        std::cout << "Aresta " << i + 1 << ": ";
        std::cin >> origem >> destino;

        // Validação para garantir que os vértices estão no intervalo de 1 a N
        while (origem < 1 || origem > numVertices || destino < 1 || destino > numVertices) { 
            std::cout << "Entrada invalida. Vertices devem estar entre 1 e " << numVertices << "." << std::endl; 
            std::cout << "Digite a aresta " << i + 1 << " novamente: ";
            std::cin >> origem >> destino;
        }

        // Converte a entrada do usuário (1 a N) para o índice interno (0 a N-1)
        g.adicionarAresta(origem - 1, destino - 1); 
    }

    std::cout << "\nGrafo criado com sucesso!" << std::endl;

    // Executar a DFS no digrafo criado
    g.DFS_Completo();

    return 0;
}