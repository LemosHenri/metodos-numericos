CC=g++
FLAGS=-lm
DIM = 4

all: inv_gauss.cpp gerar_matriz.cpp
	$(CC) -o inversaogauss inv_gauss.cpp && ./inversaogauss matriz.dat

att: gerar_matriz.cpp
	$(CC) -o gerarmatriz gerar_matriz.cpp && ./gerarmatriz $(DIM) > matriz.dat

clean: gerarmatriz gauss
	rm -r inversaogauss gerarmatriz