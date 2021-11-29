#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(void)
{
    int client_scoket, connection;
    struct sockaddr_in client_addr;
    client_scoket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_scoket == -1)
    {
        printf("Socket not created.\n");
    }
    else
    {
        printf("Socket Created Successfully.\n");
    }
    memset(&client_addr, '\0', sizeof(client_addr));

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(8081);

    if (connect(client_scoket, (struct sockaddr *)&client_addr, sizeof(client_addr)) != 0)
    {
        printf("Connection failed with server. \n");
    }
    else
    {
        printf("Connected Successfully to the Server.\n");
    }
    char buffer[100];
    int n;
    memset(buffer, '\0', 100);
    printf("CLIENT : ");
    n = 0;
    while (1)
    {
        buffer[n] = getchar();
        if (buffer[n] == '\n')
        {
            break;
        }
        n++;
    }
    printf("\n");
    write(client_scoket, buffer, sizeof(buffer));
    memset(buffer, '\0', sizeof(buffer));
    read(client_scoket, buffer, sizeof(buffer));
    printf("SERVER : %s\n", buffer);
    close(client_scoket);
    return 0;
}
