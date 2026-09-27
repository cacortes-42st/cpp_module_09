/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:49:55 by cacortes          #+#    #+#             */
/*   Updated: 2026/09/27 14:05:26 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>

bool	isNumber(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

int	date_parser(std::string date)
{
	size_t	l = 0;
	for (size_t i = 0; i < date.size() ; i++)
	{
		if (date[i] == '-')
		{
			if (!isdigit(date[i + 1]) || !isdigit(date[i - 1]))
				l = 2;
			l++;
		}
	}

	if (l != 2)
		return (1);

	std::string	year;
	std::string	month;
	std::string	day;

	std::istringstream line(date);

	std::getline(line, year, '-');
	std::getline(line, month, '-');
	std::getline(line, day, '-');

	if (!isNumber(year))
		return(1);
	else if (!isNumber(month))
		return(1);
	else if (!isNumber(day))
		return(1);
	
	int	Iyear;
	int	Imonth;
	int	Iday;

	std::istringstream(year) >> Iyear;
	std::istringstream(month) >> Imonth;
	std::istringstream(day) >> Iday;

	if (Imonth <= 0 || Imonth > 12)
		return(1);
	else if (Iday <= 0 || Iday > 31)
		return(1);
	
	std::cout << year << std::endl;
	std::cout << month << std::endl;
	std::cout << day << std::endl;

	return (0);
}
int	parse_line(std::string date, char separator, std::string value)
{
	if (date_parser(date))
		return (1);
	(void)value;
	if (separator != '|')
		return (1);
	return (0);
}

int	line_extractor(int fd)
{
	char buffer[1024];
	size_t n;
	std::string line;

	std::string date;
	char separator;
	std::string value;

	while ((n = read(fd, buffer, sizeof(buffer))) > 0)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (buffer[i] == '\n')
			{
				//std::cout << "LINEA: " << line << std::endl;
				std::istringstream iss(line);
				iss >> date >> separator >> value;
				
				std::cout << date << std::endl;
				std::cout << separator << std::endl;
				std::cout << value << std::endl;
				std::cout << "\n" << std::endl;
				if (parse_line(date, separator, value))
					return (1);		
				line.clear();
			}
			else
				line += buffer[i];
		}
	}

	/*if (!line.empty())
		std::cout << "LINEA: " << line << std::endl;*/

	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "This program needs only one argument to run." << std::endl;
		return (1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		std::cout << "Error opening the file." << std::endl;
		return (1);
	}

	if (line_extractor(fd))
		std::cout << "ERROR" << std::endl;

	close(fd);

	return (0);
}