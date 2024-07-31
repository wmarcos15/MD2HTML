COMPILER = gcc

MAIN = ./src/main.c
MAIN_OUT = ./bin/main

PARSER = ./lib/Parser/parser.a
LIBS = -L./lib/ $(PARSER)

buildMain:
	$(COMPILER) $(MAIN) -o $(MAIN_OUT) $(LIBS)

runMain:
	./bin/main

magic:
	cd lib && make buildLibs && cd ../ && make buildMain && clear && make runMain && open TESTindex.html
