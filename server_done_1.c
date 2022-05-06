#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define PORT 4927
#define IP_ADDRESS "127.0.0.1"

int main()
{

    int ser_socket;
    struct sockaddr_in ser_address;

    ser_address.sin_family = AF_INET;
    ser_address.sin_port = htons(PORT);
    ser_address.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    ser_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (ser_socket < 0)
    {
        perror("Server Socket not created !\n");
        return -1;
    }
    printf("Server socket created Successfully ! \n");
    int bind_socket = bind(ser_socket, (struct sockaddr *)&ser_address, sizeof(ser_address));
    if (bind_socket < 0)
    {
        perror("Socket binding failed ! \n");
        return -1;
    }
    printf("Binding Successful ! \n");
    int sock_listener = listen(ser_socket, 10);
    if (sock_listener < 0)
    {
        perror("Error while listening.\n");
        return -1;
    }
    printf("Waiting for connection........\n");

    // char nameBuffer[100];
    // char *pBuffer = nameBuffer;
    // int receiving; // this represents the return call of the recv function.

    int sock_reciever;
    struct sockaddr_in reciever_address;
    socklen_t recvAddrlen = sizeof(reciever_address);

    sock_reciever = accept(ser_socket, (struct sockaddr *)&reciever_address, &recvAddrlen);

    FILE *fp;
    fp = fopen("send.wav", "r");
    if (fp == NULL)
    {
        perror("File not found ! \n");
        return -1;
    }
    printf("File opened\n");

    char buffer[2048] = {0};
    while (fread(buffer, 2048, 1, fp))
    {

        if (send(sock_reciever, buffer, sizeof(buffer), 0) == -1)
        {
            printf("Error sending the data\n");
            return 1;
        }
        bzero(buffer, 2048);
    }
    printf("Sent successfully !\n");

    printf("Closing the Socket. \n");

    close(ser_socket);

    printf("Program Ended. \n");
    return 0;
}