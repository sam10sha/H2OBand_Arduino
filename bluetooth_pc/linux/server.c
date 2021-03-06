/*
  BlueZ example code to build an rfcomm server.
  This code just creates a socket and accepts
  connections from a remote bluetooth device.

  Programmed by Bastian Ballmann
  http://www.geektown.de

  Compile with gcc -lbluetooth <executable> <source>
*/

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define QUEUE 10

int main(int argc, char** argv)
{
    int sock, client, alen;
    char buffer[100];
    struct sockaddr_rc addr;

    if(argc < 2) {
        printf("%s <channel>\n", argv[0]);
        exit(0);
    }

    if( (sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
        perror("socket");
        exit(1);
    }

    addr.rc_family = AF_BLUETOOTH;
    bacpy(&addr.rc_bdaddr, BDADDR_ANY);
    addr.rc_channel = atoi(argv[1]);
    alen = sizeof(addr);

    if(bind(sock, (struct sockaddr *)&addr, alen) < 0) {
        perror("bind");
        exit(1);
    }

    listen(sock,QUEUE);
    printf("Waiting for connections...\n\n");  

    while(client = accept(sock, (struct sockaddr *)&addr, &alen)) {
        memset(buffer, 0, sizeof(buffer));
        recv(client, buffer, sizeof(buffer)-1, 0);
        printf("%s\n", buffer);
        close(client);
    }

    close(sock);
    return 0;
}

