CC = g++
MINGW = i686-w64-mingw32-g++
CPP = $(shell find . -name *.cpp)
H = $(shell find . -name *.hh)
GCH = $(shell find . -name *.gch)
LDFLAGS = -I $$HOME/Dev/Terminal-Play/src -L $$HOME/Dev/Terminal-Play/build -lterminalplay

build: $(CPP) $(H)
	$(CC) -std=c++11 -static $(LDFLAGS) -c $(CPP) $(H)
	$(CC) *.o $(LDFLAGS) -o game -static
	rm -rf $(GCH)
	./game

windows: $(CPP) $(H)
	$(MINGW) -std=c++11 -static $(LDFLAGS) -c $(CPP) $(H)
	$(MINGW) *.o $(LDFLAGS) -o game.exe -static
	

clean:
	rm -rf *.o
	rm -rf $(GCH)
	rm -rf game game.exe
