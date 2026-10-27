/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:35 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/27 21:40:53 by cacortes         ###   ########.fr       */
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

/*For the pair container*/
#include <utility>

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
void	free_char(char **result);

inline void print_element(const std::pair<int, int>& value)
{
	if (value.first <= 0)
		return;
	std::cout << value.first << " ";
}

template <typename E>
void result_printer(const E& base)
{
	for (size_t i = 0; i < base.size(); ++i)
		print_element(base[i]);

	std::cout << '\n';
}

template <typename Q>
std::pair<int, int> FindSmallNumberById(const Q& Numbers, int id)
{
	for (size_t i = 0; i < Numbers.size(); i++)
	{
		if (Numbers[i].second == id)
			return Numbers[i];
	}

	return std::make_pair(0, -1);
}

template <typename Q, typename S>
void binary_insertion(Q& result, const S& SmallOnesOrg)
{
	for (size_t i = 0; i < SmallOnesOrg.size(); ++i)
	{
		int small = SmallOnesOrg[i].first;
		int id = SmallOnesOrg[i].second;

		size_t first = 0;
		size_t last = result.size();

		if (id != -1)
		{
			size_t bigPos = 0;

			while (bigPos < result.size() && result[bigPos].second != id)
				++bigPos;

			if (bigPos == result.size())
				continue;

			last = bigPos;
		}

		while (first < last)
		{
			size_t mid = first + (last - first) / 2;

			if (result[mid].first < small)
				first = mid + 1;
			else
				last = mid;
		}

		result.insert(result.begin() + first, std::make_pair(small, id));
	}
}

template <typename Q>
char	**int_to_char(const Q &values)
{
	char	**result = new char*[values.size() + 1];

	for (size_t i = 0; i < values.size(); ++i)
	{
		std::ostringstream stream;
		stream << values[i].first;

		std::string str = stream.str();

		result[i] = new char[str.size() + 1];
		std::strcpy(result[i], str.c_str());
	}

	result[values.size()] = NULL;
	return result;
}

template <typename T, typename U>
T& chair_function(T& Container, U& BigOnes)
{
	T orderedContainer;
	std::vector<bool> used(Container.size(), false);

	for (size_t i = 0; i < BigOnes.size(); ++i)
	{	
		int bestIndex = -1;

		for (size_t j = 0; j < Container.size(); ++j)
		{
			if (used[j])
				continue;

			if (Container[j].BigNumber != BigOnes[i].first)
				continue;

			bestIndex = static_cast<int>(j);
			break;
		}

		if (bestIndex != -1)
		{
			PairNumbers pair = Container[bestIndex];
			
			pair.IdNumber = static_cast<int>(i);

			orderedContainer.push_back(pair);
			used[bestIndex] = true;
		}
	}

	Container = orderedContainer;
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

template <typename J>
J jacky_resolution(J littleOnes, std::vector<int> jacky)
{
	J result;

	size_t previous = 0;
	size_t size = littleOnes.size();

	for (size_t i = 0; i < jacky.size(); ++i)
	{
		size_t current = static_cast<size_t>(jacky[i]);

		if (current > size)
			current = size;

		while (current > previous)
		{
			result.push_back(littleOnes[current - 1]);
			--current;
		}

		previous = static_cast<size_t>(jacky[i]);

		if (previous >= size)
			break;
	}

	return result;
}


template <typename T, typename U>
U	main_creator(T &Container, char **numbers, int argc)
{
	U main_chain;
	U BigOnes;
	U SmallOnes;
	
	bool hasLeftover = (argc % 2 != 0);
	int leftover = 0;

	if (hasLeftover)
		leftover = MyAtoi(numbers[argc - 1]);

	
	for (int i = 0, j = 0; i < argc; i += 2, ++j)
	{
		if (i + 1 < argc)
		{
			int first1 = MyAtoi(numbers[i]);
			int second1 = MyAtoi(numbers[i + 1]);

			if (first1 >= second1)
			{
				Container.push_back(PairNumbers(first1, second1, j));
				BigOnes.push_back(std::make_pair(first1, j));
			}
			else
			{
				Container.push_back(PairNumbers(second1, first1, j));
				BigOnes.push_back(std::make_pair(second1, j));
			}
		}
	}

	if (BigOnes.size() > 1)
	{
		T Pair;

		char **Big = int_to_char(BigOnes);
		BigOnes = main_creator<T, U>(Pair, Big, static_cast<int>(BigOnes.size()));

		free_char(Big);
	}

	Container = chair_function(Container, BigOnes);
	
	BigOnes = makePairs<T, U>(Container, true);
	SmallOnes = makePairs<T, U>(Container, false);
	
	std::pair<int, int> smaller = FindSmallNumberById(SmallOnes, 0);
	
	main_chain = BigOnes;
	
	main_chain.insert(main_chain.begin(), smaller);

	for (size_t i = 0; i < SmallOnes.size(); i++)
	{
    	if (SmallOnes[i].second == smaller.second)
    	{
        	SmallOnes.erase(SmallOnes.begin() + i);
        	break;
    	}
	}

	if (hasLeftover)
		SmallOnes.push_back(std::make_pair(leftover, -1));

	std::vector<int> JackyNumbers = jacky_secuency(static_cast<int>(SmallOnes.size()));

	U SmallOnesOrg = jacky_resolution(SmallOnes, JackyNumbers);

		
	binary_insertion(main_chain, SmallOnesOrg);

	return (main_chain);
}

#endif