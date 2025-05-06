#include "RPN.hpp"

RPN& RPN::operator=(const RPN&) {return *this;}

bool validInput(const std::string& input, std::list<std::string>& list);
void fillStack(std::stack<std::string>& stack, std::list<std::string>& list);


RPN::RPN(const std::string& string)
{
	if (!validInput(string, list))
		throw std::runtime_error("Invalid input");
}

RPN::~RPN()
{
}

float RPN::getResult()
{
	fillStack(stack, list);

	std::stack<float> numbers;
	char* end;

	while (!stack.empty())
	{
		std::string& token = stack.top(); stack.pop();
		if (token == "-" || token == "+" || token == "*" || token == "/")
		{
			float operand1 = numbers.top(); numbers.pop();
			float operand2 = numbers.top(); numbers.pop();
			if (token == "-")
				numbers.push(operand1 - operand2);
			else if (token == "+")
				numbers.push(operand1 + operand2);
			else if (token == "*")
				numbers.push(operand1 * operand2);
			else if (token == "/")
			{
				if (token == "/" && operand2 == 0.0f) {
					throw std::runtime_error("Error: division by zero");
				}
				numbers.push(operand1 / operand2);
			}
		}
		else
			numbers.push(strtof(token.c_str(), &end));
	}
	return (numbers.top());
}

void fillStack(std::stack<std::string>& stack, std::list<std::string>& list)
{
	for (RPN::reverse_iter it=list.rbegin(); it!=list.rend(); ++it)
		stack.push(*it);
}

bool isNumber(std::string& string)
{
	char* end;
	strtof(string.c_str(), &end);
	if (*end != '\0')
		return false;
	return true;
}

void fillList(const std::string& input, std::list<std::string>& list)
{
	std::istringstream stream(input);
	std::string word;
	while(stream >> word)
		list.push_back(word);
}

bool isNumberOrOperator(std::list<std::string>& list)
{
	std::string operators[] = {"+", "-", "*", "/"};
	for (RPN::iter it = list.begin(); it != list.end(); ++it)
	{
		bool isOperator = false;
		for (int i = 0; i < 4; ++i)
		{
			if (operators[i] == *it)
			{
				isOperator = true;
				break;
			}
		}
		if (!isNumber(*it) && !isOperator)
			return false;
	}
	return true;
}

bool validFormat(std::list<std::string>& list)
{
	RPN::iter first = list.begin();
	RPN::iter second = ++first;

	if (list.size() < 3)
		return false;
	if (!isNumber(*first) || !isNumber(*second))
		return false;
	if (isNumber(list.back()))
		return false;

	int numbers = 0;
	int nOperators = 0;

	for (RPN::iter it = list.begin(); it != list.end(); ++it)
	{
		if (isNumber(*it))
			++numbers;
		else
			++nOperators;
		if (nOperators == numbers)
			return false;
	}
	return true;
}

bool validInput(const std::string& input, std::list<std::string>& list)
{
	fillList(input, list);
	
	if (!isNumberOrOperator(list) || !validFormat(list))
	{
		std::cerr << "Impossible RVP.\n";
		return false;
	}

	return true;
}