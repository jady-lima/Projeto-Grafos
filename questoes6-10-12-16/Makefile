# Para Compilar:
    # make all: Compila todas as questões de uma só vez
    # make saida06: Compila apenas o programa da Questão 06
    # make saida10: Compila apenas o programa da Questão 10
    # make saida12: Compila apenas o programa da Questão 12
    # make saida16: Compila apenas o programa da Questão 16
    # make clean: Apaga todos os programas compilados para limpar a pasta
# Para Executar:
    # ./questao06: Executa o programa da questão 06 e assim por diante

all: questao06 questao10 questao12 questao16

questao06: questao06.cpp Grafo.cpp
	g++ -Wall -o questao06 questao06.cpp Grafo.cpp

questao10: questao10.cpp Grafo.cpp
	g++ -Wall -o questao10 questao10.cpp Grafo.cpp

questao12: questao12.cpp Grafo.cpp
	g++ -Wall -o questao12 questao12.cpp Grafo.cpp

questao16: questao16.cpp Digrafo.cpp
	g++ -Wall -o questao16 questao16.cpp Digrafo.cpp

clean:
	del /Q questao06.exe questao10.exe questao12.exe questao16.exe 2>nul