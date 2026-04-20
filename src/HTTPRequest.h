#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
using namespace std;

#include <string>

class HTTPRequest {
private:
    string method;
    string uri;
    string version;

public:
    HTTPRequest(const string& raw_request);

    string getMethod()  const { return method;  }
    string getURI()     const { return uri;     }
    string getVersion() const { return version; }
};

#endif