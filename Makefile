# Compiler
CXX = g++
CXXFLAGS = -Wall -g

main.out: main.o
	${CXX} $^ -o $@

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm *.out
	rm *.o