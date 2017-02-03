#include <winsock2.h>
#include <ws2bth.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(int argc, char** argv) {
    const int CHANNEL = 4;
    const int QUEUE = 2;

    WSADATA wsaData;
    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if(iResult != 0) {
        cout << "WSAStartup failed: ";
        cout << iResult;
        cout << "\r\n";
        return 1;
    }

    char buffer[100];
    SOCKADDR_BTH server_addr;
    SOCKET server = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM),
           client;

    if(server == INVALID_SOCKET) {
        cout << "Failed to create server socket\r\n";
        cout << "Error code: ";
        cout << WSAGetLastError();
        cout << "\n";
        return 1;
    }

    server_addr.addressFamily = AF_BTH;
    server_addr.btAddr = 0;
    //server_addr.serviceClassId = GUID_NULL;
    server_addr.port = CHANNEL;

    if(bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        cout << "Could not bind to socket\r\n";
        cout << "Error code: ";
        cout << WSAGetLastError();
        cout << "\r\n";
        return 1;
    }

    listen(server, QUEUE);

    cout << "Listening\r\n";

    do {
        client = accept(server, NULL, NULL);
        memset(buffer, 0, sizeof(buffer));
        recv(client, buffer, sizeof(buffer)-1, 0);
        cout << buffer;
        cout << "\n";
        send(client, "Received\n", 9, 0);
        closesocket(client);
    } while(strcmp(buffer, "halt"));

    WSACleanup();

    return 0;
}
