DEPENDENCIAS := loja.h loja.cpp

saida: $(DEPENDENCIAS) main.cpp
	g++ -o saida $(DEPENDENCIAS) main.cpp 
