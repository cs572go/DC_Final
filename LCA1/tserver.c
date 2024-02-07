#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

// max client threads allowd
#define MAX_CLIENTS 5

// global struct for client id and client name
struct client_info
{
    int sockfd;
    char name[80];
};

void *handle_client(void *arg)
{
    // client handling thread
    // stays alive till a client is connected
    // ends when client is terminated

    struct client_info *client = (struct client_info *)arg;
    char message[200];
    // int flag=0;

    // read client name once a client connects
    ssize_t name_len = read(client->sockfd, client->name, sizeof(client->name));

    // error handling for name
    if (name_len <= 0)
    {
        // perror("Read name error");
        close(client->sockfd);
        free(client);
        pthread_exit(NULL);
    }
    client->name[name_len] = '\0';
    printf("%s has connected\n", client->name);
    while (1)
    {
        // keep reading and printing all client messages
        ssize_t message_len = read(client->sockfd, message, sizeof(message));

        if (message_len <= 0)
        {
            // perror("Read message error");
            break;
        }
        message[message_len] = '\0';

        // if the read message was bye, print that client has left and stop listening
        if (strcmp(message, "bye") == 0)
        { // Remove '\n' from "bye"
            printf("%s has left the chat.\n", client->name);
            break;
        }

        printf("%s says: %s\n", client->name, message);
    }

    // close client connection and end the thread
    close(client->sockfd);
    free(client);
    pthread_exit(NULL);
}

int main()
{
    int server_sockfd;
    struct sockaddr_in server_address;
    pthread_t threads[MAX_CLIENTS];

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // error handling for socket creation
    if (server_sockfd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    // change the inet_addr to desired ip and change the port to desired port
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9129);

    // error handling for binding ip address
    if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Bind failed");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    // server has started and is waiting for clients
    printf("Server waiting for connections...\n");
    listen(server_sockfd, MAX_CLIENTS);

    while (1)
    {
        // keeps listening for clients
        // spawns a thread when new client connects
        // closes thread when client leaves
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);

        int client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

        // error handling for client connection to server
        if (client_sockfd == -1)
        {
            perror("Accept failed");
            continue;
        }

        // new client has connected
        struct client_info *client = (struct client_info *)malloc(sizeof(struct client_info));

        // error handling for new client
        if (client == NULL)
        {
            perror("Memory allocation failed");
            close(client_sockfd);
            continue;
        }

        // set new client id and spawn thread
        client->sockfd = client_sockfd;
        pthread_create(&threads[MAX_CLIENTS], NULL, handle_client, (void *)client);
    }

    close(server_sockfd);
    exit(EXIT_SUCCESS);
}
