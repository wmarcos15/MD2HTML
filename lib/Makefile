COMPILER = gcc
OUTPUT = ../bin

HTML_UTILS = ./HTML_Utils/html_utils.c
HTML_UTILS_O_OUT = ../bin/html_utils.o
HTML_UTILS_A_OUT = ./HTML_Utils/html_utils.a

PARSER = ./Parser/parser.c
PARSER_O_OUT = ../bin/parser.o
PARSER_A_OUT = ./Parser/parser.a
PARSER_LIBS = $(HTML_UTILS_O_OUT) $(PARSER_O_OUT)

buildHTML_Utils.o:
	$(COMPILER) -c $(HTML_UTILS) -o $(HTML_UTILS_O_OUT)

buildHTML_Utils.a:
	ar rcs $(HTML_UTILS_A_OUT) $(HTML_UTILS_O_OUT)

buildParser.o:
	$(COMPILER) -c $(PARSER) -o $(PARSER_O_OUT)

buildParser.a:
	ar rcs $(PARSER_A_OUT) $(PARSER_LIBS)

buildLibs:
	make buildHTML_Utils.o
	make buildHTML_Utils.a
	make buildParser.o
	make buildParser.a

make clear:
	rm $(OUTPUT)/*
