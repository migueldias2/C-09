#include "PmergeMe.hpp"
#include <algorithm>

bool hasDuplicates(std::vector<int>& vec)
{
	int max = *max_element(vec.begin(), vec.end());
	std::vector<bool> mapa(max + 1, false);

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (mapa[vec[i]])
			return true;
		mapa[vec[i]] = true;
	}
	return false;
}


int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Invalid argument size.\n";
		return 1;
	}
	std::vector<int> vec;
	for (int i = 1; i < argc; ++i)
	{
		
		std::istringstream iss(argv[i]);
		int number;
		if (!(iss >> number) || !(iss.eof()))
		{
			std::cerr << "Error" << '\n';
			return 1;
		}
		if (number < 0)
		{
			std::cerr << "Error" << '\n';
			return 1;
		}
		vec.push_back(number);
	}

	if (hasDuplicates(vec))
	{
		std::cerr << "Error" << '\n';
		return 1;
	}

    std::cout << "Before: ";
	if (argc < 16)
	{
		for (int i = 1; i < argc; ++i) {
			std::cout << argv[i] << " ";
		}
	}
	else
	{
		for (int i = 1; i < 5; ++i) {
			std::cout << argv[i] << " ";
		}
		std::cout << "[...]";
	}
    std::cout << std::endl;


    PmergeMe sorter(argc, argv);

    clock_t v0 = clock();
    std::vector<int> vecSorted = sorter.sortVector();
    clock_t v1 = clock();

    clock_t d0 = clock();
    std::deque<int> deqSorted = sorter.sortDeque();
    clock_t d1 = clock();

    std::cout << "After:  ";
	if (vecSorted.size() < 15)
	{
		for (size_t i = 0; i < vecSorted.size(); ++i)
        	std::cout << vecSorted[i] << " ";
	}
	else
	{
		for (size_t i = 0; i < 4; ++i)
        	std::cout << deqSorted[i] << " ";
		std::cout << "[...]";

	}
    
    std::cout << std::endl;

    // Print timings
    double vector_us = double(v1 - v0) / CLOCKS_PER_SEC * 1e6;
    double deque_us = double(d1 - d0) / CLOCKS_PER_SEC * 1e6;

    std::cout << "Time to process a range of " << vecSorted.size()
              << " elements with std::vector : " << vector_us << " us" << std::endl;
    std::cout << "Time to process a range of " << deqSorted.size()
              << " elements with std::deque  : " << deque_us << " us" << std::endl;

    return 0;

}