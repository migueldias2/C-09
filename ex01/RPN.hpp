#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib> //for strtof
#include <list>
#include <typeinfo>

class RPN
{
private:
	std::list<std::string> list;
	std::stack<std::string> stack;

	RPN();
	RPN(const RPN&);
	RPN& operator=(const RPN&);
public:
	RPN(const std::string&);
	~RPN();
	
	float getResult();

	typedef std::list<std::string>::reverse_iterator reverse_iter;
	typedef std::list<std::string>::iterator iter;

};

#endif