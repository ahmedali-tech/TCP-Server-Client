#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 4927
#define IP_ADDRESS "127.0.0.1"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{

    int cli_sock;
    struct sockaddr_in addr;

    cli_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_sock < 0)
    {
        perror("Problem in Socket creation.\n");
        return -1;
    }
    printf("Socket created Successfully.\n");

    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    int connection = connect(cli_sock, (struct sockaddr *)&addr, sizeof(addr));
    if (connection < 0)
    {
        perror("Problem in server connection.\n");
        return -1;
    }
    printf("Connected to the server\n");

    FILE *fp;
    int recieved;
    char buffer[2048];
    fp = fopen("recv.wav", "wb");
    if (fp == NULL)
    {
        perror("Error while creating the file. \n");
    }
    while (1)
    {
        recieved = recv(cli_sock, buffer, sizeof(buffer), 0);
        if (recv <= 0)
        {
            break;
        }
        fwrite(buffer, 2048, 1, fp);
        bzero(buffer, 2048);
    }
    printf("The file has been received successfully.\n");

    close(cli_sock);
    return 0;
}