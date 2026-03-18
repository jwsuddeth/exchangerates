// pull the current exchange rate from an API
// it comes back with EUR as the base rate.
// Request USD and whatever currency you want to convert to.
// Divide that currency by the USD to get the rate from USD to that currency.
// This tells you how many dollars of that currency one USD will buy you. 
// If you are in mexico and the price says 800 MXN and you want to know how many USD you are spending
// you can run this program.
// convert 800 MXN USD
//
// to build:   g++ exchrate.cpp httpclient.cpp -ljsoncpp  -lcurl -std=c++11 -o rates


// defect: seems to be a rounding error. My calculation doens't match google. It's only off by small change though.

#include <iostream>
#include <string>
#include <algorithm>
#include <json/json.h>

#include "httpclient.h"

using namespace std;

// output looks like:
// {"success":true,"timestamp":1773846668,"base":"EUR","date":"2026-03-18","rates":{"USD":1.152405,"MXN":20.346839}}


void parse(string json, string toCurrency, string fromCurrency, double fromPrice)
{
	Json::Value root;
	JSONCPP_STRING error;

	Json::CharReaderBuilder builder;

	const auto jsonLength = static_cast<int>(json.length());

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

	if (!reader->parse(json.c_str(), json.c_str() + jsonLength, &root, &error))
	{
		cout << "error parsing JSON: " << error << endl;
		return;
	}

	Json::Value rates = root["rates"];


	const double toDollars = rates[toCurrency].asDouble();
	const double fromDollars = rates[fromCurrency].asDouble();

	cout << toCurrency << "/" << fromCurrency << endl << toDollars << "\t" << fromDollars << endl;

	// calc rate per USD
	double rt = fromDollars / toDollars;

	cout << "1 " << toCurrency << " is equal to " << rt << " " << fromCurrency << endl;

	if (fromPrice > 0)
	{
		double toPrice = fromPrice / rt;
		cout << "The price for " << fromPrice << " " << fromCurrency << " in " << toCurrency << " is " << toPrice << endl;
	}
}


int main(int argc, char **argv)
{


	if (argc < 3)
	{
		cout << "Usage: rates toCurrency fromCurrency fromPrice" << endl
			<< "Example: rates usd mxn 400.00" << endl;
		return 0;
	}

	double fromPrice = -1.0;
	string toCurrency = string(argv[1]);
	string fromCurrency = string(argv[2]);

	if (argc > 3)
	{
		fromPrice = ::atof(argv[3]);
	}

	transform(toCurrency.begin(), toCurrency.end(), toCurrency.begin(), ::tolower);
	transform(fromCurrency.begin(), fromCurrency.end(), fromCurrency.begin(), ::tolower);

	string url ="http://api.exchangeratesapi.io/v1/latest?access_key=e946e8d572e1312f4f0c8543a3781a72&symbols=" + toCurrency + "," + fromCurrency;

	HttpClient client(url);


	string response = client.get();
	if (response == client.HTTP_ERROR)
	{
		cout << response << endl;
	}
	else 
	{
		transform(toCurrency.begin(), toCurrency.end(), toCurrency.begin(), ::toupper);
		transform(fromCurrency.begin(), fromCurrency.end(), fromCurrency.begin(), ::toupper);

		parse(response, toCurrency, fromCurrency, fromPrice);
	}


	return 0;
}
