#INC = /usr/include/pari/
#LIB = /usr/lib/pari/

CPPFLAGS=-std=c++17 -g #-I$(INC) -L$(LIB) -lpari

OBJDIR=obj

SOURCES=main.cpp intmat.cpp matsystem.cpp rowechelonform.cpp smith.cpp homology.cpp quotient.cpp interval.cpp cube.cpp cubicalset.cpp keyhasher.cpp cubesystem.cpp grid.cpp landscape.cpp
OBJECTS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))


build: $(OBJECTS)
	g++ $(CPPFLAGS) -o build $(OBJECTS) 

$(OBJECTS): | obj

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.cpp %.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp -o $(OBJDIR)/main.o

.PHONY : clean
clean: 
	rm build $(OBJECTS)
