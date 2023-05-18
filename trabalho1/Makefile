CC=g++
FLAGS=-lm
DIM = 5

all: main.cpp gerar_matriz.cpp
	$(CC) -o trabalho main.cpp && ./trabalho matriz.dat

att: gerar_matriz.cpp
	$(CC) -o gerarmatriz gerar_matriz.cpp && ./gerarmatriz $(DIM) > matriz.dat



clean: gerarmatriz trabalho
	rm -r trabalho gerarmatriz