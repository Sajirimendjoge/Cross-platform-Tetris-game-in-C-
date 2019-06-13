#SOURCES specifies which files to compile as part of the project
SOURCES=$(wildcard ./*.cpp)

#OBJECTS are the object file for each file
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

#CC specifies which compiler we're using
CC = g++

#LDFLAGS specifies what we're linking against
LDFLAGS = -lSDL2 -lSDL2_gfx -lSDL2_ttf -ldl -lpthread -lfreetype

#OBJ_NAME specifies the name of our exectuable
EXECUTABLE=bin/linux/Tetris-linux

#RUNTIME_PATH specifies where to look for the .so file
RUNTIME_PATH=-Wl,-rpath=./

#LIB_PATH specifies the location to find the library
LIB_PATH=-L./lib/linux

#INCLUDE_PATH specifies the location to the header files
INCLUDE_PATH=-I./header/linux

#This is the target that compiles our executable
all : $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(RUNTIME_PATH) $(OBJECTS) $(LIB_PATH) $(LDFLAGS) $(INCLUDE_PATH)

$(OBJECTS): $(SOURCES)
	$(CC) -c $(SOURCES) $(INCLUDE_PATH)


clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) 
