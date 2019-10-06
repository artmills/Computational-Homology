CXXFLAGS=-std=c++17 -g

SOURCES=main.cpp intmat.cpp matsystem.cpp 
OBJECTS=$(subst .cpp,.o,$(SOURCES))

build: $(OBJECTS)
	g++ $(CXXFLAGS) -o build $(OBJECTS) 

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp

intmat.o: intmat.cpp
	g++ $(CXXFLAGS) -c intmat.cpp

matsystem.o: matsystem.cpp
	g++ $(CXXFLAGS) -c matsystem.cpp

