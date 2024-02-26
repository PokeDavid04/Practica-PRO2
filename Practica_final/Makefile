OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cluster.o Procesador.o Proceso.o AreaProcesos.o
	g++ -o program.exe *.o 

Cluster.o: Cluster.cc Cluster.hh Procesador.hh BinTree.hh
	g++ -c Cluster.cc $(OPCIONS)

AreaProcesos.o: AreaProcesos.cc AreaProcesos.hh Proceso.hh
	g++ -c AreaProcesos.cc $(OPCIONS)

Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONS) 

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS) 

program.o: program.cc Cluster.hh AreaProcesos.hh Procesador.hh Proceso.hh
	g++ -c program.cc $(OPCIONS) 

tar2:
	tar -cvf practica.tar program.exe *.cc *.hh Makefile

tar:
	tar -cvf practica.tar *.cc *.hh Makefile html.zip jp_david.berrocal.fidalgo.zip

clean:
	rm -f *.o
	rm -f *.gch
	
