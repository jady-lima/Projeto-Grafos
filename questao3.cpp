// Arquivo: questao3.cpp
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class Grafo {
private:
    int qntVertices;
    vector<list<int>> listaAdj;
    map<string, int> rotuloParaIndice;
    vector<string> indiceParaRotulo;

    void addVertice(const string& rotulo) {
        if (rotuloParaIndice.find(rotulo) == rotuloParaIndice.end()) {
            rotuloParaIndice[rotulo] = qntVertices++;
            indiceParaRotulo.push_back(rotulo);
            listaAdj.resize(qntVertices);
        }
    }

public:
    Grafo() : qntVertices(0) {}

    void addAresta(const string& u_rotulo, const string& v_rotulo) {
        addVertice(u_rotulo);
        addVertice(v_rotulo);
        int u = rotuloParaIndice[u_rotulo];
        int v = rotuloParaIndice[v_rotulo];
        listaAdj[u].push_back(v);
        listaAdj[v].push_back(u);
    }

    void criarGrafoMatrizIncidencia(const vector<vector<int>>& matriz, const vector<string>& rotulos) {
        if (matriz.empty() || rotulos.empty() || matriz.size() != rotulos.size()) return;
        
        for (const auto& r : rotulos) addVertice(r);

        int totalVertices = matriz.size();
        int totalArestas = matriz[0].size();

        for (int j = 0; j < totalArestas; ++j) {
            vector<int> verticesAresta;
            for (int i = 0; i < totalVertices; ++i) {
                if (matriz[i][j] == 1) verticesAresta.push_back(i);
            }
            if (verticesAresta.size() == 2) {
                addAresta(indiceParaRotulo[verticesAresta[0]], indiceParaRotulo[verticesAresta[1]]);
            }
        }
    }

    void mostrarGrafo() {
        cout << "grafo criado - lista de adjacência):" << endl;
        for (int i = 0; i < qntVertices; ++i) {
            cout << "  " << indiceParaRotulo[i] << " -> ";
            for (int v : listaAdj[i]) {
                cout << indiceParaRotulo[v] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "--- Questão 3: grafo a partir da matriz de incidência ---" << endl;
    
    Grafo meuGrafo;
    vector<string> rotulos = {"A", "B", "C", "D"};
    vector<vector<int>> matInc = {
        {1, 1, 0, 0, 0}, {1, 0, 1, 1, 0}, {0, 1, 1, 0, 1}, {0, 0, 0, 1, 1}
    };

    meuGrafo.criarGrafoMatrizIncidencia(matInc, rotulos);
    meuGrafo.mostrarGrafo();

    return 0;
}
