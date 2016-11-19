.PHONY: clean all

CFLAGS = -g -Wall -std=c++0x -I./include

all: main
src/opt.cpp: src/opt.hpp

obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

bin/main: obj/main.o obj/opt.o obj/util.o
	$(CXX) $^ -o bin/main $(LFLAGS)

test: bin/main
	@./bin/main

clean:
	@rm -rf obj/* bin/* src/*~ *~ core
