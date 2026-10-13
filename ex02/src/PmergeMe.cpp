/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 09:38:19 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/13 22:17:13 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PairNumbers::PairNumbers() : BigNumber(0), SmallNumber(0), IdNumber(0)
{
}

PairNumbers::PairNumbers(int Big, int Small, int Id) 
	: BigNumber(Big), SmallNumber(Small), IdNumber(Id)
{
}