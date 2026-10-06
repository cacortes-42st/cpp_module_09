/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:50:01 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/06 13:30:56 by cacortes         ###   ########.fr       */
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

	std::cout << "GOOD" << std::endl;

	return (0);
}