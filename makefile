# ajouter -lSDL2_gfx eventuellement
SRC_PATH=./src/
CC=g++ 
CFLAGS=-c -Wall
LDFLAGS=-w -lpython27 -lmingw32 -lSDL2main -lSDL2 -lyaml-cpp
INCL=-Iinclude -IC:\Python27\include
LIB=-Llib -LC:\Python27\libs
EXE=Main

SRC:=$(wildcard $(SRC_PATH)*.cpp)
SRC := $(filter-out $(SRC_PATH)main_noscripting.cpp, $(SRC))
OBJ=$(subst ./src, ./obj, $(SRC:.cpp=.o))

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) -g -o $@ $(OBJ) $(LIB) $(LDFLAGS)

./obj/%.o: ./src/%.cpp
	$(CC) -g -o $@ $< $(CFLAGS) $(INCL) 

clean:
	del .\obj\*