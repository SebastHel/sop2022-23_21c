#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void handle_client(int client_socket) {
    int file_name_length;
    if (recv(client_socket, &file_name_length, sizeof(file_name_length), 0) < 0) {
        perror("Błąd odczytu długości nazwy pliku");
        close(client_socket);
        return;
    }

    char file_name[file_name_length];
    if (recv(client_socket, file_name, file_name_length, 0) < 0) {
        perror("Błąd odczytu nazwy pliku");
        close(client_socket);
        return;
    }

    printf("Żądanie pliku: %s\n", file_name);

    FILE* file = fopen(file_name, "rb");
    if (file == NULL) {

        int file_size = -1;
        send(client_socket, &file_size, sizeof(file_size), 0);
        perror("Błąd otwarcia pliku");
        close(client_socket);
        return;
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);


    send(client_socket, &file_size, sizeof(file_size), 0);

    char buffer[1024];
    int remaining_bytes = file_size;
    while (remaining_bytes > 0) {
        int bytes_to_read = (remaining_bytes < sizeof(buffer)) ? remaining_bytes : sizeof(buffer);
        int bytes_read = fread(buffer, 1, bytes_to_read, file);
        send(client_socket, buffer, bytes_read, 0);
        remaining_bytes -= bytes_read;
    }

    fclose(file);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Błąd tworzenia gniazda");
        exit(EXIT_FAILURE);
    }

    // Ustalanie adresu serwera
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(123);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Błąd bindowania gniazda");
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, 1) < 0) {
        perror("Błąd nasłuchiwania");
        exit(EXIT_FAILURE);
    }

    printf("Serwer jest gotowy do odbioru plików.\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Błąd akceptacji połączenia");
            exit(EXIT_FAILURE);
        }

        printf("Połączono z %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        handle_client(client_socket);
    }
    close(server_socket);

    return 0;
}
