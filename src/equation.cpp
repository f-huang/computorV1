/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:47:53 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/19 18:13:16 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstring>
#include <regex>
#include "computor.h"
#include "equation.h"
#include "ft_math.h"

#define END_PATTERN "([\\+\\-\\=]|$)"
#define PATTERN_EQUATION "(\\-?"X_NUMBER"|"DOUBLE_NUMBER" *\\* *"X_NUMBER"|"DOUBLE_NUMBER"|"DOUBLE_NUMBER""X_NUMBER") *"END_PATTERN

#define PATTERN_CONTAINS_X ".*[xX]+.*"
#define PATTERN_NO_DEGREE ".*[xX]\\^0.*"
#define PATTERN_FIRST_DEGREE "(.*[xX]\\^1.*|.*[xX]"END_PATTERN")"
#define PATTERN_SECOND_DEGREE ".*[xX]\\^2.*"

#define DEBUG_DELTA "∆ = b² - 4ac"
#define DEBUG_FIRST_DEGREE "\tx = "UNDERLINE"-c\n\t"NO_UNDERLINE"     b"
#define DEBUG_X "\tx1 = "UNDERLINE"-b - √∆"NO_UNDERLINE"    x2 = "UNDERLINE"-b + √∆"NO_UNDERLINE"\n\t        2a             2a"
#define DEBUG_X0 "\tx = "UNDERLINE"-b"NO_UNDERLINE"\n\t    2a"
#define DEBUG_CANNOT_SOLVE_DEGREE "Only solve equations of degree 0, 1 or 2."
#define DEBUG_ERROR "Encountered an error."
#define DEBUG_NO_SOLUTION "No solution possible."
#define DEBUG_INFINITE "There is an infinity of solution for this equation."

equation::equation(const char *av, bool debug = false)
{
	std::string::iterator	end;

	str = av;
	end = std::remove(str.begin(), str.end(), ' ');
	str.erase(end, str.end());
	this->debug = debug;
	s_x1 = "";
	s_x1 = "";
	degree = 0;
	discriminant = UNDEFINED;
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

void	equation::do_debug()
{
	fraction	a = members.get_coef(2);
	fraction	b = members.get_coef(1);
	fraction	c = members.get_coef(0);
	int			tmp;

	std::cout << DEBUG_TITLE << std::endl <<
	"\ta = " << a.to_string() << "; b = " << b.to_string() << "; c = " << c.to_string() << std::endl;
	if (degree == 2)
	{
		std::cout <<
		"\t"DEBUG_DELTA << std::endl <<
		"\t∆ = " << b.to_string() << "² - 4 * " << a.to_string() << " * " << c.to_string() << std::endl <<
		"\t∆ = " << (b * b).to_string() << " - " << ((4 * a) * c).to_string() << " = "BOLD << discriminant << NO_BOLD << std::endl <<
		"And:\n" << (discriminant != 0 ? DEBUG_X : DEBUG_X0) << std::endl <<
		"So:\n\tx1 = "UNDERLINE"-" << b.to_string() << " - √" << discriminant << NO_UNDERLINE <<
		"\n\t      2 * " << a.to_string() << std::endl;
		if (discriminant != 0)
			std::cout << "\tx2 = "UNDERLINE"-" << b.to_string() << " + √" << discriminant << NO_UNDERLINE <<
			"\n\t      2 * " << a.to_string() << std::endl;
	}
	else if (degree == 1)
	{
		std::cout <<
		""DEBUG_FIRST_DEGREE << std::endl <<
		"\tx = "UNDERLINE"-" << c.to_string() << NO_UNDERLINE << "\n\t" << "     " << b.to_string() << std::endl;
	}
	else if (degree == 0)
	{
		tmp = solve_degree_zero(str, c.get_value());
		if (tmp == SOLUTION_ERROR)
			std::cout << DEBUG_ERROR << std::endl;
		else if (tmp == SOLUTION_NONE)
			std::cout << DEBUG_NO_SOLUTION << std::endl;
		else
			std::cout << DEBUG_INFINITE << std::endl;
	}
	else
		std::cout << DEBUG_CANNOT_SOLVE_DEGREE << std::endl;
	std::cout << "\n";
}

static void	find_power(std::string str, int *power)
{
	int			pos;
	int			nb;

	if (*power == -1 && (pos = str.find('^')) != std::string::npos)
	{
		nb = std::stoi(str.substr(pos + 1));
		*power = nb;
	}
}

bool	equation::set_variables(std::string str, bool negative, enum e_equation_side side)
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
	if (std::isdigit(str.front()) || str.front() == '+' || str.front() == '-')
	{
		if (str.front() == '-' && !std::isdigit(str[1]))
			nb = -1.0;
		else if (((!std::isdigit(str.front()) && std::isdigit(str[1])) ||
			std::isdigit(str.front())) && (nb = std::stod(str)) == 0.0)
			return (true);
	}
	if (nb > 2147483647 || nb < -2147483648)
		return (false);
	if (negative)
		nb *= -1;
	if (side == RIGHT)
		nb *= -1;
	find_power(str, &power);
	fraction tmp = fraction(nb);
	members.add(tmp, power);
	return (true);
}

bool	equation::parse()
{
	std::regex			pattern1(PATTERN_EQUATION);
	std::regex_iterator<std::string::iterator>	iterator(str.begin(), str.end(), pattern1);
	std::regex_iterator<std::string::iterator>	end;

	size_t				len;
	bool				negative;
	enum e_equation_side	side;

	len = 0;
	negative = false;
	side = LEFT;
	while (iterator != end)
	{
		if (!set_variables(iterator->str(), negative, side))
			return (false);
		switch (iterator->str().back())
		{
			case '=' :
				if (side == RIGHT)
					return (false);
				side = RIGHT;
				negative = false;
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
	degree = members.get_biggest_power();
	return (str.back() != '-' && str.back() != '+' && str.back() != '=' &&
		len == str.length());
}

bool	equation::is_correct()
{
	int		pos;

	if ((pos = str.find('=')) == std::string::npos || pos + 1 == str.length())
		return (false);
	return (equation::parse());
}

void	equation::solve_two_solutions(fraction a, fraction b, fraction c)
{
	double		sqrt_value = ft_math::sqrt(ft_math::abs(discriminant));
	std::string	delta = ft_math::double_to_string(ft_math::abs(discriminant), 2);
	fraction	f_sqrt(sqrt_value);
	fraction	bot(2 * a);
	fraction	top_left(-b);
	fraction	left = top_left / bot;

	if (ft_math::remainder(sqrt_value, 1.0) == 0.0)
	{
		s_x1 = ((top_left - fraction(sqrt_value)) / (bot)).to_string() + (discriminant < 0 ? "i" : "");
		s_x2 = ((top_left + fraction(sqrt_value)) / (bot)).to_string() + (discriminant < 0 ? "i" : "");
	}
	else
	{
		std::string	str_bot = bot.to_string();
		if (str_bot.find('/') != std::string::npos)
			str_bot = "(" + str_bot + ")";
		if (left.denominator != bot.get_value())
		{
			s_x1 = (top_left / bot).to_string() + " - " + (discriminant < 0 ? "i" : "") + "√" + delta + " / " + str_bot;
			s_x2 = (top_left / bot).to_string() + " + " + (discriminant < 0 ? "i" : "") + "√" + delta + " / " + str_bot;
		}
		else
		{
			s_x1 = "(" + std::to_string(top_left.numerator) + " - " + (discriminant < 0 ? "i" : "") + "√" + delta + ") / " + str_bot;
			s_x2 = "(" + std::to_string(top_left.numerator) + " + " + (discriminant < 0 ? "i" : "") + "√" + delta + ") / " + str_bot;
		}
	}
	x2 = (top_left + f_sqrt) / bot;
	x1 = (top_left - f_sqrt) / bot;
}

bool	equation::is_overflowing()
{
	double	a = members.get_coef(2).get_value();
	double	b = members.get_coef(1).get_value();
	double	c = members.get_coef(0).get_value();
	double	tmp = 4 * a * c;

	return (
		b > 46430 || b < -46430 ||
		tmp > 2147483647 ||
		tmp < -2147483648
	);
}

int		equation::solve()
{
	int			ret;
	fraction	a = members.get_coef(2);
	fraction	b = members.get_coef(1);
	fraction	c = members.get_coef(0);

	if (is_overflowing())
		return (SOLUTION_OVERFLOW);
	switch (degree)
	{
		case 0:
			ret = solve_degree_zero(str, c.get_value());
			break ;
		case 1:
			x1 = -c / b;
			s_x1 = x1.to_string();
			ret = SOLUTION_ONE;
			break ;
		case 2:
			discriminant = ft_math::calculate_discriminant(a.get_value(), b.get_value(), c.get_value());
			if (discriminant != 0)
			{
				solve_two_solutions(a, b, c);
				ret = SOLUTION_TWO;
			}
			else
			{
				x1 = (-b / (2 *a));
				s_x1 = x1.to_string();
				ret = SOLUTION_ONE;
			}
			break ;
		default:
			ret = SOLUTION_CANNOT_SOLVE_DEGREE;
			break ;
	}
	debug ? do_debug() : (void)debug;
	return (ret);
}

std::string		equation::get_reduced_form()
{
	equation_member	*iterator;
	std::string		ret;
	double			abs_coef;

	iterator = members.list;
	if (!iterator)
		ret += "0";
	while (iterator)
	{
		abs_coef = ft_math::abs(iterator->coef.get_value());
		if (!ret.length())
		{
			if (iterator->coef.get_value() < 0)
				ret += "-";
		}
		else
			ret += iterator->coef.get_value() < 0 ? " - " : " + ";
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
