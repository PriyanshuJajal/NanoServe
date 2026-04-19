#include "TCPServer.h"
#include <iostream>
using namespace std;

TCPServer::TCPServer(string ipAddress , int port) 
    : ipAddress(ipAddress) , port(port) , server_socket(INVALID_SOCKET) {

        // Initializing the Winsock library before using any socket functions
        WSADATA wsaData;

        // Request Winsock version 2.2
        if (WSAStartup(MAKEWORD(2 , 2) , &wsaData) != 0) {
            cerr << "[ERROR] WSAStartup failed. Error: " << WSAGetLastError() << "\n";
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

void TCPServer::startServer() {
    // Creating a TCP socket (IPv4, stream-oriented)
    server_socket = socket(AF_INET , SOCK_STREAM , 0);
    if (server_socket == INVALID_SOCKET) {
        cerr << "[ERROR] Cannot create socket. Error: " << WSAGetLastError() << "\n";
        exit(1);
    }

    cout << "[INFO] Socket created successfully.\n";

    // Bind socket to the specified IP and port
    if (bind(server_socket , (struct sockaddr *)& server_address , sizeof(server_address)) == SOCKET_ERROR) {
        cerr << "[ERROR] Cannot bind to port " << port << ". Error: " << WSAGetLastError() << "\n";
        exit(1);
    }

    cout << "[INFO] Bound to port " << port << " successfully.\n";
}

void TCPServer::startListen() {
    // Put socket into listening mode, backlog of 20 connections
    if (listen(server_socket , 20) == SOCKET_ERROR) {
        cerr << "[ERROR] Socket listening failed. Error: " << WSAGetLastError() << "\n";
        exit(1);
    }

    cout << "\n*** Listening on IP: " << ipAddress << " Port: " << port << " ***\n\n";

    SOCKET client_socket;
    struct sockaddr_in client_address;
    int client_address_size = sizeof(client_address); // int instead of socklen_t

    // Buffer to store client request (30 KB)
    char buffer[30720] = {0};

    // Infinite loop to accept multiple client connections
    while(true) {
        // Accept incoming connection
        client_socket = accept(server_socket , (struct sockaddr *)& client_address , &client_address_size);
        if (client_socket == INVALID_SOCKET) {
            cerr << "[ERROR] Server failed to accept incoming connection\n";
            continue;
        }
        
        cout << "[INFO] Connection accepted from client!\n";

        // Receive data from client
        int bytesReceived = recv(client_socket , buffer , 30720 , 0);
        if (bytesReceived < 0) {
            cerr << "[ERROR] Failed to read bytes from client\n";
        }
        else {
            cout << "------ Received Request ------\n" << buffer << "\n------------------------------\n";

            string response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 21\r\n"
                "\r\n"
                "Hello from C++ Server";
            
            // Send response back to client
            send(client_socket , response.c_str() , response.size() , 0);
            cout << "[INFO] Response sent to client\n";
        }

        closesocket(client_socket);
        cout << "[INFO] Client socket closed. Waiting for next connection...\n\n";
    }
}

void TCPServer::closeServer() {
    // Close the main server socket
    closesocket(server_socket);
    std::cout << "[INFO] Server socket closed.\n";
}