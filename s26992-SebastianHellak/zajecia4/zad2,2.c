#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* File;
    int* numbers;
    int Numb, i;

    if (argc == 1) {
        File = stdin;
    }
    else if (argc == 2) {
        File = fopen(argv[1], "r");
        if (File == NULL) {
            printf("Brak Pliku\n");
            return 1;
        }
    }
    fscanf(File, "%d", &Numb);

    numbers = malloc(Numb * sizeof(int));
    if (numbers == NULL) {
        printf("Blad Alokacji pamieci\n");
        return 1;
    }
    for (i = 0; i < Numb; i++) {
        fscanf(File, "%d", &numbers[i]);
    }
    if (File != stdin) {
        fclose(File);
    }
    for (i = Numb - 1; i >= 0; i--) {
        printf("%d\n", numbers[i]);
    }
    free(numbers);
    return 0;
}
