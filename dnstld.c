#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

int main(void)
{

    int server_socket, connection, len, origin_socket;
    struct sockaddr_in server_addr, client_addr, origin_addr;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Socket not created.\n");
    }
    else
    {
        printf("Socket Created Successfully.\n");
    }
    memset(&server_addr, '\0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8082);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
    {
        printf("Scoket Binding Falied\n");
    }
    else
    {
        printf("Socket Binded Successfully.\n");
    }

    if (listen(server_socket, 5) != 0)
    {
        printf("Listen failed.\n");
    }
    else
    {
        printf("Server Listening.\n");
    }
    len = sizeof(client_addr);
    connection = accept(server_socket, (struct sockaddr *)&client_addr, &len);
    if (connection < 0)
    {
        printf("Server accept failed.\n");
    }
    else
    {
        printf("Server Accepted the Client.\n");
    }

    char buffer[100];
    int n;
    memset(buffer, '\0', 100);
    read(connection, buffer, sizeof(buffer));
    printf("ROOT SERVER : %s\n", buffer);

    origin_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (origin_socket == -1)
    {
        printf("origin Socket not created.\n");
    }
    else
    {
        printf("origin Socket Created Successfully.\n");
    }

    memset(&origin_addr, '\0', sizeof(origin_addr));

    origin_addr.sin_family = AF_INET;
    origin_addr.sin_port = htons(8083);
    origin_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(origin_socket, (struct sockaddr *)&origin_addr, sizeof(origin_addr)) != 0)
    {
        printf("Connection failed with origin server. \n");
    }
    else
    {
        printf("Connected Successfully to the origin Server.\n");
    }
    printf("\nTLD SERVER TO ORIGIN SERVER : %s\n", buffer);
    write(origin_socket, buffer, sizeof(buffer));
    memset(buffer, '\0', sizeof(buffer));
    read(origin_socket, buffer, sizeof(buffer));
    printf("ORIGIN SERVER : %s\n\n", buffer);
    printf("TLD SERVER TO ROOT SERVER : %s\n", buffer);
    printf("\n");
    write(connection, buffer, sizeof(buffer));
    close(origin_socket);
    close(server_socket);
    return 0;
}