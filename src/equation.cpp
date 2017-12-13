/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:47:53 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/13 18:48:16 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstring>
#include <regex>
#include "computor.h"
#include "equation.h"
#include "ft_math.h"

#define DOUBLE_NUMBER "-?\\d+(\\.\\d+)?"
#define X_NUMBER "[xX] *(\\^ *\\d+)?"
#define END_PATTERN "([\\+\\-\\=]|$)"
#define PATTERN_EQUATION "("X_NUMBER"|"DOUBLE_NUMBER" *\\* *"X_NUMBER"|"DOUBLE_NUMBER"|"DOUBLE_NUMBER" *"X_NUMBER") *"END_PATTERN

#define PATTERN_CONTAINS_X ".*[xX]+.*"
#define PATTERN_NO_DEGREE ".*[xX]\\^0.*"
#define PATTERN_FIRST_DEGREE "(.*[xX]\\^1.*|.*[xX]"END_PATTERN")"
#define PATTERN_SECOND_DEGREE ".*[xX]\\^2.*"

equation::equation(const char *av)
{
	std::string::iterator	end;

	str = av;
	end = std::remove(str.begin(), str.end(), ' ');
	str.erase(end, str.end());
	// a = 0;
	// b = 0;
	// c = 0;
	x1 = 0;
	x2 = 0;
	degree = 0;
}

void	equation::findDegree(std::string str, int *power)
{
	int			pos;
	int			nb;
	std::string	tmp;

	if ((pos = str.find('^')) != std::string::npos)
	{
		nb = std::stoi(str.substr(pos + 1));
		if (nb > degree)
			degree = nb;
		*power = nb;
	}
}

void	equation::setVariables(std::string str, bool negative, enum EquationSide side)
{
	std::regex	contains_x(PATTERN_CONTAINS_X);
	std::regex	is_no_degree(PATTERN_NO_DEGREE);
	std::regex	is_first_degree(PATTERN_FIRST_DEGREE);
	std::regex	is_second_degree(PATTERN_SECOND_DEGREE);
	// double		*dest;
	double		nb;
	int			power;

	nb = 1.0;
	// dest = NULL;
	if (!std::regex_match(str, contains_x) || std::regex_match(str, is_no_degree))
	{
		power = 0;
		// dest = &c;
	}
	else if (std::regex_match(str, is_second_degree))
	{
		power = 2;
		degree = degree < 2 ? 2 : degree;
		// dest = &a;
	}
	else if (std::regex_match(str, is_first_degree))
	{
		power = 1;
		degree = degree < 1 ? 1 : degree;
		// dest = &b;
	}
	else
		findDegree(str, &power);
	if (power >= 0 && power <= 2)
	{
		if (std::isdigit(str.front()))
			nb = std::stod(str);
		if (negative)
			nb *= -1;
		if (side == RIGHT)
			nb *= -1;
		// *dest += nb;
		// std::cout << nb << " & " << power << std::endl;
		members.add(nb, power);
	}
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
	// std::cout << "a = " << a << "; b = " << b << "; c = " << c << std::endl;
	return (len == str.length());
}

bool	equation::isCorrect()
{
	int		pos;

	if ((pos = str.find('=')) == std::string::npos || pos + 1 == str.length())
		return (false);
	return (equation::parse());
}

int		equation::solve()
{
	std::regex	contains_x(PATTERN_CONTAINS_X);
	EquationMember	*found;
	double		tmp;
	double		a;
	double		b;
	double		c;

	if (degree < 0 || degree > 2)
		return (SOLUTION_CANNOT_SOLVE_DEGREE);
	// a = members.find(2);
	// b = members.find(1);
	// c = members.find(0);
	found = members.find(0);
	c = found ? found->coef : 0.0;
	found = members.find(1);
	b = found ? found->coef : 0.0;
	found = members.find(2);
	a = found ? found->coef : 0.0;
	std::cout << "a = " << a << "; b = " << b << "; c = " << c << std::endl;
	if (degree == 0)
	{
		if (members.find(0))
			return (SOLUTION_ERROR);
		else if (!std::regex_match(str, contains_x))
			return (SOLUTION_NONE);
		else
			return (SOLUTION_INFINITE);
	}
	else if (degree == 1)
	{
		x1 = -c / b ;
		return (SOLUTION_ONE);
	}
	else
	{
		discriminant = ft_math::calculateDiscriminant(a, b, c);
		if (discriminant == 0)
		{
			x1 = -b / (2 * a);
			return (SOLUTION_ONE);
		}
		else if (discriminant < 0)
			discriminant = ft_math::abs(discriminant);
		tmp = ft_math::sqrt(discriminant);
		std::cout << "Reducing : "<< ft_math::reduce(-b - tmp, 2 * a) << std::endl;
		// std::cout << discriminant << " -> " << tmp << std::endl;
		x1 = (-b - tmp) / (2 * a);
		x2 = (-b + tmp) / (2 * a);
		return (SOLUTION_TWO);
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
