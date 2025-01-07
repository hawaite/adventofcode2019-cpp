.DEFAULT_GOAL := build

bin/part1.out: part1.cpp
	mkdir -p bin
	g++ -o bin/part1.out part1.cpp

bin/part2.out: part2.cpp
	mkdir -p bin
	g++ -o bin/part2.out part2.cpp

build: bin/part1.out bin/part2.out

run_1: bin/part1.out
	bin/part1.out

run_2: bin/part2.out
	bin/part2.out

clean:
	rm -rf bin