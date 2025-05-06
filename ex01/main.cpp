#include "RPN.hpp"

bool validArguments(int argc)
{
	if (argc != 2)
	{
		std::cerr << "Wrong argument size\n";
		return false;
	}
	return true;
}

int	main(int argc, char *argv[])
{
	if (!validArguments(argc))
		return 1;
	try
	{
		RPN notation(argv[1]);
		std::cout << notation.getResult() << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	return 0;
}