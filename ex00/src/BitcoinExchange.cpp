/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:50:31 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/02 11:28:02 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

const char* BadFileExcepction::what() const throw()
{
    return "could not open file.";
}

const char* NegativeNumberExcepction::what() const throw()
{
    return "not a positive number.";
}

const char* OutOfRangeUpExcepction::what() const throw()
{
    return "too large a number.";
}

const char* OutOfRangeDownExcepction::what() const throw()
{
    return "too low a number.";
}

const char* BadFormatExcepction::what() const throw()
{
    return "bad input";
}


