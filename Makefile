CXXFLAGS=-Wall -Wextra -pedantic -static -std=c++23
CXX=g++
PROG=bin\cpp_digit_boy.exe

cpp_digit_boy: \
	src\main.o \
	src\mnist.o \
	src\matrix.o \
	src\network.o
	$(CXX) $(CXXFLAGS) \
		src\main.o \
		src\mnist.o \
		src\matrix.o \
		src\network.o \
	-o $(PROG)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c src\main.cpp

mnist.o: mnist.cpp
	$(CXX) $(CXXFLAGS) -c src\mnist.cpp

matrix.o: matrix.cpp
	$(CXX) $(CXXFLAGS) -c src\matrix.cpp

network.o: network.cpp
	$(CXX) $(CXXFLAGS) -c src\network.cpp

clean:
	del /Q src\*.o $(PROG)

