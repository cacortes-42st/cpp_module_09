/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:05 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/10 13:39:26 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	argument_parsing(std::string numbers)
{
	for (size_t i = 0; i < numbers.size() ; i++)
	{
		if (!std::isdigit(numbers[i]) || numbers[i] <= 0)
			return (1);
	}
	return (0);
}

int	MyAtoi(std::string str)
{
	int number = 0;

	std::istringstream ss(str);

	ss >> number;

	return (number);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Not enough arguments recieved." << std::endl;
		return (1);
	}

	for (int i = 1; i < argc ; i++)
	{
		if (argument_parsing(argv[i]))
		{
			std::cout << "The argument is not a valid integer." << std::endl;
			return (1);
		}
	}

	std::vector<int> Cont1;
	std::vector<int> Cont2;
	pair_creator(Cont1, Cont2, argv, argc);
	// for (int i = 1; i < argc ; i++)
	// {
	// 	std::cout << "CONTENT: " << argv[i] << std::endl;
	// }


	return (0);
}