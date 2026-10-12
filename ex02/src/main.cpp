/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:05 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/12 14:00:04 by cacortes         ###   ########.fr       */
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

// std::vector<int>	jacky_resolution(std::vector<int> littleOnes, std::vector<int> jacky)
// {
// 	std::vector<int> numbers;
// 	std::vector<int> result;

// 	int j = 0;
// 	for (size_t i = 0; i < jacky.size(); i++)
// 	{
// 		while(littleOnes[j] < jacky[i] && littleOnes[j] < jacky[i + 1])
// 		{
// 			numbers.push_back(littleOnes[j]);
// 			j++;
// 		}
// 		result = numbers;
// 	}
// 	for (size_t i = 0; i < result.size(); ++i)
//     	std::cout << "Numbers: " << result[i] << '\n';

// 	std::cout << "PARSE1" << std::endl;
// 	return (result);
// }


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

    for (size_t i = 0; i < result.size(); ++i)
        std::cout << "Numbers: " << result[i] << '\n';

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

	// for (int i = 0; i < argc; i++)
	// 	std::cout << jacky[i] << std::endl;

	return(jacky);
}

void binary_search(int target, const std::vector<int>& numbers)
{
    size_t first = 0;
    size_t second = numbers.size();

    while (first < second)
    {
        size_t pos = first + (second - first) / 2;

        if (numbers[pos] < target)
        {
            first = pos + 1;
        }
        else if (numbers[pos] > target)
        {
            second = pos;
        }
        else
        {
            std::cout << "Number found at index: " << pos << '\n';
            return;
        }
    }

    std::cout << "Number not found\n";
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
	
	numeros.push_back(2);
	numeros.push_back(9);
	numeros.push_back(4);
	numeros.push_back(1);
	numeros.push_back(3);

	binary_search(1, numeros);
	//jacky_resolution(numeros, jacob);
	// for (int i = 1; i < argc ; i++)
	// {
	// 	std::cout << "CONTENT: " << argv[i] << std::endl;
	// }


	return (0);
}



// void	binary_serach(int target, std::vector<int>numbers)
// {
// 	size_t	first = 0;
// 	size_t	second = numbers.size();

// 	while (first < second)
// 	{
// 		int pos = numbers.size() / 2;

// 		if (pos < target)
// 		{
// 			first = pos;
// 			second = numbers.end(); 
// 		}
// 		else if (pos > target)
// 		{
// 			first = pos;
// 			second = numbers.end(); 			
// 		}
// 		else

// 	}
// }