#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char *reverse_sentence(const char *input);

int main() {
    char *user_input = readline("Введите строку: ");
    if (user_input) {
        printf("Вы ввели: %s\n", user_input);
        char *output = reverse_sentence(user_input);
        printf("Отзеркаленная строка: %s\n", output);
        free(output);
        free(user_input);
    }
    return 0;
}

char *reverse_sentence(const char *input) {
    size_t len = strlen(input);
    char *reversed = malloc(len + 1);
    if (!reversed) {
        printf("Ошибка выделения памяти");
    }

    const char *end_of_word = input + len;
    size_t pos = 0;

    for (size_t i = len; i > 0; i--) {
        if (input[i - 1] == ' ' || i == 1) {
            const char *start_of_word;
            if (i == 1) {
                start_of_word = input;
            } else {
                start_of_word = input + i;
            }
            size_t word_size = end_of_word - start_of_word;

            memcpy(reversed + pos, start_of_word, word_size);
            pos += word_size;
            if (i != len) {
                reversed[pos++] = ' ';
            }
            end_of_word = input + i - 1;
        }
    }

    reversed[pos] = '\0';
    return reversed;
}
