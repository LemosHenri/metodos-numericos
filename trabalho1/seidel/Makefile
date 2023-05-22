CC=g++
FLAGS=-lm
DIM = 4

all: seidel.cpp matriz.dat
	$(CC) -o seidel seidel.cpp && ./seidel matriz.dat

att: gerar_matriz.cpp
	$(CC) -o gerarmatriz gerar_matriz.cpp && ./gerarmatriz $(DIM) > matriz.dat

clean: jacobi gerarmatriz
	rm -r jacobi gerarmatriz  