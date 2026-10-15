/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:35 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/15 11:21:18 by cacortes         ###   ########.fr       */
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

/*For strol*/
#include <cstdlib>

/*For the deque container*/
#include <deque>

/*For the clock*/
#include <ctime>

/*For setprecission*/
#include <iomanip>

struct PairNumbers
{
	int	BigNumber;
	int	SmallNumber;
	int	IdNumber;

	PairNumbers();
	PairNumbers(int Big, int Small, int id);
};

int	MyAtoi(std::string str);
std::vector<int>	jacky_secuency(int	argc);
std::vector<int> jacky_resolution(std::vector<int> littleOnes, std::vector<int> jacky);
void	free_char(char **result);

template <typename E>
void	result_printer(E &base)
{
	E result;
	for (size_t i = 0; i < base.size(); i++)
	{
		if (base[i] < 1)
			continue;
		result.push_back(base[i]);
	}
	for (size_t i = 0; i < result.size(); ++i)
    	std::cout << result[i] << ' ';
	std::cout << "\n";
}

template <typename Q>
int FindSmallNumberById(const Q& Numbers, int id)
{
    for (size_t i = 0; i < Numbers.size(); i++)
    {
        if (Numbers[i].IdNumber == id)
            return Numbers[i].SmallNumber;
    }

    return -1;
}


template <typename Q>
void binary_insertion(int target, Q& numbers)
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

template <typename Q>
char	**int_to_char(const Q &values)
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

template <typename T, typename U>

T &chair_function(T &Container, U &BigOnes)
{
	std::vector<bool> used(Container.size(), false);

	for (size_t i = 0; i < BigOnes.size(); i++)
	{
		int bestIndex = -1;

		for (size_t j = 0; j < Container.size(); j++)
		{
			if (used[j])
				continue;

			if (Container[j].BigNumber != BigOnes[i])
				continue;

			if (bestIndex == -1 || Container[j].SmallNumber	< Container[bestIndex].SmallNumber)
				bestIndex = j;
		}

		if (bestIndex != -1)
		{
			Container[bestIndex].IdNumber = i;
			used[bestIndex] = true;
		}
	}

	return Container;
}

template <typename Container, typename PairContainer>
PairContainer makePairs(const Container& container, bool useBigNumber)
{
    PairContainer result;

    typename Container::const_iterator it;

    for (it = container.begin(); it != container.end(); ++it)
    {
        int number;

        if (useBigNumber)
            number = it->BigNumber;
        else
            number = it->SmallNumber;

        result.push_back(std::make_pair(number, it->IdNumber));
    }

    return result;
}

template <typename T, typename U>
U	pair_creator(T &Container, char **numbers, int argc)
{
	U result;
	if (argc == 1)
	{
		int only = MyAtoi(numbers[0]);
		result.push_back(only);
		return (result);
	}

	U BigOnes;
	U SmallOnes;
	
	int	leftover = 0;
	
	for (int i = 0, j = 0; i < argc; i += 2, ++j)
	{
		if (i + 1 < argc)
		{
			int first1 = MyAtoi(numbers[i]);
			int second1 = MyAtoi(numbers[i + 1]);

			if (first1 >= second1)
			{
				Container.push_back(PairNumbers(first1, second1, j));
				// BigOnes.push_back(std::make_pair(first1, j));
				// SmallOnes.push_back(std::make_pair(second1, j));
			}
			else
			{
				Container.push_back(PairNumbers(second1, first1, j));
				// BigOnes.push_back(std::make_pair(second1, j));
				// SmallOnes.push_back(std::make_pair(first1, j));
			}
		}
		else
			leftover = MyAtoi(numbers[i]);
	}

	if (BigOnes.size() > 1)
	{
		T Pair;

		char **Big = int_to_char(BigOnes);
		BigOnes = pair_creator<T, U>(Pair, Big, static_cast<int>(BigOnes.size()));

		free_char(Big);
	}
	
	result = BigOnes;
	Container = chair_function(Container, BigOnes);
	
	BigOnes = makePairs(Container, true);
	SmallOnes = makePairs(Container, false);
	
	int smaller = FindSmallNumberById(Container, 0);
	result.insert(result.begin(), smaller);

	for (size_t i = 0; i < SmallOnes.size(); i++)
	{
    	if (SmallOnes[i] == smaller)
    	{
        	SmallOnes.erase(SmallOnes.begin() + i);
        	break;
    	}
	}

	if (result.size() <= 2)
	{
		if (leftover != 0)
			binary_insertion(leftover, result);
		return (result);
	}

	std::vector<int> JackyNumbers = jacky_secuency(argc);
	std::vector<std::pair<int, int> > SmallOnesVector(SmallOnes.begin(), SmallOnes.end());
	std::vector<std::pair<int, int> > SmallOnesOrg = jacky_resolution(SmallOnesVector, JackyNumbers);
	
	for(size_t i = 0; i < SmallOnesOrg.size(); i++)
		binary_insertion(SmallOnesOrg[i], result);

	if (leftover != 0)
		binary_insertion(leftover, result);

	return (result);
}

#endif