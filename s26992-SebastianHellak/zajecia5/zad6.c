#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Czytaj() {
    FILE* plik;
    char Wiadomosc[100];

    plik = fopen("/tmp/chat_messages.txt", "r");
    if (plik == NULL) {
        printf("Nie można Odczytać\n");
        exit(1);
    }
    while (fgets(Wiadomosc, 100, plik) != NULL) {
        printf("%s", Wiadomosc);
    }
    fclose(plik);
}

void Zapisz(const char* message) {
    FILE* plik;

    plik = fopen("/tmp/chat_messages.txt", "a");
    if (plik == NULL) {
        printf("Nie można zapisać\n");
        exit(1);
    }
    fprintf(plik, "%s\n", message);
    fclose(plik);
}

int main() {
    char Wiadomosc[100];

    while (1) {
        printf("Wpisz z by wyjść ");
        fgets(Wiadomosc, 100, stdin);
        if (strcmp(Wiadomosc, "z\n") == 0) {
            break;
        }
        Zapisz(Wiadomosc);
        Czytaj();
    }

    return 0;
}
