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

	const char* css = 
		"/* Dark Mode Styles */\n"
		"body {\n"
		"    background-color: #121212;\n"
		"    color: #e0e0e0;\n"
		"    font-family: 'Roboto', sans-serif;\n"
		"    margin: 0;\n"
		"    padding: 0;\n"
		"    line-height: 1.6;\n"
		"    display: block;\n"
		"    width: 80%%;\n"
		"    max-width: 800px;\n"
		"    margin-left: auto;\n"
		"    margin-right: auto;\n"
		"}\n"
		"\n"
		"/* Heading Styles */\n"
		"h1, h2, h3 {\n"
		"    margin-top: 0;\n"
		"    font-weight: 700;\n"
		"    color: #ffffff;\n"
		"}\n"
		"\n"
		"h1 {\n"
		"    font-size: 2.5rem;\n"
		"}\n"
		"\n"
		"h2 {\n"
		"    font-size: 2rem;\n"
		"}\n"
		"\n"
		"h3 {\n"
		"    font-size: 1.75rem;\n"
		"}\n"
		"\n"
		"/* List Styles */\n"
		"ul, ol {\n"
		"    margin: 1rem 0;\n"
		"    padding: 0 1.5rem;\n"
		"}\n"
		"\n"
		"li {\n"
		"    margin: 0.5rem 0;\n"
		"}\n"
		"\n"
		"/* Custom Blockquote Class */\n"
		".blockquote {\n"
		"    background-color: rgba(255, 255, 255, 0.1);\n"
		"    border-left: 4px solid #ff9800;\n"
		"    margin: 1.5rem 0;\n"
		"    padding: 1rem 1.5rem;\n"
		"    font-style: italic;\n"
		"    color: #cccccc;\n"
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
	fprintf(file, "    <title>Boilerplate HTML</title>\n");
	fprintf(file, "    <style>\n");
	style(file);
	fprintf(file, "    </style>\n");
	fprintf(file, "</head>\n");
	fprintf(file, "<body>\n");
}

void hHTML(FILE* file, int type, char* lexeme) {
	fprintf(file, "<h%d>%s</h%d>\n", type, lexeme, type);
}

FILE* beginHTML(char* name) {
	FILE* html = fopen(name, "w");
	startHTML(html);
	return html;
}

void closeHTML(FILE* file) {
	fprintf(file, "</body>\n");
	fprintf(file, "</html>\n");
	fclose(file);
}
