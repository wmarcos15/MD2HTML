#include "../lib/Parser/parser.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		perror("Usage: md2html filename");
		return 1;
	}
	parseFile(argv[1]);
	return 0;
}
