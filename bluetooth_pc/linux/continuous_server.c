#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define QUEUE 5

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Usage: %s <channel_number>\n", *argv);
        return 1;
    }

    int serverfd, clientfd;
    socklen_t clilen;
    char buffer[100];
    struct sockaddr_rc server_addr, client_addr;

    server_addr.rc_family = AF_BLUETOOTH;
    bacpy(&server_addr.rc_bdaddr, BDADDR_ANY);
    server_addr.rc_channel = atoi(argv[1]);

    if((serverfd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
        printf("Cannot create socket\n");
        return 1;
    }

    if(bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Cannot bind to address\n");
        return 1;
    }

    listen(serverfd, QUEUE);

    do {
        clientfd = accept(serverfd, (struct sockaddr *)&client_addr, &clilen);
        memset(buffer, 0, sizeof(buffer));
        recv(clientfd, buffer, sizeof(buffer)-1, 0);
        printf("%s\n", buffer);
        send(clientfd, "Received\n", 9, 0);
        shutdown(clientfd, SHUT_RDWR);
    } while(strcmp(buffer, "halt"));

    return 0;
}
