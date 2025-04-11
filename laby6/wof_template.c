#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTS 20

int guess_a_letter(char* text, const char* original_text) {
    const char letter = (rand() % ('Z' - 'A' + 1)) + 'A';
    int i = 0, result = 0;

    if (text == NULL) return 0;

    while (original_text[i]) {
        if (original_text[i] == letter && text[i] == '_') {
            result++;
            text[i] = letter;
        }
        i++;
    }
    return result;
}

char* play(const char* original_text, const int number_of_players, const int turns, int* p_player) {
    char* display = malloc(sizeof(original_text));
    int i = 0, left_to_guess = 0, guess = 0;

    while (original_text[i]) {
        if (original_text[i] != ' ') {
            display[i] = '_';
            left_to_guess++;
        }

        else
            display[i] = ' ';
        i++;
    }

    for (i=0;i<turns;i++) {
        guess = guess_a_letter(display, original_text);
        if (guess == 0 && i < turns - 1) {
            *p_player = *p_player + 1;
            *p_player = *p_player % number_of_players;
            continue;
        }

        if (guess != 0) {
            left_to_guess -= guess;
            if (left_to_guess == 0) return display;
            i--;

        }

    }

    return display;
}

int main() {

    const char* texts[MAX_TEXTS] = {
        "PAN TADEUSZ",
        "HENRYK SIENKIEWICZ",
        "MORZE KASPIJSKIE",
        "POGODA DLA BOGACZY",
        "CZERWONE GITARY",
        "KAZANIE PIOTRA SKARGI",
        "QUO VADIS",
        "ADAM MICKIEWICZ",
        "ALBERT EINSTEIN",
        "DENNIS RITCHIE",
        "FIZYKA KWANTOWA",
        "PROGRAMOWANIE IMPERATYWNE",
        "ALGORYTMY I STRUKTURY DANYCH",
        "BRIAN KERNIGHAN",
        "CZERWONY KAPTUREK",
        "MARIA KONOPNICKA",
        "WILLIAM SHAKESPEARE",
        "ZBIGNIEW ZAPASIEWICZ",
        "MAGDALENA SAMOZWANIEC",
        "JEZIORO ONTARIO"
    };

    int number_of_players, turns, player=0;
    unsigned seed;

    scanf("%d %u %d", &number_of_players, &seed, &turns);
    srand(seed);
    const int number = rand() % MAX_TEXTS;
    char* text = play(texts[number], number_of_players, turns, &player);
    printf("%s\n", text);
    printf("%d\n", player);
    free(text);

    return 0;

}

