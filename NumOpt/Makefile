.PHONY: clean all

CFLAGS = -g -Wall -std=c++0x

all: main

obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

main: obj/main.o obj/opt.o
	$(CXX) $^ -o bin/main $(LFLAGS)

test: main
	@./bin/main

clean:
	@rm -rf obj/* bin/* src/*~ *~ core
