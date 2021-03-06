# compiler
CC=g++

# compiler flags (no flags are used)
CFLAGS=

# Executable
EXE = MonteCarlo

# object files (.cpp files with .o instead of .cpp)
OBJ = main.o MonteCarlo.o CommandLineHandler.o

# all
all: $(EXE)

# build executable from object files
# Flag -o is for setting output name
$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# create object files
# an object file (%.o) is built from a .cpp file sharing the same name (%.cpp)
# and depends on a header file (%.h) sharing the same name
# Flag -o is for setting output name
# Flag -c is for telling the compiler to build object files
# $@ is the file name of the object, $< is the first dependency (the .cpp file)
%.o: %.cpp %.h
	$(CC) -c -o $@ $< $(CFLAGS)

# clean project from all files generated by makefile
clean:
	rm *.o $(EXE)
