#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define MAX_LINE 128

typedef enum {
	NONE,
	ONE_LINER,
	MULTI_LINER
} comment_status;

void find_comments(int*, int*);
void count_comment(comment_status*, char, char, int*, int*, short*);
int find_idents(void);
int contains(char**, int , const char*);
void isIdent(char, char, char**, comment_status*, short*, int*, int*);
void fill_char(char*);
void cut_word(char*, int*);
int is_letter(char);

char *identifiers[MAX_IDS];

char *keywords[] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

void find_comments(int *line_comment_counter, int *block_comment_counter) {
	*line_comment_counter = 0; *block_comment_counter = 0;
	comment_status curr_comment = NONE;
	short in_string = 0;

	while (1){
		char line[MAX_LINE];
		if (fgets(line, MAX_LINE, stdin) == NULL) break;
		int i=1;
		while (line[i]) {
			count_comment(&curr_comment, line[i-1], line[i], line_comment_counter, block_comment_counter, &in_string);
			i++;
		}
	}
}

void count_comment(comment_status* curr_comment, const char last_char, const char curr_char, int *line_comment_counter, int *block_comment_counter, short* in_string) {
	if (*in_string && curr_char == '"' && last_char != '\\')
		*in_string = 0;

	else if (*in_string)
		return;
	else if (curr_char == '"' && *curr_comment == NONE)
		*in_string = 1;

	switch (*curr_comment) {
		case ONE_LINER:
			if (curr_char == '\n')
				*curr_comment = NONE;
			break;
		case MULTI_LINER:
			if (curr_char == '/' && last_char == '*')
				*curr_comment = NONE;
			break;
		case NONE:
			if (curr_char == '*' && last_char == '/') {
				*curr_comment = MULTI_LINER;
				(*block_comment_counter)++;
			}
			else if (curr_char == '/' && last_char == '/') {
				*curr_comment = ONE_LINER;
				(*line_comment_counter)++;
			}

			break;
	}
}

int find_idents(void) {
	comment_status curr_comment = NONE;
	short in_string = 0;
	int n = 0;
	char* word = malloc(MAX_ID_LEN * sizeof(char));

	while (1){
		char line[MAX_LINE];
		if (fgets(line, MAX_LINE, stdin) == NULL) break;
		int i=1, word_length = 0;
		fill_char(word);


		if (line[0] > '9' && is_letter(line[0])) {
			word[0] = line[0];
			word_length++;
		}
		while (line[i]) {
			isIdent(line [i-1],line[i], &word, &curr_comment, &in_string, &n, &word_length);
			if (curr_comment == ONE_LINER) {
				curr_comment = NONE;
				break;
			}

			i++;
		}

	}
	free(word);
	return n;
}

void cut_word(char* word, int *n) {

	if (contains(identifiers, *n, word) == 0 && contains(keywords, 32, word) == 0) {
		strcpy(identifiers[*n], word);
		*n += 1;
	}
	fill_char(word);
}

void isIdent(const char last_letter, const char letter, char** word, comment_status* curr_comment, short* in_string, int *n, int *word_length) {
	if (letter == '"' && *curr_comment == NONE && *in_string == 0) {
		*in_string = 1;
		return;
	}
	if (letter == '/' && last_letter == '/' && *in_string == 0 && *curr_comment == NONE) {
		*curr_comment = ONE_LINER;
		return;
	}
	if (letter == '*' && last_letter == '/' && *in_string == 0 && *curr_comment == NONE) {
		*curr_comment = MULTI_LINER;
		return;
	}
	if (*in_string == 0 && *curr_comment == NONE && is_letter(letter) == 0 && *word_length > 0) {
		cut_word(*word, n);
		*word_length = 0;
		return;
	}
	if (*in_string && letter == '"' && last_letter != '\\') {
		*in_string = 0;
		return;
	}
	if (*in_string) {
		return;
	}
	if (*curr_comment == MULTI_LINER && last_letter == '*' && letter == '/') {
		*curr_comment = NONE;
		return;
	}
	if (*curr_comment != NONE) {
		return;
	}
	if ((*word_length > 0 && is_letter(letter) == 1) || (letter > '9' && is_letter(letter) == 1)) {
		(*word)[*word_length] = letter;
		*word_length += 1;
		return;
	}


}

int contains(char* unique[], const int n, const char* ident) {
	for (int i=0;i<n;i++) {
		if (strcmp(unique[i], ident) == 0)
			return 1;
	}
	return 0;
}

int read_int() {
	char line[MAX_LINE];
	fgets(line, MAX_LINE, stdin); // to get the whole line
	return (int)strtol(line, NULL, 10);
}

void fill_char(char *word) {
	for (int i=0;i<MAX_ID_LEN;i++) {
		word[i] = 0;
	}
}
int is_letter(const char letter) {
	if((letter > 47 && letter < 58) || (letter > 64 && letter < 91) || letter == 95 || (letter > 96 && letter < 123)) {
		return 1;
	}
	return 0;
}

int main(void) {
	int line_comment_counter, block_comment_counter;
	const int to_do = read_int();
	for (int i=0;i<MAX_IDS;i++) {
		identifiers[i] = calloc(MAX_ID_LEN, sizeof(char));
	}

	switch (to_do) {
		case 1:
			find_comments(&line_comment_counter, &block_comment_counter);
			printf("%d %d\n", block_comment_counter, line_comment_counter);
			break;
		case 2:
			printf("%d\n", find_idents());
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}

	for (int i=0;i<MAX_IDS;i++) {
		free(identifiers[i]);
	}

	return 0;
}

