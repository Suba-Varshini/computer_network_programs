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
    int server_socket, connection, len;
    struct sockaddr_in server_addr, client_addr;
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
    server_addr.sin_port = htons(8083);
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
    char ip_addr[100];
    int n;
    memset(buffer, '\0', 100);
    read(connection, buffer, sizeof(buffer));
    printf("TLD SERVER : %s\n", buffer);
    if (strncmp(buffer, "google.com", 10) == 0)
    {
        strcpy(ip_addr, "216.58.217.206");
    }
    else if (strncmp(buffer, "yahoo.com", 9) == 0)
    {
        strcpy(ip_addr, "192.168.0.1");
    }
    else if (strncmp(buffer, "youtube.com", 11) == 0)
    {
        strcpy(ip_addr, "199.223.232.0");
    }
    else
    {
        strcpy(ip_addr, "127.0.0.1");
    }
    printf("ORIGIN SERVER TO TLD SERVER : %s\n", ip_addr);
    write(connection, ip_addr, sizeof(ip_addr));
    close(server_socket);
    return 0;
}
