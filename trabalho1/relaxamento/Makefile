CC=g++
FLAGS=-lm
DIM = 4

all: relaxamento.cpp matriz.dat
	$(CC) -o relaxamento relaxamento.cpp && ./relaxamento matriz.dat

att: gerar_matriz.cpp
	$(CC) -o gerarmatriz gerar_matriz.cpp && ./gerarmatriz $(DIM) > matriz.dat

clean: jacobi gerarmatriz
	rm -r relaxamento gerarmatriz  