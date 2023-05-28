CXX = clang++
PREFIX = /usr/local/opt

CXXFLAGS = -std=c++2b -I$(PREFIX)/mupdf/include -L$(PREFIX)/mupdf/lib -lmupdf

SOURCES = $(wildcard *.cpp)

EXES = $(patsubst %.cpp, %.exe, $(SOURCES))

all: $(EXES)

%.exe: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	rm ./*.exe
