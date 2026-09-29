/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:49:55 by cacortes          #+#    #+#             */
/*   Updated: 2026/09/29 16:28:17 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>

/*Check and process input lines*/

int	check_date(int month, int day)
{
	(void)day;
	if (month % 2 != 0)
	{
		std::cout << "Es impar" << std::endl;
		if (month >= 7)
		{
			if (day != 31)
				return (1);
		}
		else
		{
			if (day != 30)
				return (1);
		}
	}
	else
	{
		std::cout << "Es par" << std::endl;
		if (month >= 8)
		{
			if (day != 31)
				return (1);
		}
		else
		{
			if (day != 30)
				return (1);
		}
	}
	return (0);
}

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
	else
	{
		if (Imonth == 02)
		{
			if ((Iyear % 4 == 0 && Iyear % 100 != 0) || Iyear % 400 == 0)
			{
				if (Iday != 29)
					return (1);
			}
			else
				if (Iday != 28)
					return (1);
		}
		if (Iday == 31 || Iday == 30)
		{
			if (!check_date(Imonth, Iday))
				return (1);
		}
	}


	std::cout << year << std::endl;
	std::cout << month << std::endl;
	std::cout << day << std::endl;

	return (0);
}

int	isFloat(std::string lit)
{
	size_t i = 0;
	int	f = 0;
	int	p = 0;

	if (lit.empty())
		return (1);
	if (lit[i] == '+' || lit[i] == '-')
		i++;
	if (lit[lit.length() - 1] != 'f')
		return (1);
	while (i < lit.length())
	{
		if (lit[i] == 'f')
			f++;
		if (lit[i] == '.' && lit[i + 1] != '\0')
		{
			p++;
			if (lit[i + 1] == 'f')
				return (1);
		}
		if ((!std::isdigit(lit[i]) && lit[i] != '.' && lit[i] != 'f') || f > 1 || p > 1)
			return (1);
		i++;
	}
	if (p != 1)
		return (1);

	float result = std::strtof(lit.c_str(), NULL);
	if (result < 0 || result > 1000)
		return (1);
		
	return (0);
}

int	isInt(std::string lit)
{
	size_t i = 0;
	int	Ilit;

	if (lit.empty())
		return (1);
	if (lit[i] == '+')
		i++;
	else if (lit[i] == '-')
		return (1);
	if (i == lit.length())
		return (1);
	while(i < lit.length())
	{
		if (!std::isdigit(lit[i]))
			return (1);
		i++;
	}
	std::istringstream(lit) >> Ilit;
	if (Ilit < 0 || Ilit > 1000)
		return (1);
	
	return (0);
}

int	value_parser(std::string value)
{
	if (!isFloat(value))
		std::cout << "float" << std::endl;
	else if (!isInt(value))
		std::cout << "Int" << std::endl;
	else
		return (1);

	return (0);
}

int	parse_line(std::string date, char separator, std::string value)
{
	if (date_parser(date))
		return (1);
	if (value_parser(value))
		return (1);
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


/*Check and process csv lines*/

int	file_extractor(std::ifstream& file)
{
	
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


	std::ifstream file("data.csv");
	
	if (!file.is_open())
	{
		std::cout << "Error opening the file" << std::endl;
		return (1);
	}
	else
		file_extractor(file);
		
	close(fd);

	return (0);
}

/*
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

int main()
{
    std::map<std::string, float> database;

    std::ifstream file("data.csv");

    if (!file.is_open())
    {
        std::cerr << "Error: no se pudo abrir data.csv" << std::endl;
        return 1;
    }

    // Saltamos la cabecera
    std::string line;
    std::getline(file, line);

    // Leemos el resto
    while (std::getline(file, line))
    {
        std::string date;
        std::string price;

        std::getline(file, date, ',');
        std::getline(file, price);

        database[date] = std::atof(price.c_str());
    }

    // Comprobamos qué hemos guardado
    std::map<std::string, float>::iterator it;

    for (it = database.begin(); it != database.end(); ++it)
    {
        std::cout << it->first << " => "
                  << it->second << std::endl;
    }

    return 0;
}


*/
