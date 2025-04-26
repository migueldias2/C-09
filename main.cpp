#include <iostream>
#include <vector>
#include <sstream>

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Invalid argument size.\n";
		return 1;
	}
	std::vector<int> vetorInicial;
	
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		int number;
		if (!(iss >> number) || !(iss.eof()))
		{
			std::cerr << "Invalid number(s) found on argument: " << argv[i] << '\n';
			std::exit(EXIT_FAILURE);
		}
		if (number < 0)
		{
			std::cerr << "Invalid number(s) found on argument: " << argv[i] << '\n';
			std::exit(EXIT_FAILURE);
		}
		vetorInicial.push_back(number);
	}
	vetorInicial.erase(vetorInicial.begin());
	vetorInicial.erase(vetorInicial.begin());
	typedef std::vector<int>::iterator iter;
	for (iter it = vetorInicial.begin(); it != vetorInicial.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
	bool vectorIsEven = true;
	if (vetorInicial.size() & 1)
		vectorIsEven = false;
	int iterations = vetorInicial.size() / 2;
	int leftover;
	std::vector<int> winnerSubset;
	std::vector<int> loserSubset;
	for (int i = 0; i < iterations; ++i)
	{ 
		int firstNumber = vetorInicial[0];
		int secondNumber = vetorInicial[1];
		if (firstNumber < secondNumber)
		{
			winnerSubset.push_back(secondNumber);
			loserSubset.push_back(firstNumber);
			vetorInicial.erase(vetorInicial.begin());
			vetorInicial.erase(vetorInicial.begin());
		}
		else
		{
			winnerSubset.push_back(firstNumber);
			loserSubset.push_back(secondNumber);
			vetorInicial.erase(vetorInicial.begin());
			vetorInicial.erase(vetorInicial.begin());
		}
	}
	if (!vectorIsEven)
	{
		leftover = vetorInicial[0];
		vetorInicial.erase(vetorInicial.begin());
	}

	for (int i = 0; i < iterations; ++i)
	{
		
	}

	//printing all vectors
	for (iter it = vetorInicial.begin(); it != vetorInicial.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
	for (iter it = winnerSubset.begin(); it != winnerSubset.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
	for (iter it = loserSubset.begin(); it != loserSubset.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
	if (!vectorIsEven)
		std::cout << leftover << '\n';
	return 0;
}