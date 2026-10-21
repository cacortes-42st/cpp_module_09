/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:49:55 by cacortes          #+#    #+#             */
/*   Updated: 2026/10/21 18:45:35 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	check_date(int month, int day)
{
	if (month % 2 != 0)
	{
		if (month > 7)
		{
			if (day != 30)
				return (1);
		}
		else
		{
			if (day != 31)
				return (1);
		}
	}
	else
	{
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

bool	isNumberY(std::string str)
{
	if (str.size() != 4)
		return false;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

bool isNumberDM(std::string str)
{
	if (str.size() != 2)
		return false;
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

	if (!isNumberY(year))
		return(1);
	else if (!isNumberDM(month))
		return(1);
	else if (!isNumberDM(day))
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
			if (check_date(Imonth, Iday))
				return (1);
		}
	}
	
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
	{
		if (result < 0)
			throw NegativeNumberExcepction();
		else if (result > 1000)
			throw OutOfRangeUpExcepction();
	}
	return (0);
}

int	isInt(std::string lit)
{
	size_t i = 0;
	long	Ilit = 0;
	char	*end;

	if (lit.empty())
		return (1);
	if (lit[i] == '+')
		i++;
	else if (lit[i] == '-')
		throw NegativeNumberExcepction();
	if (i == lit.length())
		return (1);
	while(i < lit.length())
	{
		if (!std::isdigit(lit[i]))
			return (1);
		i++;
	}

	Ilit = std::strtol(lit.c_str(), &end, 10);
	if (Ilit < 0 || Ilit > 1000 || Ilit < INT_MIN || Ilit > INT_MAX)
	{
		if (Ilit < 0)
			throw NegativeNumberExcepction();
		else if (Ilit > 1000)
			throw OutOfRangeUpExcepction();
		else
			throw OutOfRangeUpExcepction();
	}
	
	
	return (0);
}

int	value_parser(std::string value)
{
	if (!isInt(value))
		return (0);
	else if (!isEsInt(value))
		return (0);
	
	return (1);
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

void	solution_printer(const std::string& date, std::string& value, std::map<std::string, float>& databaseS)
{
	std::map<std::string, float>::iterator itS;
	float amount = std::strtof(value.c_str(), NULL);

		itS = databaseS.find(date);

		if (itS != databaseS.end())
		{
			float result = amount * itS->second;;
			std::cout << date << " => " << amount << " = " << result << std::endl;
		}
		else
		{
			itS = databaseS.lower_bound(date);

			if (itS == databaseS.end())
				--itS;
			else if (itS->first != date)
			{
				if(itS == databaseS.begin())
					throw NoPreviousNumberExcepction();
				else
					--itS;
			}
			float result = amount * itS->second;
			std::cout << date << " => " << amount << " = " << result << std::endl;

		}
}

int	check_header(std::string line)
{
	if (line == "date | value")
		return (1);
	return (0);
}

void	process_line(std::string line, std::map<std::string, float> databaseS)
{
	std::string date;
	char separator = '\0';
	std::string value;
	std::string trash;
				
	std::istringstream iss(line);
	iss >> date >> separator >> value >> trash;

	if (!trash.empty() || !separator || value.empty() || date.empty())
		throw BadFormatException(date, separator, value, trash);
					
	if (parse_line(date, separator, value))
		throw BadFormatException(date, separator, value, trash);
	solution_printer(date, value, databaseS);
}

void line_extractor(int fd, std::map<std::string, float> databaseS)
{
	char buffer[1024];
	size_t n;
	std::string line;
	bool first_line = true;

	while ((n = read(fd, buffer, sizeof(buffer))) > 0)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (buffer[i] == '\n')
			{
				try
				{
					if (first_line)
					{
						first_line = false;
						if (!check_header(line))
						{
							std::cerr << "Error: " << BadHeaderExcepction().what() << std::endl;
							try
							{
								process_line(line, databaseS);
							}
							catch (std::exception &e)
							{
								std::cerr << "Error: " << e.what() << std::endl;
							}
						}
						line.clear();
						continue;
					}

					process_line(line, databaseS);
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

	if (!line.empty())
	{
		try
		{
			process_line(line, databaseS);
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		line.clear();
	}

}


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
	
	return (database);
}


int	main(int argc, char **argv)
{	
	try
	{
		if (argc != 2)
		{
			throw BadFileExcepction();
			return (1);
		}
		int	fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			throw BadFileExcepction();
			return (1);
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

		line_extractor(fd, databaseS);

		close(fd);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	
	return (0);
}
