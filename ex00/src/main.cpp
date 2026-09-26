/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacortes <cacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:49:55 by cacortes          #+#    #+#             */
/*   Updated: 2026/09/26 20:07:02 by cacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	parse_line(std::string date, char separator, double value)
{
	(void)date;
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
	double value;

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