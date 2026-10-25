/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:05 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/25 20:40:37 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	MyAtoi(std::string str)
{
	int number = 0;

	std::istringstream ss(str);

	ss >> number;

	return (number);
}

int	ArgumentParsing(std::string numbers)
{
	char	*end;

	long	Inum = std::strtol(numbers.c_str(), &end, 10);

	if (*end != '\0' || Inum > INT_MAX || Inum <= 0)
		return(1);
	return (0);
}

int	ArgumentPrinter(char **numbers, int argc)
{
	for (int i = 1; i < argc; i++)
		std::cout << numbers[i] << " ";
	std::cout << "\n";
	return (0);
}

// std::vector<std::pair<int, int> > jacky_resolution(std::vector<std::pair<int, int> > littleOnes, std::vector<int> jacky)
// {
// 	std::vector<std::pair<int, int> > result;

// 	size_t previous = 0;
// 	size_t size = littleOnes.size();

// 	for (size_t i = 0; i < jacky.size(); ++i)
// 	{
// 		size_t current = static_cast<size_t>(jacky[i]);

// 		if (current > size)
// 			current = size;

// 		while (current > previous)
// 		{
// 			result.push_back(littleOnes[current - 1]);
// 			--current;
// 		}

// 		previous = static_cast<size_t>(jacky[i]);

// 		if (previous >= size)
// 			break;
// 	}

// 	return result;
// }

std::vector<int> jacky_secuency(int count)
{
	std::vector<int> jacky;

	if (count <= 0)
		return jacky;

	jacky.push_back(1);

	if (count == 1)
		return jacky;

	jacky.push_back(3);

	while (jacky.back() < count)
	{
		size_t size = jacky.size();

		long long next = static_cast<long long>(jacky[size - 1]) + 2LL * jacky[size - 2];

		if (next > count)
			next = count;

		jacky.push_back(static_cast<int>(next));
	}

	return jacky;
}

void	free_char(char **result)
{
	if (!result)
		return ;
	for (size_t i = 0; result[i] != NULL; ++i)
		delete[] result[i];

	delete[] result;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Not enough arguments recieved." << std::endl;
		return (1);
	}


	for (int i = 1; i < argc ; i++)
	{
		if (ArgumentParsing(argv[i]))
		{
			std::cerr << "Error." << std::endl;
			return (1);
		}
	}
	
	std::clock_t startV = std::clock();
	
	std::vector<PairNumbers> ContV;
	std::vector<std::pair<int, int> > resultV;
	resultV = main_creator<std::vector<PairNumbers>, std::vector<std::pair<int, int> > >(ContV, argv + 1, argc - 1);
	
	std::clock_t endV = std::clock();
	double timeV = static_cast<double>(endV - startV) * 1000000.0 / CLOCKS_PER_SEC;

	
	std::clock_t startD = std::clock();

	std::deque<PairNumbers> ContD;
	std::deque<std::pair<int, int> > resultD;
	resultD = main_creator<std::deque<PairNumbers>, std::deque<std::pair<int, int> > >(ContD, argv + 1, argc - 1);

	std::clock_t endD = std::clock();
	double timeD = static_cast<double>(endD - startD) * 1000000.0 / CLOCKS_PER_SEC;
	

	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Before: ";
	ArgumentPrinter(argv, argc);

	std::cout << "After: ";
	result_printer(resultV);

	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector: " << timeV << " us" << std::endl;
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque: " << timeD << " us" << std::endl;

	return (0);
}
