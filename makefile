# ajouter -lSDL2_gfx eventuellement
SRC_PATH=./src/
CC=g++ 
CFLAGS=-c -Wall
LDFLAGS=-w -lmingw32 -lSDL2main -lSDL2 
INCL=-Iinclude
LIB=-Llib
EXE=Main

SRC:=$(wildcard $(SRC_PATH)*.cpp)
SRC := $(filter-out $(SRC_PATH)main_temp.cpp, $(SRC))
OBJ=$(subst ./src, ./obj, $(SRC:.cpp=.o))

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) -g -o $@ $(OBJ) $(LIB) $(LDFLAGS)

./obj/%.o: ./src/%.cpp
	$(CC) -g -o $@ $< $(CFLAGS) $(INCL) 

clean:
	del .\obj\*