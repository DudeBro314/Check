#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse_sentence(const char *input);
char *get_user_input(const char *prompt);

int main() {
    char *user_input = get_user_input("Введите строку: ");
    if (user_input) {
        printf("Вы ввели: %s\n", user_input);
        char *output = reverse_sentence(user_input);
        printf("Отзеркаленная строка: %s\n", output);
        free(output);
        free(user_input);
    }
    return 0;
}

char *get_user_input(const char *prompt) {
    printf("%s", prompt);
    size_t size = 0;
    char *buffer = NULL;

    ssize_t len = getline(&buffer, &size, stdin);
    if (len == -1) {
        perror("Ошибка чтения строки");
        free(buffer);
        return NULL;
    }
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

char *reverse_sentence(const char *input) {
    size_t len = strlen(input);
    char *reversed = malloc(len + 1);
    if (!reversed) {
        printf("Ошибка выделения памяти\n");
        return NULL;
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
