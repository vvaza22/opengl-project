# Compiler variables. The name CXX is used for C++ compiler and CC for C compiler
CXX = g++
CXXFLAGS = -Wall -g

# Compiled output file name
OUTPUT = program.out

# Important!
# $(...) syntax is used to reference to variables and call functions
# ${...} is same as $(...) probably...

# Space delimited list of every cpp file
SRCS = $(wildcard *.cpp) # Call function wildcard with argument *.cpp
# Example result:
# SRCS = main.cpp shader.cpp camera.cpp

# This is a replace syntax. $(var:suffix=replacement)
OBJS = $(SRCS:.cpp=.o)

# Another example
TESTSRCS = main.cpp.cpp sha.cppder.cpp camera.cpp vertex.cppder
TESTOBJS = $(TESTSRCS:.cpp=.o)

# Take OBJS files and produce OUTPUT file
# If OBJS = main.o camera.o shader.o, these are dependencies for output
# $^ means dependencies i.e. .o files and $@ means target file, i.e. output
# Full syntax will expand to g++ -Wall -g main.o camera.o shader.o -o program.out
$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# %.o means any file that ends with .o
# So if we want to make a file that ends with .o for example myfile.o you need to use myfile.cpp as a dependency
# $< means first dependency
%.o: %.cpp
	$(info Every Dependency: $^)
	$(info First Dependency: $<)
	$(info Target: $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm *.out
	rm *.o

# This syntax is used to print debug information
debug:
	$(info Value of SRCS is equal to: $(SRCS))
	$(info Value of OBJS is equal to: $(OBJS))
	$(info Value of TESTSRCS is equal to: $(TESTSRCS))
	$(info Value of TESTOBJS is equal to: $(TESTOBJS))