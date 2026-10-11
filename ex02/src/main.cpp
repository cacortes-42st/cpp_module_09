/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:05 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/11 17:59:22 by cacortes         ###   ########.fr       */
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

char	**int_to_char(const std::vector<int> &values)
{
	char	**result = new char*[values.size() + 1];

	for (size_t i = 0; i < values.size(); ++i)
	{
		std::ostringstream stream;
		stream << values[i];

		std::string str = stream.str();

		result[i] = new char[str.size() + 1];
		std::strcpy(result[i], str.c_str());
	}

	result[values.size()] = NULL;
	return result;
}

std::vector<int>	jacky_resolution(std::vector<int> littleOnes, std::vector<int> jacky)
{
	std::vector<int> numbers;
	std::vector<int> result;

	int j = 0;
	for (size_t i = 0; i < jacky.size(); i++)
	{
		while(littleOnes[j] < jacky[i] && littleOnes[j] < jacky[i + 1])
		{
			numbers.push_back(littleOnes[j]);
			j++;
		}
		numbers = result;
	}

	return (result);
}
std::vector<int>	jacky_secuency(int	argc)
{
	std::vector<int>	jacky;

	for (int i = 0; i < argc; i++)
	{
		if (i == 0)
			jacky[i] = 0;
		else if (i == 1)
			jacky[i] = 1;
		else
			jacky[i] = jacky[i - 1] + 2 * jacky[i - 2];
	}

	for (int i = 0; i < argc; i++)
		std::cout << jacky[i] << std::endl;

	return(jacky);
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

	std::vector<PairNumbers> Cont1;
	//pair_creator(Cont1, argv + 1, argc - 1);
	std::vector<int> jacob; 
	jacob = jacky_secuency(argc - 1);


	std::vector<int> numeros;
	
	numeros.push_back(10);
	numeros.push_back(8);
	numeros.push_back(3);
	numeros.push_back(9);

	jacky_resolution(numeros, jacob);
	// for (int i = 1; i < argc ; i++)
	// {
	// 	std::cout << "CONTENT: " << argv[i] << std::endl;
	// }


	return (0);
}
