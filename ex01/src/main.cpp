/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:50:01 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/15 17:25:02 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	line_parser(std::string expr)
{
	for (size_t i = 0 ; i < expr.size() ; i++)
	{
		if (!std::isdigit(expr[i]) && expr[i] != '+' && expr[i] != '-' && expr[i] != '/' && expr[i] != '*' && expr[i] != ' ')
			return (1);
		else if (i + 1 <= expr.size() && expr[i] != ' ')
		{
			if (expr[i + 1] != ' ' && expr[i + 1] != '\0')
				return (1);
		}
		else
		{
			if (i + 1 <= expr.size() && expr[i + 1] == '\0')
				return(1);
		}
	}
	return (0);
}

std::stack<int>	stack_resolver(std::stack<int> stack, char opr, solution_box &Box)
{
	int	result = 0;

	if (stack.size() < 2)
	throw std::invalid_argument("");

	int opn2 = stack.top();
	stack.pop();
	int opn1 = stack.top();
	stack.pop();

	if (opr == '+')
	{
		result = opn1 + opn2;
		stack.push(result);
	}
	else if (opr == '-')
	{
		result = opn1 - opn2;
		stack.push(result);
	}
	else if (opr == '*')
	{
		result = opn1 * opn2;
		stack.push(result);
	}
	else if (opr == '/')
	{
		if (opn2 == 0)
			throw std::invalid_argument("");
		result = opn1 / opn2;
		stack.push(result);
	}

	Box.final_result = result;

	return (stack);
}

int	expression_parser(std::string expr)
{
	int	operands = 0;
	int operators = 0;

	for (size_t i = 0; i < expr.size() ; i++)
	{
		if (std::isdigit(expr[i]))
			operands += 1;
		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '/' || expr[i] == '*')
			operators += 1;
	}

	if (operands != operators + 1)
		throw std::invalid_argument("");

	return (0);
}

int	expression_processor(std::string expr, std::stack<int> stack)
{
	int	flag2digits = 0;
	solution_box Box;

	if (expression_parser(expr))
		return(1);

	for (size_t i = 0; i < expr.size() ; i++)
	{
		if (i + 2 <= expr.size() && std::isdigit(expr[i]) && flag2digits == 0)
		{
			stack.push(expr[i] - '0');
			if (std::isdigit(expr[i + 2]))
			{
				stack.push(expr[i + 2] - '0');
				flag2digits = 1;
				i += 2;
			}
			else
				throw std::invalid_argument("");
		}
		else if (std::isdigit(expr[i]))
			stack.push(expr[i] - '0');
		else
		{
			if (expr[i] != ' ')
				stack = stack_resolver(stack, expr[i], Box);
		}
	}

	std::cout << Box.final_result << std::endl;

	return (0);
}

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw std::invalid_argument("");
	
		if (line_parser(argv[1]))
			throw std::invalid_argument("");

		std::stack<int> stack;
		if (expression_processor(argv[1], stack))
			throw std::invalid_argument("");
	
	}
	catch (std::exception &e)
	{
		std::cerr << "Error" << std::endl;
	}


	return (0);
}
