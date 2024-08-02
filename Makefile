COMPILER = gcc

MAIN = ./src/main.c
MAIN_OUT = ./bin/main

PARSER = ./lib/Parser/parser.a
LIBS = -L./lib/ $(PARSER)

buildMain:
	$(COMPILER) $(MAIN) -o $(MAIN_OUT) $(LIBS)

buildAll:
	cd lib && make buildLibs && cd ../ && make buildMain
