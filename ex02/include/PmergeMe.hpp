/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:35 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/13 22:56:41 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

/*For max and min*/
#include <climits>

/*For the vector container*/
#include <vector>

/*For the stream*/
#include <sstream>

/*For strcpy*/
#include <cstring>

struct PairNumbers
{
	int	BigNumber;
	int	SmallNumber;
	int	IdNumber;

	PairNumbers();
	PairNumbers(int Big, int Small, int id);
};

int	MyAtoi(std::string str);
char	**int_to_char(const std::vector<int> &values);
void binary_insertion(int target, std::vector<int>& numbers);
std::vector<int>	jacky_secuency(int	argc);
std::vector<int> jacky_resolution(std::vector<int> littleOnes,
                                  std::vector<int> jacky);
int FindSmallNumberById(
    const std::vector<PairNumbers>& Numbers,
    int id);

template <typename T>


T	&chair_function(T &Container, std::vector<int> &BigOnes)
{
	for (size_t i = 0; i < BigOnes.size(); i++)
	{
		for (size_t j = 0; j < Container.size(); j++)
		{
			if (BigOnes[i] == Container[j].BigNumber)
			{
				Container[j].IdNumber = i;
				continue;
			}
		}
	}
	return Container;
}

template <typename T>
std::vector<int>	pair_creator(T &Container, char **numbers, int argc)
{
	std::vector<int> BigOnes;
	std::vector<int> SmallOnes;
	std::vector<int> result;
	int	leftover = 0;
	
	for (int i = 0, j = 0; i < argc; i += 2, ++j)
	{
		if (i + 1 < argc)
		{
			int first = MyAtoi(numbers[i]);
			int second = MyAtoi(numbers[i + 1]);

			if (first >= second)
			{
				Container.push_back(PairNumbers(first, second, j));
				BigOnes.push_back(first);
				SmallOnes.push_back(second);
			}
			else
			{
				Container.push_back(PairNumbers(second, first, j));
				BigOnes.push_back(second);
				SmallOnes.push_back(first);
			}
		}
		else
			leftover = MyAtoi(numbers[i]);
	}

	if (BigOnes.size() > 1)
	{
		std::vector<PairNumbers> Pair;
		char **Big = int_to_char(BigOnes);
		BigOnes = pair_creator(Pair, Big, BigOnes.size());
	}

	result = BigOnes;

	Container = chair_function(Container, BigOnes);
	
	// int smaller;

	// if (FindSmallNumberById(Container, 0, smaller))
	// {
    // 	result.insert(result.begin(), smaller);
	// 	std::cout << "SMALLER: " << smaller << std::endl;
	// }
	// else
	// {
    // 	std::cerr << "Error: no se encontro el IdNumber 0\n";
    // 	return result;
	// }
	int smaller = FindSmallNumberById(Container, 0);

	std::cout << "SMALLER VALUE: " << smaller << std::endl;
	if (smaller < 1)
		std::cout << "ERROR" << std::endl;
	else
		result.insert(result.begin(), smaller);

	for (size_t i = 0; i < SmallOnes.size(); i++)
	{
    	if (SmallOnes[i] == smaller)
    	{
        	SmallOnes.erase(SmallOnes.begin() + i);
        	break;
    	}
	}
	
	// for (size_t i = 0; i < result.size(); ++i)
    // 	std::cout << result[i] << ' ';
	// std::cout << "\n";

	if (result.size() <= 2)
	{
		if (leftover != 0)
		{
			//std::cout << "FIRST" << std::endl;
			binary_insertion(leftover, result);
			// for (size_t i = 0; i < result.size(); ++i)
    		// 	std::cout << result[i] << ' ';
			// std::cout << "\n";
		}
		return (result);
	}
	std::vector<int> JackyNumbers = jacky_secuency(argc);
	std::vector<int> SmallOnesOrg = jacky_resolution(SmallOnes, JackyNumbers);

	// for (size_t i = 0; i < result.size(); ++i)
    // 	std::cout << result[i] << ' ';
	// std::cout << "\n";

	// for (size_t i = 0; i < result.size(); ++i)
    // 	std::cout << SmallOnes[i] << ' ';
	// std::cout << "\n";
	
	for(size_t i = 0; i < SmallOnesOrg.size(); i++)
		binary_insertion(SmallOnesOrg[i], result);

	if (leftover != 0)
	{
			//std::cout << "FIRST" << std::endl;
		binary_insertion(leftover, result);
			// for (size_t i = 0; i < result.size(); ++i)
    		// 	std::cout << result[i] << ' ';
			// std::cout << "\n";
	}
	//binary_insertion(leftover, result);

	// for (size_t i = 0; i < result.size(); ++i)
    // 	std::cout << result[i] << ' ';
	// std::cout << "\n";
	
	// for (size_t i = 0; i < Container.size(); ++i)
    // 	std::cout << "BigNumber: " << Container[i].BigNumber << " " 
	// 				<< "SmallNumber: " << Container[i].SmallNumber << " "
	// 				<< "IdNumber: " << Container[i].IdNumber << '\n';

	return (result);
}

#endif