CPPFLAGS=-std=c++17 -O3
#CPPFLAGS=-std=c++17 -g

OBJDIR=obj

SOURCES=main.cpp intmat.cpp matsystem.cpp rowechelonform.cpp smith.cpp homology.cpp quotient.cpp interval.cpp cube.cpp cubicalset.cpp keyhasher.cpp cubesystem.cpp grid.cpp landscape.cpp smithlite.cpp
OBJECTS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

#LLIBS = $(shell pkg-config --cflags)


build: $(OBJECTS)
	g++ $(CPPFLAGS) -o build $(OBJECTS) 
	#g++ $(CPPFLAGS) -I $(LLIBS) -o build $(OBJECTS) 

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
