#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib> //strtof strtod
#include <climits>
#include <algorithm>

class BitcoinExchange
{
private:
	BitcoinExchange(const BitcoinExchange&);
	BitcoinExchange& operator=(const BitcoinExchange&);
public:
	std::map<std::string, float> btcValue;

	BitcoinExchange();
	~BitcoinExchange();

	void createMapExchange(const char*);
	void printBtcValue(char*);
};

#endif