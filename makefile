# CPSC 441 Assignment 4
# Glenn Skelton
# 10041868
#
# Project makefile

GCC = g++
FLAGS = -Wall -g
LDLIBS = -lm

SRC = main.cpp simulator.cpp bozon.cpp atmosphere.cpp
HDR = $(SRC:.cpp=.h)
OBJ = $(SRC:.cpp=.o)
MAIN = simulator

# build and run the simulation. After clean everything up
run:
	make all
	./$(MAIN)
	make clean

# build rules
all: main

main: main.cpp $(OBJ)
	$(GCC) $(FLAGS) $(LDLIBS) $(OBJ) -o $(MAIN)

%.o: %.cpp $(HDR) 
	$(GCC) $(FLAGS) $(LDLIBS) $< -c

clean: 
	$(RM) $(OBJ) $(MAIN)

.PHONY:
	clean all