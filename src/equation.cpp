/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:47:53 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/08 18:24:27 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <regex>
#include "equation.h"

#define REGEX_PATTERN1 "([xX] *(\\^ *[0-2])? *(\\* *\\d)?|\\d *\\* *[xX] *(\\^ *[0-2])?|\\d|\\d *[xX] *(\\^ *[0-2])?) *([+-=]|$)"

equation::equation(const char *av)
{
	std::string::iterator	end;

	str = av;
	end = std::remove(str.begin(), str.end(), ' ');
	str.erase(end, str.end());
}

bool	equation::parse()
{
	std::regex	pattern1(REGEX_PATTERN1);

	std::regex_iterator<std::string::iterator>	iterator(str.begin(), str.end(), pattern1);
	std::regex_iterator<std::string::iterator>	end;
	size_t		len;

	len = 0;
	std::cout << "Total = " << std::distance(iterator, end) << std::endl;
	while (iterator != end)
	{
		// std::cout << iterator->str() << std::endl;
		len += iterator->str().length();
		++iterator;
	}

	return (len == str.length());
}

bool	equation::isCorrect()
{
	if (str.find('=') == std::string::npos)
		return (false);
	return (equation::parse());
}

/*
TEST :
2 = 0
2 + 2 = 0

x+2 = 0
x^1 + 2 = 0
5x+2 = 0
5 * x + 2 = 0
5 * 3x + 2 = 0
5 * x^1 + 2 = 0
5 * 4x^1 + 2 = 0
5 * x^1 + 2x^2 = 0

2 + x = 0
2 + x^1 = 0
2 + 5x = 0
2 + 5*x = 0
2 + 5*x + 2 = 0
2 + 5*x ^1 = 0
*/
