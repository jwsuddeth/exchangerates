# exchangerates
Get exchange rates for 2 currencies and convert a price if needed


To build this you need libcurl and jsoncpp.

g++ exchrate.cpp httpclient.cpp -lcurl -ljsoncpp -o rate

you'll also need to get an API Key from exchangeratesapi.io. The free plan will get you 100 requests per month.

 
