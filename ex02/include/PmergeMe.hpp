/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:35 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/13 14:46:11 by cacortes         ###   ########.fr       */
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

template <typename T>

// void	binary_insertion(T &Container, char** Big)
// {
	
// }
std::vector<int>	pair_creator(T &Container, char **numbers, int argc)
{
	std::vector<int> BigOnes;
	std::vector<int> SmallOnes;
	std::vector<int> result;
	
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
	}

	if (BigOnes.size() > 1)
	{
		std::vector<PairNumbers> Pair;
		char **Big = int_to_char(BigOnes);
		BigOnes = pair_creator(Pair, Big, BigOnes.size());
	}

	result = BigOnes;

	result.insert(result.begin(), Container[0].SmallNumber);

	std::cout << "FIRST" << std::endl;
	for (size_t i = 0; i < result.size(); ++i)
    	std::cout << result[i] << ' ';
	std::cout << "\n";

	if (result.size() <= 2)
		return (result);
	std::vector<int> JackyNumbers = jacky_secuency(argc);
	std::vector<int> SmallOnesOrg = jacky_resolution(SmallOnes, JackyNumbers);

	std::cout << "THIRD" << std::endl;
	for (size_t i = 0; i < result.size(); ++i)
    	std::cout << result[i] << ' ';
	std::cout << "\n";
	std::cout << "THIRD1" << std::endl;
	for (size_t i = 0; i < result.size(); ++i)
    	std::cout << SmallOnes[i] << ' ';
	std::cout << "\n";
	for(size_t i = 0; i < SmallOnesOrg.size(); i++)
		binary_insertion(SmallOnesOrg[i], result);

	std::cout << "SECOND" << std::endl;
	for (size_t i = 0; i < result.size(); ++i)
    	std::cout << result[i] << ' ';
	std::cout << "\n";
	
	for (size_t i = 0; i < Container.size(); ++i)
    	std::cout << "BigNumber: " << Container[i].BigNumber << " " 
					<< "SmallNumber: " << Container[i].SmallNumber << " "
					<< "IdNumber: " << Container[i].IdNumber << '\n';

	return (result);
}

#endif