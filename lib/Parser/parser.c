#import "./parser.h"
#include <string.h>
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
		return 0;
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

char peekNextNext(char* source) {
	if (current > strlen(source)) {
		perror("Index out of range");
		exit(EXIT_FAILURE);
	}
	return source[current + 2];
}

int isNewLineToken(char c) {
	return (c == '#' ||
			c == '>');
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
	current--;
    return result * sign;
}

void hash(FILE* file, char* source) {
	int n = 1;
	while (peek(source) == '#') {
		advance(source);
		n++;
	}
	while (peek(source) == ' ') advance(source);
	start = current;
	while (peek(source) != '\n' && !isAtEnd(source)) advance(source);
	hHTML(file, n, substring(source, start, current));
}

int doubleBoldChar(char* source) {
	return (peek(source) == '*' && peekNext(source) == '*') ||
		   (peek(source) == '*' && peekPrevious(source) == '*') ||
		(peek(source) == '_' && peekNext(source) == '_') ||
		   (peek(source) == '_' && peekPrevious(source) == '_');
}

void bold(FILE* file, char* source) {
	advance(source);
	advance(source);
	int bold_start = current;
	while (!isAtEnd(source) && !doubleBoldChar(source) && peek(source) != '\n') {
		advance(source);
	}
	if (isAtEnd(source) || peek(source) == '\n') {
		fprintf(file, "%s", substring(source, bold_start - 2, current - 1));
		return;
	} else if (doubleBoldChar(source)) {
		fprintf(file, "<b>%s</b>", substring(source, bold_start, current - 1));
		advance(source);
		advance(source);
	}
}

void italic(FILE* file, char* source) {
	advance(source);
	int bold_start = current;
	while (!isAtEnd(source) && peek(source) != '*' && peek(source) != '_' && peek(source) != '\n') {
		advance(source);
	}
	if (isAtEnd(source) || peek(source) == '\n') {
		fprintf(file, "%s", substring(source, bold_start - 1, current - 1));
		return;
	} else if (peek(source) == '*' || peek(source) == '_') {
		fprintf(file, "<i>%s</i>", substring(source, bold_start, current - 1));
		advance(source);
	}
}

int isNewLine(char* source) {
	return peek(source) == '\n' && peekNext(source) == '\n';
}

void consumeLexeme(FILE* file, char* source) {
	while (!isAtEnd(source) && peek(source) != '\n') {
		if (peek(source) == '*') {
			if (peekNext(source) == '*') bold(file, source);
			else italic(file, source);
		}
		if (isAtEnd(source) || peek(source) == '\n') return;
		fprintf(file, "%c", peek(source));
		advance(source);
	}
}

void consumeString(FILE* file, char* source) {
	while (!isAtEnd(source) && !isNewLine(source)) {
		if (peek(source) == '_') {
			if (peekNext(source) == '_') bold(file, source);
			else italic(file, source);
		} else if (peek(source) == '*') {
			if (peekNext(source) == '*') bold(file, source);
			else italic(file, source);
		} 
		if (isAtEnd(source) || isNewLine(source) || isNewLineToken(peek(source))) return;
		fprintf(file, "%c", advance(source));
	}
}

void string(FILE* file, char* source) {
	fprintf(file, "<p>");
	current--;
	consumeString(file, source); 
	fprintf(file, "</p>");
	return;
}

void number(FILE* file, char* source) {
	int num = consumeNumber(source, current - 1);
	int new_num = 0;
	if (!(peek(source) == '.' && peekNext(source) == ' ' ) || num != 1) {
		current = start + 1;
		string(file, source);
		return;
	}
	fprintf(file, "<ol>\n");
	do {
		// Consume the '.' and the ' '
		advance(source);
		advance(source);

		fprintf(file, "<li>");
		consumeLexeme(file, source);
		fprintf(file, "</li>\n");

		if (isAtEnd(source) || !isNumber(peekNext(source))) break;
		advance(source);
		advance(source);

		new_num = consumeNumber(source, current - 1);
		if ((new_num - num) != 1) break;
		else num = new_num;

	} while(!isAtEnd(source));

	fprintf(file, "</ol>\n");
}

void blockquote(FILE* file, char* source) {
	while (peek(source) == ' ') advance(source);
	fprintf(file, "<div class=\"blockquote\">");
	consumeLexeme(file, source);
	fprintf(file, "</div>");
}


void unorderedList(FILE* file, char* source) {
	fprintf(file, "<ul>\n");

	do {
		advance(source); // Consume the ' '
		fprintf(file, "<li>");
		consumeLexeme(file, source);
		fprintf(file, "</li>\n");
		if (isAtEnd(source) || peekNext(source) != '-' || peekNextNext(source) != ' ') break;
		advance(source); // Consume the '\n'
		advance(source); // Consume the '-'
	} while(!isAtEnd(source));

	fprintf(file, "</ul>\n");
	advance(source); // Consume linging char
}

int isThreeBacktick(char* source, int pos) {
	if (source[pos] == '`' && source[pos + 1] == '`' && source[pos + 2] == '`') return 1;
	return 0;
}

void codeBlock(FILE* file, char* source) {
	while (peek(source) == '`') advance(source); // Consume all '`'

	int substring_start = current;
	int substring_end = current;
	while (!isThreeBacktick(source, substring_end)) {
		substring_end++;
		if ((substring_end + 2) >= strlen(source)) {
			return string(file, source);
		}
	}

	char* substring_in_block = substring(source, substring_start, substring_end - 1);

	fprintf(file, "<div class=\"code\">");

	// Write the text in lines 
	int i = 0;
	fprintf(file, "<p>");
	while (i < strlen(substring_in_block)) {
		fprintf(file, "%c", substring_in_block[i++]);
		if (substring_in_block[i] == '\n') {
			fprintf(file, "<br>");
		}
	}
	fprintf(file, "</p>");

	fprintf(file, "</div>");
	current = substring_end + 4;
}

void parse(FILE* file, char* source) {
	char c = advance(source);
	while (c == ' ' || c == '\n') c = advance(source);
	switch (c) {
		case '-':
			if (peek(source) == ' ') unorderedList(file, source);
			break;
		case '#':
			hash(file, source);
			while (c == ' ' || c == '\n') c = advance(source);
			break;
		case '>':
			blockquote(file, source);
			break;
		case '`':
			if (peek(source) == '`'	&& peekNext(source) == '`') {
				codeBlock(file, source);
			}
			return;
	}
	if (isNumber(c)) number(file, source);
	else if (!isNewLineToken(c)) string(file, source);
}

void parseFile(char* src) {
	char source[MAX_SIZE];
	readFileContent(source, src);
	FILE* html = beginHTML(src);
	while (!isAtEnd(source)) {
		start = current;
		parse(html, source);
	}
	closeHTML(html);
}
