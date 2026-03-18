
#include "httpclient.h"



HttpClient::HttpClient(std::string url)
{
    _url = url;
}


std::string HttpClient::get()
{
    std::string readBuffer;
    
    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
            readBuffer = HttpClient::HTTP_ERROR;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return readBuffer;
}


int HttpClient::get_callback(char *contents, size_t size, size_t nmemb, void *userp)
{        
    char * pdata = (char *)contents;
    std::string * pStr = (std::string *)userp;
    int sz = size * nmemb;
    pStr->append(pdata, sz);
    return sz;
}
