#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char* argv[]): m_argc(argc), m_argv(argv){}
PmergeMe::~PmergeMe(){}

// VECTORRRR
std::vector<int> merge(std::vector<int>& left,std::vector<int>& right)
{
	std::vector<int> merged;
	int totalSize = left.size() + right.size();
	PmergeMe::iter leftIt = left.begin();
	PmergeMe::iter rightIt = right.begin();
	for (int i = 0; i < totalSize; ++i)
	{
		if (leftIt == left.end())
		{
			for (; rightIt != right.end(); ++rightIt)
			{
				merged.push_back(*rightIt);
			}
			return merged;
		}
		else if (rightIt == right.end())
		{
			for (; leftIt != left.end(); ++leftIt)
			{
				merged.push_back(*leftIt);
			}
			return merged;
		}
		else if (*leftIt < *rightIt)
		{
			merged.push_back(*leftIt);
			++leftIt;
			continue;
		}
		else if (*leftIt > *rightIt)
		{
			merged.push_back(*rightIt);
			++rightIt;
			continue;
		}
	}
	return merged;
}

void mergeSort(std::vector<int>& winnerSubset)
{
	int mid = winnerSubset.size() / 2;
	if (mid > 0)
	{
		std::vector<int> left(winnerSubset.begin(), winnerSubset.begin() + mid);
		std::vector<int> right(winnerSubset.begin() + mid, winnerSubset.end());

		mergeSort(left);
		mergeSort(right);
		winnerSubset = merge(left, right);
	}
}



void fillVectors(std::vector<int>& winnerSubset, std::vector<int>& loserSubset, std::vector<int>& vetorInicial)
{
	int	mid = vetorInicial.size() / 2;
	if (mid & 1 && mid > 1)
	{
		if (vetorInicial[mid] < vetorInicial[mid-1])
		{
			loserSubset.push_back(vetorInicial[mid]);
			winnerSubset.push_back(vetorInicial[mid-1]);
			
			vetorInicial.erase(vetorInicial.begin()+ mid);
			vetorInicial.erase(vetorInicial.begin()+ mid - 1);
		}
		else
		{
			loserSubset.push_back(vetorInicial[mid-1]);
			winnerSubset.push_back(vetorInicial[mid]);
			
			vetorInicial.erase(vetorInicial.begin()+ mid);
			vetorInicial.erase(vetorInicial.begin()+ mid - 1);
		}
		--mid;
		std::vector<int> left(vetorInicial.begin(), vetorInicial.begin() + mid);
		std::vector<int> right(vetorInicial.begin() + mid, vetorInicial.end());

		fillVectors(winnerSubset, loserSubset, left);
		fillVectors(winnerSubset, loserSubset, right);

	}
	else if (mid > 1)
	{
		std::vector<int> left(vetorInicial.begin(), vetorInicial.begin() + mid);
		std::vector<int> right(vetorInicial.begin() + mid, vetorInicial.end());

		fillVectors(winnerSubset, loserSubset, left);
		fillVectors(winnerSubset, loserSubset, right);
	}
	else if (mid == 1)
	{
		if (vetorInicial[mid] < vetorInicial[mid-1])
		{
			loserSubset.push_back(vetorInicial[mid]);
			winnerSubset.push_back(vetorInicial[mid-1]);
			
			vetorInicial.erase(vetorInicial.begin()+ mid);
			vetorInicial.erase(vetorInicial.begin()+ mid -1);
		}
		else
		{
			loserSubset.push_back(vetorInicial[mid-1]);
			winnerSubset.push_back(vetorInicial[mid]);
			
			vetorInicial.erase(vetorInicial.begin()+ mid);
			vetorInicial.erase(vetorInicial.begin()+ mid -1);
		}
	}
	
}
std::vector<int> generateJacobsthalIndexes(int n)
{
    std::vector<int> order;
    std::vector<bool> used(n, false);

    int j0 = 0, j1 = 1;
    int j = j1;

    while (j < n)
	{
        if (!used[j])
		{
            order.push_back(j);
            used[j] = true;
        }
        int next = j1 + 2 * j0;
        j0 = j1;
        j1 = next;
        j = next;
    }

    for (int i = 0; i < n; ++i)
	{
        if (!used[i])
            order.push_back(i);
    }

    return order;
}

void findInsertion(std::vector<int>& winnerSubset, int number, int low, int high)
{
	int mid = (low + high)/2;
	if (high - low > 1)
	{
		if (number > winnerSubset[mid])
		{
			if (number < winnerSubset[mid + 1])
				winnerSubset.insert(winnerSubset.begin() + mid + 1, number);
			else if (number > winnerSubset[mid + 1] && high - mid == 1)
				winnerSubset.insert(winnerSubset.begin() + high + 1, number);
			if (high - mid > 1)
				findInsertion(winnerSubset, number, mid, high);
		}
		if (number < winnerSubset[mid])
		{
			if (number > winnerSubset[mid - 1])
				winnerSubset.insert(winnerSubset.begin() + mid, number);
			else if (number < winnerSubset[mid - 1] && mid - low == 1)
				winnerSubset.insert(winnerSubset.begin() + low, number);
			if (mid - low > 1)
				findInsertion(winnerSubset, number, low, mid);
		}
	}
	else if (winnerSubset.size() == 2)
	{
		if (number > winnerSubset[0] && number > winnerSubset[1])
			winnerSubset.insert(winnerSubset.end(), number);
		else if (number > winnerSubset[0] && number < winnerSubset[1])
			winnerSubset.insert(winnerSubset.begin() + 1, number);
		else if (number < winnerSubset[0] && number < winnerSubset[1])
			winnerSubset.insert(winnerSubset.begin(), number);	
	}
	else
	{
		if (number > winnerSubset[0])
			winnerSubset.insert(winnerSubset.begin() + 1, number);
		else
			winnerSubset.insert(winnerSubset.begin(), number);
	}
}

void binaryInsertion(std::vector<int>& winnerSubset, std::vector<int>& loserSubset)
{
	std::vector<int> indexes = generateJacobsthalIndexes(loserSubset.size());
	for (size_t i = 0; i < indexes.size(); ++i)
	{
		int number = loserSubset[indexes[i]];
		findInsertion(winnerSubset, number, 0, winnerSubset.size()-1);
	}
}

void fillVector(std::vector<int>& vetorInicial, int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		int number;
		if (!(iss >> number) || !(iss.eof()))
		{
			std::cerr << "Invalid number(s) found on argument: " << argv[i] << '\n';
			exit(EXIT_FAILURE);
		}
		if (number < 0)
		{
			std::cerr << "Invalid number(s) found on argument: " << argv[i] << '\n';
			exit(EXIT_FAILURE);
		}
		vetorInicial.push_back(number);
	}
}


std::vector<int>  PmergeMe::sortVector()
{
/* 	std::vector<int> input;
    fillVector(input, m_argc, m_argv);

    // 2) Print “Before: …”
    std::cout << "Before: ";
    for (size_t i = 0; i < input.size(); ++i) {
        std::cout << input[i] << ' ';
    }
    std::cout << '\n';

	if (input.size() <= 1)
    {
        // N == 0 or 1: “sorted” is exactly the same
        std::cout << "After:  ";
        if (input.size() == 1) std::cout << input[0] << ' ';
        std::cout << '\n';
        std::cout
          << "Time to process a range of "
          << input.size()
          << " elements with std::vector : 0 us\n";
        return;
    }
    // 3) Extract odd leftover, do Ford–Johnson…
    bool isEven = (input.size() % 2 == 0);
    int leftover = 0;
    if (!isEven) {
        leftover = input.back();
        input.pop_back();
    }
    std::vector<int> winners, losers;
    fillVectors(winners, losers, input);

    // 4) Time the sort+insert
    clock_t t0 = clock();
    mergeSort(winners);


    binaryInsertion(winners, losers);

	std::cout << '\n';



    if (!isEven)
        findInsertion(winners, leftover, 0, winners.size() - 1);
    clock_t t1 = clock();

    // 5) Print “After: …”
    std::cout << "After:  ";
    for (size_t i = 0; i < winners.size(); ++i) {
        std::cout << winners[i] << ' ';
    }
    std::cout << '\n';

    // 6) Print timing in μs
    double us = double(t1 - t0) / CLOCKS_PER_SEC * 1e6;
    std::cout
      << "Time to process a range of " << winners.size()
      << " elements with std::vector : "
      << us << " us\n";
 */





	  std::vector<int> input;
	  fillVector(input, m_argc, m_argv);
  
	  if (input.size() <= 1)
		  return input;
  
	  bool isEven = (input.size() % 2 == 0);
	  int leftover = 0;
	  if (!isEven) {
		  leftover = input.back();
		  input.pop_back();
	  }
  
	  std::vector<int> winners, losers;
	  fillVectors(winners, losers, input);
  
	  mergeSort(winners);
	  binaryInsertion(winners, losers);
	  if (!isEven)
		  findInsertion(winners, leftover, 0, winners.size() - 1);
  
	  return winners;
}


///---------------------DEQUE----------------------////////////////////////////////

void fillDeques(std::deque<int>& winnerSubset, std::deque<int>& loserSubset, std::deque<int>& dequeInicial)
{
	int	mid = dequeInicial.size() / 2;
	if (mid & 1 && mid > 1)
	{
		if (dequeInicial[mid] < dequeInicial[mid-1])
		{
			loserSubset.push_back(dequeInicial[mid]);
			winnerSubset.push_back(dequeInicial[mid-1]);
			
			dequeInicial.erase(dequeInicial.begin()+ mid);
			dequeInicial.erase(dequeInicial.begin()+ mid - 1);
		}
		else
		{
			loserSubset.push_back(dequeInicial[mid-1]);
			winnerSubset.push_back(dequeInicial[mid]);
			
			dequeInicial.erase(dequeInicial.begin()+ mid);
			dequeInicial.erase(dequeInicial.begin()+ mid - 1);
		}
		--mid;
		std::deque<int> left(dequeInicial.begin(), dequeInicial.begin() + mid);
		std::deque<int> right(dequeInicial.begin() + mid, dequeInicial.end());

		fillDeques(winnerSubset, loserSubset, left);
		fillDeques(winnerSubset, loserSubset, right);

	}
	else if (mid > 1)
	{
		std::deque<int> left(dequeInicial.begin(), dequeInicial.begin() + mid);
		std::deque<int> right(dequeInicial.begin() + mid, dequeInicial.end());

		fillDeques(winnerSubset, loserSubset, left);
		fillDeques(winnerSubset, loserSubset, right);
	}
	else if (mid == 1)
	{
		if (dequeInicial[mid] < dequeInicial[mid-1])
		{
			loserSubset.push_back(dequeInicial[mid]);
			winnerSubset.push_back(dequeInicial[mid-1]);
			
			dequeInicial.erase(dequeInicial.begin()+ mid);
			dequeInicial.erase(dequeInicial.begin()+ mid -1);
		}
		else
		{
			loserSubset.push_back(dequeInicial[mid-1]);
			winnerSubset.push_back(dequeInicial[mid]);
			
			dequeInicial.erase(dequeInicial.begin()+ mid);
			dequeInicial.erase(dequeInicial.begin()+ mid -1);
		}
	}
}


void fillDeque(std::deque<int>& dequeInicial, int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		int number;
		if (!(iss >> number) || !(iss.eof()))
		{
			std::cerr << "Invalid number(s) found on argument: " << argv[i] << '\n';
			exit(EXIT_FAILURE);
		}
		if (number < 0)
		{
			std::cerr << "Invalid number(s) found on argument: " << argv[i] << '\n';
			exit(EXIT_FAILURE);
		}
		dequeInicial.push_back(number);
	}
}
std::deque<int> mergeDeque(std::deque<int>& left,std::deque<int>& right)
{
	std::deque<int> merged;
	int totalSize = left.size() + right.size();
	PmergeMe::iterDeque leftIt = left.begin();
	PmergeMe::iterDeque rightIt = right.begin();
	for (int i = 0; i < totalSize; ++i)
	{
		if (leftIt == left.end())
		{
			for (; rightIt != right.end(); ++rightIt)
			{
				merged.push_back(*rightIt);
			}
			return merged;
		}
		else if (rightIt == right.end())
		{
			for (; leftIt != left.end(); ++leftIt)
			{
				merged.push_back(*leftIt);
			}
			return merged;
		}
		else if (*leftIt < *rightIt)
		{
			merged.push_back(*leftIt);
			++leftIt;
			continue;
		}
		else if (*leftIt > *rightIt)
		{
			merged.push_back(*rightIt);
			++rightIt;
			continue;
		}
	}
	return merged;
}

void mergeSortDeque(std::deque<int>& winnerSubset)
{
	int mid = winnerSubset.size() / 2;
	if (mid > 0)
	{
		std::deque<int> left(winnerSubset.begin(), winnerSubset.begin() + mid);
		std::deque<int> right(winnerSubset.begin() + mid, winnerSubset.end());

		mergeSortDeque(left);
		mergeSortDeque(right);
		winnerSubset = mergeDeque(left, right);
	}
}

std::deque<int> generateJacobsthalIndexesDeque(int n)
{
    std::deque<int> order;
    std::vector<bool> used(n, false);

    int j0 = 0, j1 = 1;
    int j = j1;

    while (j < n)
	{
        if (!used[j])
		{
            order.push_back(j);
            used[j] = true;
        }
        int next = j1 + 2 * j0;
        j0 = j1;
        j1 = next;
        j = next;
    }

    for (int i = 0; i < n; ++i)
	{
        if (!used[i])
            order.push_back(i);
    }

    return order;
}

void findInsertionDeque(std::deque<int>& winnerSubset, int number, int low, int high)
{
	int mid = (low + high)/2;
	if (high - low > 1)
	{
		if (number > winnerSubset[mid])
		{
			if (number < winnerSubset[mid + 1])
				winnerSubset.insert(winnerSubset.begin() + mid + 1, number);
			else if (number > winnerSubset[mid + 1] && high - mid == 1)
				winnerSubset.insert(winnerSubset.begin() + high + 1, number);
			if (high - mid > 1)
				findInsertionDeque(winnerSubset, number, mid, high);
		}
		if (number < winnerSubset[mid])
		{
			if (number > winnerSubset[mid - 1])
				winnerSubset.insert(winnerSubset.begin() + mid, number);
			else if (number < winnerSubset[mid - 1] && mid - low == 1)
				winnerSubset.insert(winnerSubset.begin() + low, number);
			if (mid - low > 1)
				findInsertionDeque(winnerSubset, number, low, mid);
		}
	}
	else
	{
		if (number > winnerSubset[0])
			winnerSubset.insert(winnerSubset.begin() + 1, number);
		else
			winnerSubset.insert(winnerSubset.begin(), number);
	}
}

void binaryInsertionDeque(std::deque<int>& winnerSubset, std::deque<int>& loserSubset)
{
	std::deque<int> indexes = generateJacobsthalIndexesDeque(loserSubset.size());
	for (size_t i = 0; i < indexes.size(); ++i)
	{
		int number = loserSubset[indexes[i]];
		findInsertionDeque(winnerSubset, number, 0, winnerSubset.size()-1);
	}
}

std::deque<int> PmergeMe::sortDeque()
{
/* 	std::deque<int> input;
    fillDeque(input, m_argc, m_argv);

	if (input.size() <= 1)
    {
        std::cout
          << "Time to process a range of "
          << input.size()
          << " elements with std::deque : 0 us\n";
        return;
    }
    // 3) Extract odd leftover, do Ford–Johnson…
    bool isEven = (input.size() % 2 == 0);
    int leftover = 0;
    if (!isEven) {
        leftover = input.back();
        input.pop_back();
    }
    std::deque<int> winners, losers;
    fillDeques(winners, losers, input);

	for (iterDeque it = winners.begin(); it != winners.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
	for (iterDeque it = losers.begin(); it != losers.end(); ++it)
	{
		std::cout << *it << " ";
	} 
    // 4) Time the sort+insert
    clock_t t0 = clock();
    mergeSortDeque(winners);
    binaryInsertionDeque(winners, losers);
    if (!isEven)
        findInsertionDeque(winners, leftover, 0, winners.size() - 1);
    clock_t t1 = clock();


    double us = double(t1 - t0) / CLOCKS_PER_SEC * 1e6;
    std::cout
      << "Time to process a range of " << winners.size()
      << " elements with std::deque  : "
      << us << " us\n";



 */

	  std::deque<int> input;
	  fillDeque(input, m_argc, m_argv);
  
	  if (input.size() <= 1)
		  return input;
  
	  bool isEven = (input.size() % 2 == 0);
	  int leftover = 0;
	  if (!isEven) {
		  leftover = input.back();
		  input.pop_back();
	  }
  
	  std::deque<int> winners, losers;
	  fillDeques(winners, losers, input);
  
	  mergeSortDeque(winners);
	  binaryInsertionDeque(winners, losers);
	  if (!isEven)
		  findInsertionDeque(winners, leftover, 0, winners.size() - 1);
  
	  return winners;
}