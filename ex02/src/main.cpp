/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:05 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/14 21:31:15 by cacortes         ###   ########.fr       */
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

int	argument_parsing(std::string numbers)
{
	char	*end;

	long	Inum = std::strtol(numbers.c_str(), &end, 10);

	if (*end != '\0' || Inum > INT_MAX || Inum <= 0)
		return(1);
	return (0);
}

int	argument_printer(char **numbers, int argc)
{
	for (int i = 1; i < argc; i++)
		std::cout << numbers[i] << " ";
	std::cout << "\n";
	return (0);
}

std::vector<int> jacky_resolution(std::vector<int> littleOnes,
                                  std::vector<int> jacky)
{
    std::vector<int> result;
    size_t previous = 0;

    for (size_t i = 0; i < jacky.size(); ++i)
    {
        size_t current = jacky[i];
		
        if (current > littleOnes.size())
            current = littleOnes.size();

        std::vector<int> numbers;

        while (current > previous)
        {
            numbers.push_back(littleOnes[current - 1]);
            --current;
        }

        for (size_t j = 0; j < numbers.size(); ++j)
            result.push_back(numbers[j]);

        previous = jacky[i];

        if (previous >= littleOnes.size())
            break;
    }

    return result;
}

std::vector<int>	jacky_secuency(int	argc)
{
	std::vector<int>	jacky;
	
	for (int i = 0; i < argc; i++)
	{
		if (i == 0)
			jacky.push_back(0);
		else if (i == 1)
			jacky.push_back(1);
		else
			jacky.push_back(jacky[i - 1] + 2 * jacky[i - 2]);
	}

	return(jacky);
}

void binary_insertion(int target, std::vector<int>& numbers)
{
    size_t first = 0;
    size_t second = numbers.size();

    while (first < second)
    {
        size_t pos = first + (second - first) / 2;

        if (numbers[pos] < target)
            first = pos + 1;
        else
            second = pos;
    }

    numbers.insert(numbers.begin() + first, target);
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
		std::cout << "Not enough arguments recieved." << std::endl;
		return (1);
	}


	for (int i = 1; i < argc ; i++)
	{
		if (argument_parsing(argv[i]))
		{
			std::cout << "Error." << std::endl;
			return (1);
		}
	}
	
	std::clock_t startV = std::clock();
	
	std::vector<PairNumbers> ContV;
	std::vector<int> resultV;
	resultV = pair_creator<std::vector<PairNumbers>, std::vector<int> >(ContV, argv + 1, argc - 1);
	
	std::clock_t endV = std::clock();
	double timeV = static_cast<double>(endV - startV) * 1000000.0 / CLOCKS_PER_SEC;

	
	std::clock_t startD = std::clock();

	std::deque<PairNumbers> ContD;
	std::deque<int> resultD;
	resultD = pair_creator<std::deque<PairNumbers>, std::deque<int> >(ContD, argv + 1, argc - 1);

	std::clock_t endD = std::clock();
	double timeD = static_cast<double>(endD - startD) * 1000000.0 / CLOCKS_PER_SEC;
	

	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Before: ";
	argument_printer(argv, argc);

	std::cout << "After: ";
	result_printer(resultV);

	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector: " << timeV << " us" << std::endl;
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque: " << timeD << " us" << std::endl;

	return (0);
}
