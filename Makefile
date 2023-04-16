CXX=g++
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++11
# header file path 
CXXFLAGS += -I/root/lapack-3.11/CBLAS/include
CXXFLAGS += -I/root/lapack-3.11/LAPACKE/include
# Object files
OBJ=main.o MAT_DEMO.o INPUT.o TIMER.o

# Executable
EXECUTABLE=program

# Libraries to link
LIBS = -llapacke -lcblas -llapack -lrefblas -lgfortran
LIBS += -L/root/lapack-3.11/build 

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXECUTABLE) $(LIBS)

main.o: main.cpp MAT_DEMO.h INPUT.h TIMER.h
	$(CXX) $(CXXFLAGS) -c main.cpp

MAT_DEMO.o: MAT_DEMO.cpp MAT_DEMO.h TIMER.h
	$(CXX) $(CXXFLAGS) -c MAT_DEMO.cpp

INPUT.o: INPUT.cpp INPUT.h TIMER.h
	$(CXX) $(CXXFLAGS) -c INPUT.cpp

TIMER.o: TIMER.cpp TIMER.h
	$(CXX) $(CXXFLAGS) -c TIMER.cpp

clean:
	rm -f $(OBJ) $(EXECUTABLE)

.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE) "../INPUT/input.txt" "../INPUT/output.txt"
