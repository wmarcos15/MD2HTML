#include "../lib/Parser/parser.h"

int main(int argc, char *argv[])
{
	char filename[] = "./test.md";
	parseFile(filename);
	return 0;
}
