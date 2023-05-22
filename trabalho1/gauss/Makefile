CC=g++
FLAGS=-lm
DIM = 4

all: gauss.cpp gerar_matriz.cpp
	$(CC) -o gauss gauss.cpp && ./gauss matriz.dat

att: gerar_matriz.cpp
	$(CC) -o gerarmatriz gerar_matriz.cpp && ./gerarmatriz $(DIM) > matriz.dat

clean: gerarmatriz gauss
	rm -r trabalho gerarmatriz