/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:47:53 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/09 20:09:12 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <regex>
#include "computor.h"
#include "equation.h"

#define PATTERN_EQUATION "([xX] *(\\^ *[0-2])?|-?\\d+ *\\* *[xX] *(\\^ *[0-2])?|-?\\d+|-?\\d+ *[xX] *(\\^ *[0-2])?) *([\\+\\-\\=]|$)"

#define PATTERN_CONTAINS_X ".*[xX]+.*"
#define PATTERN_NO_DEGREE ".*[xX]\\^0.*"
#define PATTERN_FIRST_DEGREE ".*[xX]\\^1.*"
#define PATTERN_SECOND_DEGREE ".*[xX]\\^2.*"

equation::equation(const char *av)
{
	std::string::iterator	end;

	str = av;
	end = std::remove(str.begin(), str.end(), ' ');
	str.erase(end, str.end());
	a = 0;
	b = 0;
	c = 0;
	x1 = 0;
	x2 = 0;
}

void	equation::setVariables(std::string str, bool negative, enum EquationSide side)
{
	std::regex	contains_x(PATTERN_CONTAINS_X);
	std::regex	is_no_degree(PATTERN_NO_DEGREE);
	std::regex	is_second_degree(PATTERN_SECOND_DEGREE);
	double		*dest;
	double		nb;

	nb = 1.0;
	if (!std::regex_match(str, contains_x) || std::regex_match(str, is_no_degree))
		dest = &c;
	else if (std::regex_match(str, is_second_degree))
		dest = &a;
	else
		dest = &b;
	if (std::isdigit(str.front()))
		nb = std::stod(str);
	if (negative)
		nb *= -1;
	if (side == RIGHT)
		nb *= -1;
	*dest += nb;
}

bool	equation::parse()
{
	std::regex			pattern1(PATTERN_EQUATION);
	std::regex_iterator<std::string::iterator>	iterator(str.begin(), str.end(), pattern1);
	std::regex_iterator<std::string::iterator>	end;

	size_t				len;
	bool				negative;
	enum EquationSide	side;

	len = 0;
	negative = false;
	side = LEFT;
	while (iterator != end)
	{
		// std::cout << iterator->str() << std::endl;
		setVariables(iterator->str(), negative, side);
		switch (iterator->str().back())
		{
			case '=' :
				side = RIGHT;
				break ;
			case '-' :
				negative = true;
				break ;
			default :
				negative = false;
				break ;
		}
		len += iterator->str().length();
		++iterator;
	}
	std::cout << "a = " << a << "; b = " << b << "; c = " << c << std::endl;
	return (len == str.length());
}

bool	equation::isCorrect()
{
	int		pos;

	if ((pos = str.find('=')) == std::string::npos || pos + 1 == str.length())
		return (false);
	return (equation::parse());
}

double	equation::sqrt(double nb)
{
	double	i;
	if (nb < 1)
		return (0.0);
	i = 0.0;
	while (i * i < nb)
		i++;
	return (i * i == nb ? i : 0.0);
}

void	equation::setDiscriminant()
{
	discriminant = (b * b) -  4 * a * c;
}

int		equation::solve()
{
	std::regex	contains_x(PATTERN_CONTAINS_X);
	double		tmp;

	if (!a && !b)
	{
		if (c)
			return (-1);
		else if (!std::regex_match(str, contains_x))
			return (0);
		else
			return (SOLUTION_INFINITE);
	}
	if (!a)
	{
		if (b != 0)
			x1 = -c / b ;
		return (1);
	}
	else
	{
		setDiscriminant();
		if (discriminant == 0)
		{
			x1 = -b / (2 * a);
			return (1);
		}
		else if (discriminant < 0)
			discriminant *= -1;
		tmp = sqrt(discriminant);
		x1 = (-b - tmp) / (2 * a);
		x2 = (-b + tmp) / (2 * a);
		return (2);
	}
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
