CXXFLAGS=-Wall -Wextra -pedantic -static -std=c++23
CXX=g++
PROG=bin\cpp_digit_boy.exe

cpp_digit_boy: src\main.o src\mnist.o
	$(CXX) $(CXXFLAGS) \
		src\main.o \
		src\mnist.o \
	-o $(PROG)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c src\main.cpp

mnist.o: mnist.cpp
	$(CXX) $(CXXFLAGS) -c src\mnist.cpp

clean:
	del /Q src\*.o $(PROG)

