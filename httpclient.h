

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <curl/curl.h>



class HttpClient
{
    private:
        std::string _url;

    public:

    const std::string HTTP_ERROR = "Http Error: ";

    // constructors
    HttpClient(std::string url);

    // public member functions
    std::string get();

    // public static functions
    static int get_callback(char *contents, size_t size, size_t nmemb, void *userp);
};



#endif
