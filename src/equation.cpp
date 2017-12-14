/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:47:53 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/14 20:36:44 by fhuang           ###   ########.fr       */
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
	x1 = "";
	x2 = "";
	degree = 0;
}

static void	findPower(std::string str, int *power)
{
	int			pos;
	int			nb;

	if (*power == -1 && (pos = str.find('^')) != std::string::npos)
	{
		nb = std::stoi(str.substr(pos + 1));
		*power = nb;
	}
}

void	equation::setVariables(std::string str, bool negative, enum EquationSide side)
{
	std::regex	contains_x(PATTERN_CONTAINS_X);
	std::regex	is_no_degree(PATTERN_NO_DEGREE);
	std::regex	is_first_degree(PATTERN_FIRST_DEGREE);
	std::regex	is_second_degree(PATTERN_SECOND_DEGREE);
	double		nb;
	int			power;

	nb = 1.0;
	power = -1;
	if (!std::regex_match(str, contains_x) || std::regex_match(str, is_no_degree))
		power = 0;
	else if (std::regex_match(str, is_first_degree))
		power = 1;
	else if (std::regex_match(str, is_second_degree))
		power = 2;
	if (std::isdigit(str.front()) || str.front() == '-' || str.front() == '+')
		if ((nb = std::stod(str)) == 0.0)
			return ;
	if (negative)
		nb *= -1;
	if (side == RIGHT)
		nb *= -1;
	findPower(str, &power);
	members.add(nb, power);
	// std::cout << str << " : " << nb << " <--> " << power << std::endl;
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
	members.clean();
	degree = members.getBiggestPower();
	return (len == str.length());
}

bool	equation::isCorrect()
{
	int		pos;

	if ((pos = str.find('=')) == std::string::npos || pos + 1 == str.length())
		return (false);
	return (equation::parse());
}

static int	solve_degree_zero(std::string str, double c)
{
	std::regex	contains_x(PATTERN_CONTAINS_X);

	if (c)
		return (SOLUTION_ERROR);
	else if (!std::regex_match(str, contains_x))
		return (SOLUTION_NONE);
	else
		return (SOLUTION_INFINITE);
}

int		equation::solve()
{
	int			ret;
	double		tmp;
	double		a = members.getCoef(2);
	double		b = members.getCoef(1);
	double		c = members.getCoef(0);

	std::cout << "a = " << a << "; b = " << b << "; c = " << c << std::endl;
	switch (degree)
	{
		case 0:
			ret = solve_degree_zero(str, c);
			break ;
		case 1:
			x1 = ft_math::reduce(-c, b);
			ret = SOLUTION_ONE;
			break ;
		case 2:
			discriminant = ft_math::calculateDiscriminant(a, b, c);
			std::cout << "Discriminant = " << discriminant << std::endl;
			if (discriminant != 0)
			{
				tmp = ft_math::sqrt(ft_math::abs(discriminant));
				x1 = ft_math::reduce(-b - tmp, 2 * a);
				x2 = ft_math::reduce(-b + tmp, 2 * a);
				ret = SOLUTION_TWO;
			}
			else
			{
				x1 = ft_math::reduce(-b, 2 * a);
				ret = SOLUTION_ONE;
			}
			break ;
		default:
			ret = SOLUTION_CANNOT_SOLVE_DEGREE;
			break ;
	}
	return (ret);
}

std::string		equation::getReducedForm()
{
	EquationMember	*iterator;
	std::string		ret;
	double			abs_coef;

	iterator = members.list;
	while (iterator)
	{
		abs_coef = ft_math::abs(iterator->coef);
		if (!ret.length())
		{
			if (iterator->coef < 0)
				ret += "-";
		}
		else
			ret += iterator->coef < 0 ? " - " : " + ";
		if (abs_coef > 1 || iterator->power == 0)
			ret += ft_math::double_to_string(abs_coef, 2);
		if (iterator->power)
			ret += "x";
		if (iterator->power > 1)
		{
			ret += "^";
			ret += std::to_string(iterator->power);
		}
		iterator = iterator->next;
	}
	ret += " = 0";
	return (ret);
}
