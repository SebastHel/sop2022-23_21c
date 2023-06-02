#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define FORBIDDEN_LIST_SIZE 3

char* forbidden_list[FORBIDDEN_LIST_SIZE] = {
    "/secret",
    "/hidden",
    "/private"
};

void handle_connection(int client_socket, const struct sockaddr_in* client_address) {
    char buffer[BUFFER_SIZE];
    char request[BUFFER_SIZE];

    memset(buffer, 0, sizeof(buffer));
    memset(request, 0, sizeof(request));

    ssize_t bytes_read;
    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        strncpy(request, buffer, sizeof(request) - 1);
        int i;
        for (i = 0; i < FORBIDDEN_LIST_SIZE; ++i) {
            if (strstr(request, forbidden_list[i]) != NULL) {
                write(client_socket, response, strlen(response));
                close(client_socket);
                return;
            }
        }
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address->sin_addr), client_ip, INET_ADDRSTRLEN);
        printf("Client connected: %s\n", client_ip);

        write(client_socket, response, strlen(response));

        memset(buffer, 0, sizeof(buffer));
        memset(request, 0, sizeof(request));
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;
    pid_t child_pid;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    if (listen(server_socket, 10) < 0) {
        perror("Error listening for connections");
        exit(1);
    }

    printf("Server started\n");

    while (1) {
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Error accepting client connection");
            exit(1);
        }

        child_pid = fork();
        if (child_pid < 0) {
            perror("Error forking process");
            exit(1);
        }
        else if (child_pid == 0) {
            close(server_socket);
            handle_connection(client_socket, &client_address);
            exit(0);
        }
        else {
            close(client_socket);
            waitpid(-1, NULL, WNOHANG);
        }
    }

    close(server_socket);

    return 0;
}
