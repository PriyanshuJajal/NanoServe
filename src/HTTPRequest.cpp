#include "HTTPRequest.h"
#include <sstream>
using namespace std; 

HTTPRequest::HTTPRequest(const string& raw_request) {
    if (raw_request.empty()) {
        method  = "";            
        uri     = "/";           
        version = "HTTP/1.1";    
        return;
    }

    // Create a string stream from the raw request to parse its components
    istringstream stream(raw_request);
    stream >> method >> uri >> version;  // Extract method, URI, and version

    if (method.empty())  method  = "GET";       
    if (uri.empty())     uri     = "/";         
    if (version.empty()) version = "HTTP/1.1";  
}
