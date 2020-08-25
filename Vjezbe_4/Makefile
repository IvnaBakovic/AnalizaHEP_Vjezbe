CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

analyzer: analyzer.o Analyzer.o
	$(CC) $(LDFLAGS) -o analyzer analyzer.o Analyzer.o

clean:
	rm -rf *.o analyzer
