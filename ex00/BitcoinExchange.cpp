#include "BitcoinExchange.hpp"

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange&) {return *this;}
BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::createMapExchange(const char* csv)
{

	std::ifstream file(csv);
	if (!file)
	{
		std::cerr << "Error reading file\n";
		std::exit(EXIT_FAILURE);
	}
	
	std::string string;
	while (getline(file, string))
	{
		if (string.substr(0, 4) == "date")
			continue;
		char* end;
		btcValue[string.substr(0, 10)] = strtof(string.substr(11).c_str(), &end);
	}
	file.close();
	if (btcValue.empty())
	{
		std::cerr << "Empty input file." << std::endl;
		std::exit(EXIT_SUCCESS);
	}
}

void printBtcUsd(float value, std::string& date, std::map<std::string, float>& btcValue);

bool isEmptyFile(std::ifstream& file)
{
	if (file.peek() == std::ifstream::traits_type::eof())
	{	
		std::cerr << "Empty input file." << '\n';
		return true;
	}
	return false;
}
bool isValidDate(std::string& date)
{
	for (int i = 0; i < 4; ++i)
	{
		if (!isdigit(date[i]))
		{
			std::cerr << "Error: bad input => " << date << '\n';
			return false;
		}
	}
	return true;
}

bool isValidFormat(std::string& date, std::string string)
{
	if (date[4] != '-' || date[7] != '-' || string[10] != ' ')
	{
		std::cerr << "Error: bad input => " << date << '\n';
		return false;
	}
	int month = std::atoi(date.substr(5, 2).c_str());
	if (month > 12)
	{
		std::cerr << "Error: bad input => " << date << '\n';
		return false;
	}
	int day = std::atoi(date.substr(8, 2).c_str());
	if (day > 31)
	{
		std::cerr << "Error: bad input => " << date << '\n';
		return false;
	}
	if (string[12] != ' ')
	{
		std::cerr << "Error: bad value format => " << string.substr(11) << '\n';
		return false;
	}
	return true;
}

bool invalidValue(float value)
{
	if (value < 0)
	{
		std::cerr << "Error: not a positive number.\n";
		return false;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number.\n";
		return false;
	}
	return true;
}

void BitcoinExchange::printBtcValue(char* input)
{
	std::ifstream file(input);
	if (!file)
	{
		std::cout << "Error reading file.\n";
		std::exit(EXIT_FAILURE);
	}
	if (isEmptyFile(file))
		std::exit(EXIT_FAILURE);

	std::string string;
	while (getline(file, string))
	{
		if (string.substr(0, 4) == "date") //isHeaderLine
			continue;

		std::string date = string.substr(0, 11);
		if (!isValidDate(date))
			continue;
		
		if (!isValidFormat(date, string))
			continue;

		char* end;
		float value = strtof(string.substr(12).c_str(), &end);
		if (!invalidValue(value))
			continue;

		printBtcUsd(value, date, btcValue);
	}
	file.close();
}

void printBtcUsd(float value, std::string& date, std::map<std::string, float>& btcValue)
{
	typedef std::map<std::string, float>::iterator iter;

	iter found = btcValue.find(date);
	if (found == btcValue.end())
	{
		found = (btcValue.lower_bound(date));
		--found;
	}
	std::cout << date << " => " << value << " = " << value * found->second << '\n';
}