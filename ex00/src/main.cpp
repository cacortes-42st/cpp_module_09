/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:49:55 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/02 20:06:04 by cacortes         ###   ########.fr       */
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
		throw NegativeNumberExcepction();

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


	// std::cout << year << std::endl;
	// std::cout << month << std::endl;
	// std::cout << day << std::endl;
	
	return (0);
}

int	isEsInt(std::string lit)
{
	size_t i = 0;
	int	f = 0;
	int	p = 0;

	if (lit.empty())
		return (1);
	if (lit[i] == '+' || lit[i] == '-')
		i++;
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
		if ((!std::isdigit(lit[i]) && lit[i] != '.') || p > 1)
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
	std::cout << "\n" << std::endl;
    std::cout << "isEsInt: " << isEsInt(value) << std::endl;
    std::cout << "isInt: " << isInt(value) << std::endl;
	
	if (!isEsInt(value))
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

void	solution_printer(std::string date, float amount, std::map<std::string, float> databaseS)
{
	std::map<std::string, float>::iterator itS;

		itS = databaseS.find(date);

		if (itS != databaseS.end())
		{
			float result = amount * itS->second;;
			std::cout << date << " => " << amount << " = " << result << std::endl;
		}
		else
		{
			itS = databaseS.lower_bound(date);

			if (itS == databaseS.begin())
				--itS;
			else if (itS->first != date)
			{
				float result = amount * itS->second;
				std::cout << date << " => " << amount << " = " << result << std::endl;
			}
			--itS;
		}
}

std::multimap<std::string, float>	line_extractor(int fd, std::multimap<std::string, float> databaseI, std::map<std::string, float> databaseS)
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
				std::istringstream iss(line);
				iss >> date >> separator >> value;
				
				// std::cout << date << std::endl;
				// std::cout << separator << std::endl;
				// std::cout << value << std::endl;
				// std::cout << "\n" << std::endl;
				try
				{
					if (parse_line(date, separator, value))
					{
						std::cout << "ERROR" << std::endl;
						throw BadFormatExcepction();
					}
					float amount = std::strtof(value.c_str(), NULL);
					std::multimap<std::string, float>::iterator it = databaseI.insert(std::make_pair(date, amount));
					solution_printer(it->first, it->second, databaseS);
				}
				catch (std::exception & e)
				{
					std::cerr << "Error: " << e.what() << std::endl;
				}
				line.clear();
			}
			else
				line += buffer[i];
		}
	}
	
	// std::multimap<std::string, float>::iterator it;

	// for (it = databaseI.begin(); it != databaseI.end(); it++)
	// {
	// 	std::cout << "Date: " << it->first << std::endl;
	// 	std::cout << "Value: " << it->second << std::endl;
	// }

	
	/*if (!line.empty())
		std::cout << "LINEA: " << line << std::endl;*/

	return (databaseI);
}


/*Check and process csv lines*/

std::map<std::string, float> file_extractor(std::ifstream& file)
{
	std::map<std::string, float> database;
	
	std::string	line;
	std::getline(file, line);

	while (getline(file, line))
	{
		std::string date;
		std::string value;

		std::istringstream seg(line);

		std::getline(seg, date, ',');
		std::getline(seg, value);

		database[date] = std::strtof(value.c_str(), NULL);
	}
	
	// std::map<std::string, float>::iterator it;

	// for (it = database.begin(); it != database.end(); it++)
	// {
	// 	std::cout << "Date: " << it->first << std::endl;
	// 	std::cout << "Value: " << it->second << std::endl;
	// }
	
	return (database);
}


int	main(int argc, char **argv)
{
	int	fd = open(argv[1], O_RDONLY);
	
	try
	{
		if (argc != 2)
		{
			throw BadFileExcepction();
			return (1);
		}
		if (fd == -1)
		{
			throw BadFileExcepction();
			return (1);
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::ifstream file("data.csv");
	std::map<std::string, float> databaseS;
		
	if (!file.is_open())
	{
		throw BadFileExcepction();
		return (1);
	}
	else
		databaseS = file_extractor(file);

	std::multimap<std::string, float> databaseI;

	databaseI = line_extractor(fd, databaseI, databaseS);

		
	//solution_printer(databaseI, databaseS);	

	close(fd);



	return (0);
}


/*

#include <iostream>
#include <map>
#include <string>

struct Persona
{
    std::string nombre;
    int edad;
    double altura;
};

int main()
{
    std::multimap<int, Persona> personas;

    Persona p1;
    p1.nombre = "Juan";
    p1.edad = 25;
    p1.altura = 1.75;

    Persona p2;
    p2.nombre = "Ana";
    p2.edad = 30;
    p2.altura = 1.68;

    personas.insert(std::make_pair(1, p1));
    personas.insert(std::make_pair(1, p2));

    return 0;
}

*/