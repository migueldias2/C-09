#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <ctime>
#include <cstdlib>

class PmergeMe
{
private:
	int m_argc;
	char** m_argv;
	std::vector<int> vec;
	std::deque<int> deq;
	PmergeMe();
	PmergeMe(const PmergeMe&);
	PmergeMe& operator=(const PmergeMe&);
public:
	PmergeMe(int argc, char* argv[]);
	~PmergeMe();

	std::vector<int>  sortVector();
	std::deque<int> sortDeque();
	typedef std::vector<int>::iterator iter;
	typedef std::deque<int>::iterator iterDeque;

};

#endif