#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BRAND_LENGTH 16
#define MAX_OWNER_LENGTH 256

typedef struct {
    char brand[MAX_BRAND_LENGTH];
    char owner[MAX_OWNER_LENGTH];
    float mileage;
} Car;

void StdinInput(Car **cars, int *count);
void TxtInput(Car **cars, int *count, const char *filename);
void BinInput(Car **cars, int *count, const char *filename);
void StdOutput(Car *cars, int count);
void ShakerSort(Car *cars, int count, int ascending);
void DoubleSelectionSort(Car *cars, int count, int ascending);

int main(int argc, char *argv[]) {
    Car *cars;
    int count;

    if (argc < 2) {
        fprintf(stderr, "Использование: %s <mode> [filename]\n", argv[0]);
        fprintf(stderr, "mode: stdin | text | binary\n");
        return EXIT_FAILURE;
    }

    const char *mode = argv[1];

    if (strcmp(mode, "stdin") == 0) {
        StdinInput(&cars, &count);
    } else if (strcmp(mode, "text") == 0 && argc == 3) {
        TxtInput(&cars, &count, argv[2]);
    } else if (strcmp(mode, "binary") == 0 && argc == 3) {
        BinInput(&cars, &count, argv[2]);
    } else {
        fprintf(stderr, "Неправильный режим или отсутствует имя файла. Используйте 'stdin', 'text' или 'binary'.\n");
        return EXIT_FAILURE;
    }

    StdOutput(cars, count);

    ShakerSort(cars, count, 1);
    StdOutput(cars, count);

    free(cars);
    return EXIT_SUCCESS;
}

void StdinInput(Car **cars, int *count) {
    printf("Введите количество автомобилей: ");
    scanf("%d", count);
    getchar();

    *cars = (Car *)malloc(*count * sizeof(Car));

    for (int i = 0; i < *count; i++) {
        printf("Введите марку автомобиля: ");
        scanf("%s", (*cars)[i].brand);
        getchar();

        printf("Введите ФИО владельца автомобиля: ");
        fgets((*cars)[i].owner, MAX_OWNER_LENGTH, stdin);
        (*cars)[i].owner[strcspn((*cars)[i].owner, "\n")] = '\0';

        printf("Введите пробег автомобиля (в тыс. км): ");
        scanf("%f", &(*cars)[i].mileage);
        getchar();
    }
}


void TxtInput(Car **cars, int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Ошибка открытия файла %s\n", filename);
        return;
    }
    
    fscanf(file, "%d", count);
    getchar();
    *cars = (Car *)malloc(*count * sizeof(Car));

    for (int i = 0; i < *count; i++) {
        fscanf(file, "%s", (*cars)[i].brand);
        fgets((*cars)[i].owner, MAX_OWNER_LENGTH, file);
        (*cars)[i].owner[strcspn((*cars)[i].owner, "\n")] = '\0';
        fscanf(file, "%f", &(*cars)[i].mileage);
    }

    fclose(file);
}

void BinInput(Car **cars, int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Ошибка открытия файла %s\n", filename);
        return;
    }

    fread(count, sizeof(int), 1, file);
    *cars = (Car *)malloc(*count * sizeof(Car));
    
    fread(*cars, sizeof(Car), *count, file);

    fclose(file);
}

void StdOutput(Car *cars, int count) {
    for (int i = 0; i < count; i++) {
        printf("Марка: %s, Владелец: %s, Пробег: %.2f тыс. км\n", cars[i].brand,
               cars[i].owner,
               cars[i].mileage);
    }
}

void ShakerSort(Car *cars, int count, int ascending) {
    int left = 0;
    int right = count - 1;
    
    while (left < right) {
        for (int i = left; i < right; i++) {
            if ((ascending && strcmp(cars[i].brand, cars[i + 1].brand) > 0) ||
                (!ascending && strcmp(cars[i].brand, cars[i + 1].brand) < 0)) {
                Car temp = cars[i];
                cars[i] = cars[i + 1];
                cars[i + 1] = temp;
            }
        }
        right--;

        for (int i = right; i > left; i--) {
            if ((ascending && strcmp(cars[i - 1].brand, cars[i].brand) > 0) ||
                (!ascending && strcmp(cars[i - 1].brand, cars[i].brand) < 0)) {
                Car temp = cars[i];
                cars[i] = cars[i - 1];
                cars[i - 1] = temp;
            }
        }
        left++;
    }
}

void DoubleSelectionSort(Car *cars, int count, int ascending) {
    for (int i = 0; i < count / 2; i++) {
        int min_idx = i;
        int max_idx = i;

        for (int j = i; j < count - i; j++) {
            if ((ascending && strcmp(cars[j].brand, cars[min_idx].brand) < 0)) {
                min_idx = j;
            }
            if ((ascending && strcmp(cars[j].brand, cars[max_idx].brand) > 0)) {
                max_idx = j;
            }
        }

        if (min_idx != max_idx) {
            Car temp_min = cars[min_idx];
            cars[min_idx] = cars[i];
            cars[i] = temp_min;

            if (max_idx == i) {
                max_idx = min_idx;
            }

            Car temp_max = cars[max_idx];
            cars[max_idx] = cars[count - i - 1];
            cars[count - i - 1] = temp_max;
        }
    }
}
