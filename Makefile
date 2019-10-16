OBJ = main.o Block.o Point.o
SRC = Block.cpp Point.cpp main.cpp
INC = inc/Block.h inc/Point.h
CFLAGS = 

SRCWP = $(addprefix src/, $(SRC))

CXX = g++
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

#all: $(INC) $(OBJ)
#	$(CXX) -o main $(OBJ) $(LDLIBS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(LDLIBS)

main.o: $(SRCWP) $(INC)
	$(CXX) -c $(SRCWP)

Block.o: src/Block.cpp inc/Block.h src/Point.cpp inc/Point.h
	$(CXX) -c src/Block.cpp

Point.o: src/Point.cpp inc/Point.h
	$(CXX) -c src/Point.cpp


clean: 
	$(RM) main $(OBJ)




