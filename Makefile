CXXFLAGS=-Wall -Wextra -pedantic -ggdb -std=c++23
CXX=g++
PROG=bin\cpp_digit_boy.exe

cpp_digit_boy: src\main.o
	$(CXX) $(CXXFLAGS) src\main.o -o $(PROG)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c src\main.cpp

mnist_reader.o: mnist_reader.cpp
	$(CXX) $(CXXFLAGS) -c src\mnist_reader.cpp

clean:
	del /Q src\*.o $(PROG)

