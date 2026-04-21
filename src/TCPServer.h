#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include <winsock2.h> // The Windows socket library
#include <ws2tcpip.h> // Contains newer functions and structs for IP addresses
using namespace std;

class TCPServer {
private:
    string ipAddress;
    int port;
    SOCKET server_socket;
    struct sockaddr_in server_address;

    void startServer();
    void closeServer();

public:
    TCPServer(string ipAddress , int port);
    ~TCPServer();

    void startListen();
};

#endif