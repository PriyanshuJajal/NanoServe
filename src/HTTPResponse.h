#ifndef HTTPResponse.h
#define HTTPRESPONSE_H

#include <string>
using namespace std;

class HTTPResponse {
private:
    string determineContentType(const string& filePath);

public:
    // Takes the URI (e.g. "/about.html") and returns the full formatted HTTP response
    string buildResponse(const string& uri);
};

#endif