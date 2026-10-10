/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:35 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/10 19:09:10 by cacortes         ###   ########.fr       */
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

int	MyAtoi(std::string str);

template <typename T>
void	pair_creator(T &Container, char **numbers, int argc)
{
	Container<std::pair<int, int>> box;

	for (int i = 1; i < argc; i++)
	{
		int firstA = MyAtoi(numbers[i]);
		int secondA = MyAtoi(numbers[i + 1]);

		
		if (i + 1 <= argc && first >= second)
		{
			BigContainer.push_back(first);
			SmallContainer.push_back(second);
			i += 1;
		}
		else if (i + 1 <= argc)
		{
			BigContainer.push_back(second);
			SmallContainer.push_back(first);
			i += 1;			
		}
	}

	//std::cout << "PARSE1" << std::endl;
	for (size_t i = 0; i < BigContainer.size(); i++)
		std::cout << BigContainer[i] << " ";
	std::cout << "BIG" << std::endl;
	
	for (size_t i = 0; i < SmallContainer.size(); i++)
		std::cout << SmallContainer[i] << " ";
	std::cout << "SMALL" << std::endl;
}

#endif