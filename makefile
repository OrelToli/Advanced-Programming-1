# Limor Levi 308142389
# Orel Israeli

a.out: compileAll
	g++ *.o 
	rm -f *.o

compileAll: src/*.h src/*.cpp
	g++ -c src/*.cpp
