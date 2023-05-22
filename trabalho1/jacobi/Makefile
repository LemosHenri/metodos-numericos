CC=g++
FLAGS=-lm
DIM = 4

all: jacobi.cpp matriz.dat
	$(CC) -o jacobi jacobi.cpp && ./jacobi matriz.dat

att: gerar_matriz.cpp
	$(CC) -o gerarmatriz gerar_matriz.cpp && ./gerarmatriz $(DIM) > matriz.dat

clean: jacobi gerarmatriz
	rm -r jacobi gerarmatriz  