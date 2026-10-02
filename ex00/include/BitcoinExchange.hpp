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

struct	ErrorFlag
{
	float	value;
	bool	NegativeNumber;
	bool	OutOfRangeUp;
	bool	OutOfRangeDown;
	bool	BadFormat;

	ErrorFlag() : value (0), NegativeNumber(false), OutOfRangeUp(false), OutOfRangeDown(false), BadFormat(false) {}
};

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

class   OutOfRangeDownExcepction : public std::exception
{
	const char *what() const throw();
};

class	BadFormatExcepction : public std::exception
{
	const char *what() const throw();
};


#endif