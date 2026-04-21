#include "HTTPResponse.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Helper function to tell the browser what kind of file we are sending
string HTTPResponse::determineContentType(const string& filePath) {
    if (filePath.find(".css") != string::npos) {
        return "text/css";
    }

    if (filePath.find(".json") != string::npos) {
        return "application/json";
    }

    if (filePath.find(".png") != string::npos) {
        return "image/png";
    }

    return "text/html";
}

string HTTPResponse::buildResponse(const string& method , const string& uri , const string& request_body) {

    // 1. HANDLE POST REQUESTS
    if (method == "POST" && uri == "/api/data") {
        cout << "[INFO] Intercepted POST Request. Payload: \n" << request_body << "\n";
        string json_response = "{\"status\": \"success\", \"message\": \"JSON received by C++ server!\"}";

        string status_line = "HTTP/1.1 200 OK\r\n";
        string content_type = "Content-Type: application/json\r\n";
        string content_length = "Content-Length: " + to_string(json_response.size()) + "\r\n";

        return status_line + content_type + content_length + "\r\n" + json_response;
    }

    // 2. HANDLE GET REQUESTS (File Routing Logic) 
    string filePath = "public" + uri;

    // If user just type localhost:8080/, default to index.html
    if (uri == "/") {
        filePath = "public/index.html";
    }

    // Opens in binary mode so that images & non-text files are handled correctly
    ifstream file(filePath , ios::in | ios::binary);
    string body;
    string status_line;

    if (file.is_open()) {
        // File exists! Read the entire thing into our 'body' string
        ostringstream file_contents;
        file_contents << file.rdbuf();

        body = file_contents.str();

        status_line = "HTTP/1.1 200 OK\r\n";

        file.close();
    }
    else {
        status_line = "HTTP/1.1 404 Not Found\r\n";

        // Try to load a custom 404 file if it exists
        ifstream error_file("public/404.html");

        if (error_file.is_open()) {
            ostringstream error_contents;
            error_contents << error_file.rdbuf();

            body = error_contents.str();

            error_file.close();
        }
        else {
            body = "<html><body><h1>404 - File Not Found</h1></body></html>";
        }
    }

    string content_type = "Content-Type: " + determineContentType(filePath) + "; charset=utf-8\r\n";
    string connection = "Connection: close\r\n";
    string content_length = "Content-Length: " + to_string(body.size()) + "\r\n";
    
    return status_line + content_type + connection + content_length + "\r\n" + body;
}