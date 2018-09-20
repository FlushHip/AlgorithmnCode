#include <bits/stdc++.h>

#define HTTP_HEADER                                                   \
    "GET /index.html HTTP/1.1\r\n"                                    \
    "Content-Type: text/tab-separated-values; charset=iso-8859-1\r\n" \
    "Host: webservices.domain.com\r\n"                                \
    "Accept: text/html\r\n"                                           \
    "Accept-Encoding: identity\r\n"                                   \
    "User-Agent: Mozilla/3.0 (compatible; Indy Library)\r\n"          \
    "\r\n"

struct HTTPHeader
{
    std::string method;
    std::string url;
    std::string version;
    std::map<std::string, std::string> headers;
};

HTTPHeader ParseHTTPHeader(const std::string & str)
{
    static const int BUFF_SIZE = 1 << 10;
    HTTPHeader ret;
    std::stringstream sin(str);

    std::string line;

    std::getline(sin, line);
    std::stringstream sub(line);
    sub >> ret.method >> ret.url >> ret.version;

    for ( ; std::getline(sin, line) && !line.empty() && line.back() == '\r'; )
    {
        line.pop_back();
        if (line.empty())
        {
            break;
        }
        auto pos = line.find(":");
        ret.headers[line.substr(0, pos)] = line.substr(pos + 1);
    }

    return ret;
}

int main()
{
    HTTPHeader httpHeader= ParseHTTPHeader(HTTP_HEADER);
    
    std::cout << httpHeader.method << " " << httpHeader.url << " " << httpHeader.version << std::endl;
    for (auto & ele : httpHeader.headers)
    {
        std::cout << ele.first << ":" << ele.second << std::endl;
    }
    return 0;
}
