/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:50:31 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/04 23:01:46 by cacortes         ###   ########.fr       */
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


BadFormatException::BadFormatException(std::string &date, char separator, std::string &value, std::string &trash) : message("")
{
	if (trash.empty() && !separator && value.empty() && date.empty())
		message = "bad input.";
	else
		message = "bad input => " + date + " " + separator + " " + value + " " + trash;
}

BadFormatException::~BadFormatException() throw()
{
}

const char* BadFormatException::what() const throw()
{
    return message.c_str();
}


const char* BadHeaderExcepction::what() const throw()
{
    return "The header input file is incorrect.";
}

const char* NoPreviousNumberExcepction::what() const throw()
{
    return "No previous date exists.";
}