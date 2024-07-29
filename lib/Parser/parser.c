#import "./parser.h"
#include <assert.h>
#include <stdio.h>

int current = 0, start = 0;
int list_index = 0, in_list = 0;

int readFileContent(char* dest, char* filename) {
	char* buffer = 0;
	long length;
	FILE* f = fopen(filename, "rb");

	if (f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = malloc(length);
		if (buffer) {
			fread(buffer, 1, length, f);
		}
		fclose(f);
	} else {
		perror("INVALID FILE");
	}

	if (buffer) {
		strncpy(dest, buffer, MAX_SIZE);
		return 1;
	} else return 0;
}

char* substring(const char* source, int start, int finish) {
	int length = finish - start + 1;
	char* sub = (char*)malloc((length + 1) * sizeof(char));
	if (sub == NULL) {
		perror("Unable to allocate memory");
		exit(EXIT_FAILURE);
	}
	strncpy(sub, source + start, length);
	sub[length] = '\0';
	return sub;
}

int isAtEnd(char* source) {
	return current >= strlen(source);
}

char advance(char* source) {
	return source[current++];
}

int isNumber(char c) {
	return c >= '0' && c <= '9';
}

char peek(char* source) {
	return source[current];
}

char peekPrevious(char* source) {
	if (current - 2 < 0) {
		perror("Index out of range");
		exit(EXIT_FAILURE);
	}
	return source[current - 1];
}

char peekNext(char* source) {
	if (current > strlen(source)) {
		perror("Index out of range");
		exit(EXIT_FAILURE);
	}
	return source[current + 1];
}

char consume(char* source, char c) {
	while (peek(source) == c) advance(source);
	return peek(source);
}

int consumeNumber(char *source, int i) {
    int result = 0;
    int sign = 1;
    if (source[i] == '-' || source[i] == '+') {
        if (source[i] == '-') {
            sign = -1;
        }
		i++;
		advance(source);
    }
    while (isNumber(source[i])) {
        int digit = source[i] - '0';
        // Check for overflow
        if (sign == 1 && (result > (2147483647 - digit) / 10)) {
            result = 2147483647;
            break;
        } else if (sign == -1 && (result > (2147483648U - digit) / 10)) {
            result = -2147483648;
            break;
        }
        result = result * 10 + digit;
		i++;
        advance(source);
    }
    return result * sign;
}

void hash(char* source) {
	while (peek(source) == '#') advance(source);
	int len = current - start;
	while (peek(source) == ' ') advance(source);
	start = current;
	while (peek(source) != '\n' && !isAtEnd(source)) advance(source);
	printf("h%d: %s", len, substring(source, start, current));
}


void parse(char* source) {
	char c = advance(source);
	switch (c) {
		case '\n':
		case ' ':
			start = current;
			consume(source, c);
			break;
		case '#':
			hash(source);
			break;
	}
	if (isNumber(c)) number(source);
}

void parseFile(char* filename) {
	char source[MAX_SIZE];
	readFileContent(source, filename);
	while (!isAtEnd(source)) {
		start = current;
		parse(source);
	}
	// close html
}
