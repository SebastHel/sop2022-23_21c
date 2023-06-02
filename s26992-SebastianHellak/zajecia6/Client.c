#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define Size_Buf 1024

int Zapis(int sockf, char* fileN) {
    int wartosc;
    char buffer[Size_Buf];
    FILE* file;
    file = fopen(fileN, "w");

    while (1) {
        wartosc = recv(sockf, buffer, Size_Buf, 0);
        if (n <= 0) {
            break;
        }
        fprintf(file, "%s", buffer);
        bzero(buffer, Size_Buf);
    }
    fclose(file);
    return 0;
}

int main(int argc, char* argv[])
{
    int sockf, port, connection;
    struct sockaddr_in serwer_addres;
    char* fileN = argv[2];

    if (argc < 3) {
        exit(1);
    }
    sockf = socket(AF_INET, SOCK_STREAM, 0);
    if (sockf < 0) {
        perror("Socket error\n");
    }
    port = atoi(argv[1]);
    serwer_addres.sin_family = AF_INET;
    serwer_addres.sin_addr.s_addr = INADDR_ANY;
    serwer_addres.sin_port = port;
    connection = connect(sockf, (struct sockaddr*)&serwer_addres, sizeof(serwer_addres));

    if (connection == -1) {
        perror("błąd połączenia\n");
        exit(1);
    }
    if (send(sockf, fileN, strlen(fileN), 0) < 0) {
        perror("Błąd wysyłki");
        exit(1);
    }
    if (Zapis(sockf, fileN) == 0) {
        printf("Pliki przesłane pomyślnie\n");
        return 0;
    }
    else {
        exit(1);
    }
    close(sockf);

    return 0;
}
