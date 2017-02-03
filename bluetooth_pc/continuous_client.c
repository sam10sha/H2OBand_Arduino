#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Usage: %s <bluetooth address> <channel>\n", *argv);
        return 1;
    }

    int clientfd;
    short shut_down;
    char buffer[100];
    struct sockaddr_rc server_addr;

    server_addr.rc_family = AF_BLUETOOTH;
    str2ba(argv[1], &server_addr.rc_bdaddr);
    server_addr.rc_channel = atoi(argv[2]);

    shut_down = 0;

    do {
        memset(buffer, 0, sizeof(buffer));
        printf(">>> ");
        scanf("%s", buffer);
        if(!strcmp(buffer, "halt"))
            shut_down = 1;
        if((clientfd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
            printf("Cannot create socket\n");
            continue;
        }
        if(connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            printf("Failed to send\n");
            continue;
        }
        send(clientfd, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        recv(clientfd, buffer, sizeof(buffer)-1, 0);
        printf("%s\n", buffer);
        shutdown(clientfd, SHUT_RDWR);
    } while(!shut_down);

    shutdown(clientfd, SHUT_RDWR);

    return 0;
}
