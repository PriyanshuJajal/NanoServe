#include "TCPServer.h"
#include <iostream>
using namespace std;

TCPServer::TCPServer(string ipAddress , int port) 
    : ipAddress(ipAddress) , port(port) , server_socket(INVALID_SOCKET) {

        // Initializing the Winsock library before using any socket functions
        WSADATA wsaData;

        // Request Winsock version 2.2
        if (WSAStartup(MAKEWORD(2 , 2) , &wsaData) != 0) {
            std::cerr << "[ERROR] WSAStartup failed. Error: " << WSAGetLastError() << "\n";
            exit(1);
        }

        // Configure server address structure
        server_address.sin_family = AF_INET;            // IPv4 protocol
        server_address.sin_port = htons(port);          // Convert port to network byte order
        server_address.sin_addr.s_addr = INADDR_ANY;    // Accept connections on any local IP
        
        // Calling function to create and bind the server socket
        startServer();
}

TCPServer::~TCPServer() {
    closeServer();
    WSACleanup(); // Cleanup Winsock library
}