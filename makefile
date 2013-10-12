CC=clang++
SOURCES=src/*.cpp
OBJECTS=build/*.o
SOURCEDIR=src
OBJECTDIR=build
STDLIBS=-std=c++11 -stdlib=libc++
SFMLLIBS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
EXECUTABLE=Game
LDFLAGS=-lm

all: $(EXECUTABLE)
	@echo "Compilation and linking successful."

$(EXECUTABLE): $(OBJECTS)
	@echo "- Linking object files and libraries..."
	$(CC) $(STDLIBS) $(OBJECTS) -o $(EXECUTABLE) $(SFMLLIBS)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo "- Creating object file ->" $@
	$(CC) $(STDLIBS) -c $< -o $@

fallback:
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(SFMLLIBS)

%.o: %.cpp
	$(CC) $< -c $@ $(LIBS)


install: $(EXECUTABLE)

test: $(SOURCES)
	$(CC) -c $(SOURCES) ./build/ $(LIBS)

.PHONY: clean

