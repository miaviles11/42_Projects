/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:39:30 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/09 17:39:30 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype> // std::isdigit

/*
 * Reverse Polish Notation (RPN), also called postfix notation, writes the
 * operator AFTER its two operands. Example: "8 3 *" means 8 * 3.
 *
 * The classic way to evaluate it is with a STACK (LIFO):
 *   - When we read a NUMBER   -> push it on the stack.
 *   - When we read an OPERATOR -> pop the two most recent numbers,
 *                                 apply the operator, push the result back.
 * At the very end, exactly ONE value must remain: that is the result.
 *
 * This exercise is validated with std::stack (the container required here).
 */

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

RPN::~RPN() {}

// Returns true if the character is one of the four supported operators.
bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

void RPN::calculate(const std::string &expression)
{
	// std::istringstream lets us split the expression on whitespace easily:
	// each ">> token" reads the next non-space chunk.
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		// A valid token is exactly ONE character long: either a single digit
		// (0-9, because the subject guarantees numbers are always < 10) or a
		// single operator. Anything else (e.g. "(", "12", "a") is an error.
		if (token.length() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
		{
			// Convert the digit character to its numeric value and push it.
			_stack.push(static_cast<double>(token[0] - '0'));
		}
		else if (token.length() == 1 && isOperator(token[0]))
		{
			// An operator needs two operands already on the stack.
			if (_stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return;
			}

			// Pop order matters: the SECOND popped value is the left operand.
			// For "a b -" the stack is [a, b] (b on top), so a - b.
			double b = _stack.top();
			_stack.pop();
			double a = _stack.top();
			_stack.pop();
			double result = 0.0;

			switch (token[0])
			{
				case '+':
					result = a + b;
					break;
				case '-':
					result = a - b;
					break;
				case '*':
					result = a * b;
					break;
				case '/':
					if (b == 0) // guard against division by zero
					{
						std::cerr << "Error" << std::endl;
						return;
					}
					result = a / b;
					break;
			}
			_stack.push(result);
		}
		else
		{
			// Unknown token (brackets, multi-digit numbers, letters, ...).
			std::cerr << "Error" << std::endl;
			return;
		}
	}

	// A well-formed RPN expression collapses to exactly one value.
	// Zero values (empty input) or more than one value (too many numbers)
	// both mean the expression was malformed.
	if (_stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return;
	}

	std::cout << _stack.top() << std::endl;
}
