.DEFAULT_GOAL := build

obj/intcode.o:
	mkdir -p obj
	g++ -o obj/intcode.o -c ../intcode/intcode.cpp -I ../intcode/

bin/part1.out: obj/intcode.o part1.cpp
	mkdir -p bin
	g++ -o bin/part1.out part1.cpp obj/intcode.o -I ../intcode/

bin/part2.out: obj/intcode.o part2.cpp
	mkdir -p bin
	g++ -o bin/part2.out part2.cpp obj/intcode.o -I ../intcode/

build: bin/part1.out bin/part2.out

run_1: bin/part1.out
	bin/part1.out

run_2: bin/part2.out
	bin/part2.out

clean:
	rm -rf bin
	rm -rf obj