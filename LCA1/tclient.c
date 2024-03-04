#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_address;
    char name[80], message[200];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    // Remove the newline character
    name[strcspn(name, "\n")] = '\0';

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Error handling for socket creation
    if (sockfd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    
    // change the inet_addr to server's ip and change the port to server's port
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9129);

    // error handling for server connection
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // if connected, sends client name to server
    write(sockfd, name, strlen(name));
    while (1)
    {
        // keeps asking the client for input and sends it to server
        printf("Enter your message (type 'bye' to exit): ");
        fgets(message, sizeof(message), stdin);

        message[strcspn(message, "\n")] = '\0';
        write(sockfd, message, strlen(message));

        printf("%s Sending: %s\n", name, message);

        // if the sent message was bye, terminate the client
        if (strcmp(message, "bye") == 0)
        {
            printf("Chat terminated.\n");
            break;
        }
    }

    close(sockfd);
    exit(EXIT_SUCCESS);
}
