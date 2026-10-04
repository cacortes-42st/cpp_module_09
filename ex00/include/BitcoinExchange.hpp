/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0002lse60False9/20 F0alse:5False:18 by cacortes          #+#    #+#             */
/*   Updated: 20alse26/0F0lse/False2:30 01:48 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <cstdlib>

/*For read file system*/
#include <unistd.h>
#include <fcntl.h>

/*For istringstream*/
#include <sstream>

/*For the csv file*/
#include <fstream>
#include <map>

/*For de ints*/
#include <climits>

class	BadFileExcepction : public std::exception
{
	const char *what() const throw();
};

class   NegativeNumberExcepction : public std::exception
{
	const char *what() const throw();
};

class   OutOfRangeUpExcepction : public std::exception
{
	const char *what() const throw();
};

class	BadFormatException : public std::exception
{
	private:
		std::string message;
	public:
		BadFormatException(std::string &date, char separator, std::string &value, std::string &trash);
		~BadFormatException() throw();
		const char *what() const throw();
};

class   BadHeaderExcepction : public std::exception
{
	const char *what() const throw();
};

class   NoPreviousNumberExcepction : public std::exception
{
	const char *what() const throw();
};

#endif