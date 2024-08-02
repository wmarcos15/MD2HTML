#include "./html_utils.h"
// Boilerplate
// Write text
// Open pTag
// Close pTag
// Open bTag
// Close bTag

void style(FILE* file) {
	if (file == NULL) {
		perror("INVALID FILE");
		return;
	}

	const char* css = "/* Main body style */\n"
		"body {\n"
		"    background-color: #121212; /* Dark background */\n"
		"    color: #E0E0E0; /* Light text color */\n"
		"    font-family: 'Roboto', sans-serif; /* Modern font */\n"
		"    margin: 0;\n"
		"    padding: 0;\n"
		"    display: flex;\n"
		"    justify-content: center; /* Center horizontally */\n"
		"    align-items: center;\n"
		"    height: 100vh;\n"
		"    box-sizing: border-box;\n"
		"}\n"
		"\n"
		"/* Container for the text */\n"
		".main_text {\n"
		"    max-width: 800px; /* Maximum width */\n"
		"    margin: 2vw; /* Margin on the sides */\n"
		"    padding: 20px; /* Padding inside the container */\n"
		"    box-sizing: border-box;\n"
		"    text-align: justify;\n"
		"}\n"
		"\n"
		"/* Header styles */\n"
		"h1 {\n"
		"    font-size: 2.5em;\n"
		"    margin-bottom: 0.5em;\n"
		"    color: #FF8A65; /* Accent color */\n"
		"}\n"
		"\n"
		"h2 {\n"
		"    font-size: 2em;\n"
		"    margin-bottom: 0.5em;\n"
		"    color: #FFAB91; /* Slightly different accent */\n"
		"}\n"
		"\n"
		"h3 {\n"
		"    font-size: 1.75em;\n"
		"    margin-bottom: 0.5em;\n"
		"    color: #FFCCBC; /* Slightly different accent */\n"
		"}\n"
		"\n"
		"/* List styles */\n"
		"ul, ol {\n"
		"    margin: 1em 0;\n"
		"    padding: 0 1.5em; /* Indent the list */\n"
		"}\n"
		"\n"
		"li {\n"
		"    margin-bottom: 0.5em;\n"
		"    color: #BDBDBD; /* Slightly lighter text color */\n"
		"}\n"
		"\n"
		"/* Custom blockquote class */\n"
		".blockquote {\n"
		"    background-color: rgba(255, 255, 255, 0.1); /* Transparent background */\n"
		"    padding: 15px;\n"
		"    border-left: 5px solid #FF8A65; /* Accent border */\n"
		"    margin: 1em 0;\n"
		"    color: #E0E0E0; /* Light text color */\n"
		"    font-style: italic;\n"
		"}\n"
		"\n"
		"/* Flexbox for centering the main_text div */\n"
		"body > div {\n"
		"    height: 100%;\n"
		"    width: 100%;\n"
		"}\n";

	fprintf(file, "%s", css);
}

void startHTML(FILE * file) {
	if (file == NULL) {
		perror("INVALID FILE");
		return;
	}
	fprintf(file, "<!DOCTYPE html>\n");
	fprintf(file, "<html lang=\"en\">\n");
	fprintf(file, "<head>\n");
	fprintf(file, "    <meta charset=\"UTF-8\">\n");
	fprintf(file, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
	fprintf(file, "    <title>MD2HTML</title>\n");
	fprintf(file, "    <style>\n");
	style(file);
	fprintf(file, "    </style>\n");
	fprintf(file, "</head>\n");
	fprintf(file, "<body>\n");
	fprintf(file, "<div class=\"main_text\">\n");
}

void hHTML(FILE* file, int type, char* lexeme) {
	fprintf(file, "<h%d>%s</h%d>\n", type, lexeme, type);
}

FILE* beginHTML(char* name) {
	char filename[500000];
	int i = 0;
	while (name[i] != '.') {
		filename[i] = name[i];
		i++;
	}
	filename[i] = '.';
	filename[i+1] = 'h';
	filename[i+2] = 't';
	filename[i+3] = 'm';
	filename[i+4] = 'l';
	filename[i+5] = '\0';

	FILE* html = fopen(filename, "w");
	startHTML(html);
	return html;
}

void closeHTML(FILE* file) {
	fprintf(file, "</div>\n");
	fprintf(file, "</body>\n");
	fprintf(file, "</html>\n");
	fclose(file);
}
