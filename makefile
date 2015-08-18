CXX = clang++
CFLAGS = -g -Wall -std=c++11
OBJ = theater-program.o
EXE = theater

all: $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(EXE)

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXE)
