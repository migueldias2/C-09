#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file.\n";
		return 1;
	}
	BitcoinExchange btc;
	btc.createMapExchange("data.csv");
	btc.printBtcValue(argv[1]);
}