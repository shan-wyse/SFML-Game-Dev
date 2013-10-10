CC=clang++
SOURCES=src/*.cpp
OBJECTS=build/*.o # $(SOURCES:.cpp=.o)
SOURCEDIR=src
OBJECTDIR=build
STDLIBS=-std=c++11 -stdlib=libc++
LIBS=-std=c++11 -stdlib=libc++ -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
EXECUTABLE=./Game
LDFLAGS=-lm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(STDLIBS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS) $(LIBS)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CC) -c -o $@ $< $(STDLIBS)

fallback:
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(LIBS)

%.o: %.cpp
	$(CC) -c $< $@ $(LIBS)


install: $(EXECUTABLE)

test: $(SOURCES)
	$(CC) -c $(SOURCES) ./build/ $(LIBS)

.PHONY: clean

