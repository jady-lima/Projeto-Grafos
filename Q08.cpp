//Função que determina o número total de arestas.
//Gabrielle

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm> 
using namespace std;

int main(){
    set<string> vertices; //Vetor de vértices
    set<tuple<string, string>> arestas; //Set de arestas do grafo (não permite repetições)

    //Salvar os vértices no vetor
    cout << " DIGITE OS VÉRTICES: (fim para acabar) \n";
    string v_temp;
    while(true){
        v_temp = "";
        cin >> v_temp;
        if (v_temp == "fim") break;
        vertices.insert(v_temp);
    }
    cout << " Vértices inseridos\n";

    string n, m;
    cout << " DIGITE AS ARESTAS: \n ('fim' para acabar)\n";
    //Receber as arestas
    while(true){
        n = ""; m = "";
        cin >> n;
        if (n == "fim") break; 
        cin >> m;
        if (m == "fim") break;

        //Verificar que os vértices existem
        bool n_existe = vertices.count(n);
        bool m_existe = vertices.count(m);

        if (n_existe && m_existe) {
            if (n > m) swap(n, m); //Garante que a ordem não importe nas arestas (grafo não direcionado)
            arestas.insert({n, m});
            cout << "Aresta adicionada!\n\n";
        } else {
            std::cout << "O vértice não foi encontrado na lista.\n" << std::endl;
        }    
    }

    //Impressão do total de arestas
    cout << "\n Quantidade total de arestas no grafo: " << arestas.size() << "\n";

    return 0;
}