/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:50:01 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/07 11:33:12 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	line_parser(std::string expr)
{
	for (size_t i = 0 ; i < expr.size() ; i++)
	{
		//std::cout << "Arguments: " << expr[i] << std::endl;
		if (!std::isdigit(expr[i]) && expr[i] != '+' && expr[i] != '-' && expr[i] != '/' && expr[i] != '*' && expr[i] != ' ')
		{
			std::cout << "Is not a correct element.";
			return (1);
		}
		else if (i + 1 <= expr.size() && expr[i] != ' ')
		{
			if (expr[i + 1] != ' ' && expr[i + 1] != '\0')
			{
				std::cout << "It has a wrong structure." << std::endl;
				return (1);
			}
		}
		else
		{
			if (i + 1 <= expr.size() && expr[i + 1] == '\0')
			{
				std::cout << "It has a wrong ending." << std::endl;
				return (1);
			}
		}
	}
	return (0);
}

void	stack_resolver(char expr, std::stack<char> stack)
{
	(void)expr;
	(void)stack;
	std::cout << "Expresion solved." << std::endl;
}

int	expression_processor(std::string expr, std::stack<char> stack)
{
	int	flag2digits = 0;


	for (size_t i = 0; i < expr.size() ; i++)
	{
		if (i + 2 <= expr.size() && std::isdigit(expr[i]) && flag2digits == 0)
		{
			stack.push(expr[i]);
			if (std::isdigit(expr[i + 2]))
			{
				stack.push(expr[i + 2]);
				flag2digits = 1;
			}
			else
			{
				std::cout << "No two digits on the expression." << std::endl;
				return (1);
			}
		}
		else
		{
			if (expr[i] != ' ')
			{
				stack.push(expr[i]);
				stack_resolver(expr[i], stack);
			}
		}
	}

	while (!stack.empty())
	{
		std::cout << "StackElement: " << stack.top() << std::endl;
		stack.pop();
	}

	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "The number of arguments provided is invalid." << std::endl;
		return (1);
	}

	std::cout << "Arguments: " << argv[1] << std::endl;
	
	if (line_parser(argv[1]))
	{
		std::cout << "Incorrect line." << std::endl;
		return (1);
	}

	std::stack<char> stack;
	if (expression_processor(argv[1], stack))
	{
		std::cout << "Incorrect expression." << std::endl;
		return (1);
	}
	
	std::cout << "GOOD" << std::endl;

	return (0);
}

/*

#include <iostream>
#include <stack>

int main() {
    std::stack<int> pila;

    pila.push(10);
    pila.push(20);
    pila.push(30);

    std::cout << pila.top() << '\n'; // 30

    pila.pop();

    std::cout << pila.top() << '\n'; // 20

    return 0;
}

*/