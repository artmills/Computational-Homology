#CPPFLAGS=-std=c++17 -O3
#LBCPPFLAGS=-std=c++17 -O3 $(shell pkg-config --cflags givaro linbox)
CPPFLAGS=-std=c++17 -g
LBCPPFLAGS=-std=c++17 -g $(shell pkg-config --cflags givaro linbox)
LLIBS=$(shell pkg-config --libs givaro linbox)

OBJDIR=obj

SOURCES=intmat.cpp matsystem.cpp rowechelonform.cpp smith.cpp quotient.cpp interval.cpp cube.cpp cubicalset.cpp keyhasher.cpp grid.cpp landscape.cpp smithlite.cpp matrix.cpp
LBSOURCES=compiler.cpp

OBJECTS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))
LBOBJECTS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(LBSOURCES))


build: $(OBJECTS) $(LBOBJECTS)
	g++ $(LBCPPFLAGS) $(LLIBS) -o build $(OBJECTS) $(LBOBJECTS)

$(OBJECTS): | obj
$(LBOBJECTS): | obj

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.cpp %.hpp
	g++ $(LBCPPFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp -o $(OBJDIR)/main.o

.PHONY : clean
clean: 
	rm build $(OBJECTS) $(LBOBJECTS)

.PHONY : lbclean
lbclean: 
	rm build $(LBOBJECTS)
