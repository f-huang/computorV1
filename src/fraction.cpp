/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:35:39 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/19 12:45:53 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <regex>
#include "computor.h"
#include "ft_math.h"
#include "fraction.h"

#define EXCEPTION_TITLE "fraction: "
#define EXCEPTION_PARAMETERS EXCEPTION_TITLE"Invalid parameters."

void	fraction::init_fraction(long numerator, long denominator)
{
	int		neg;
	int		gcd;

	neg = 1;
	this->numerator = 0;
	this->denominator = 0;
	if (denominator == 0)
		throw std::string(EXCEPTION_PARAMETERS);
	if (numerator < 0 && denominator < 0)
		neg = -1;
	if (!(gcd = ft_math::gcd(numerator, denominator)))
		gcd = 1;
	this->numerator = (numerator * neg) / gcd;
	this->denominator = (denominator * neg) / gcd;
}

void	fraction::init_fraction_double(double numerator, double denominator)
{
	long	multiple;
	int		tmp;

	multiple = ft_math::count_precision(numerator);
	tmp = ft_math::count_precision(denominator);
	if (tmp > multiple)
		multiple = tmp;
	multiple = multiple == 0 ? 1 : ft_math::pow(10, multiple);
	init_fraction(numerator * multiple, denominator * multiple);
}

void	fraction::init_fraction_div(std::string str)
{
	int			pos;
	std::string	top;
	std::string	bot;

	pos = str.find('/');
	if (pos == std::string::npos || str.length() == pos + 1 || pos == 0)
		throw std::string(EXCEPTION_PARAMETERS);
	top = str.substr(0, pos);
	bot = str.substr(pos + 1, str.length());
	if (!ft_math::is_digit(top) || !ft_math::is_digit(bot))
		throw std::string(EXCEPTION_PARAMETERS);
	init_fraction(std::stol(top), std::stol(bot));
}

fraction::fraction()
{
	init_fraction(0L, 1L);
}

fraction::fraction(double numerator)
{
	numerator = (double)ft_math::floor(numerator * 10000) / (double)10000.0;
	init_fraction_double(numerator, 1.00);
}

fraction::fraction(long numerator)
{
	init_fraction(numerator, 1L);
}

fraction::fraction(long numerator, long denominator)
{
	init_fraction(numerator, denominator);
}

fraction::fraction(double numerator, double denominator)
{
	init_fraction_double(numerator, denominator);
}

fraction::fraction(std::string str)
{
	std::regex	is_fraction(FRACTION_NUMBER);
	std::regex	is_double(DOUBLE_NUMBER);

	if (std::regex_match(str, is_fraction))
		init_fraction_div(str);
	else if (std::regex_match(str, is_double))
		init_fraction_double(std::stod(str), 1.0);
	else
		throw std::string(EXCEPTION_PARAMETERS);
}

std::string	fraction::to_string()
{
	double		tmp;
	std::string	ret;

	tmp = this->get_value();
	if (ft_math::count_precision(tmp) <= 4)
		return (ft_math::double_to_string(tmp, ft_math::count_precision(tmp)));
	ret = std::to_string(this->numerator);
	if (this->numerator && (this->denominator < 0 || this->denominator > 1))
	{
		ret += " / ";
		ret += std::to_string(this->denominator);
	}
	return (ret);
}

int		fraction::get_gcd()
{
	return (ft_math::gcd(numerator, denominator));
}

double	fraction::get_value()
{
	if (denominator == 0)
		throw std::string(EXCEPTION_PARAMETERS);
	return (numerator ? (double)numerator / (double)denominator : 0.0);
}

void	fraction::reduce()
{
	int		gcd;

	gcd = get_gcd();
	if (gcd == 0)
		gcd = 1;
	numerator = numerator / gcd;
	denominator = denominator / gcd;
	if (numerator < 0 && denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
	else if (numerator < 1 || denominator < 0)
	{
		numerator = -(ft_math::abs(numerator));
		denominator = ft_math::abs(denominator);
	}
}

void	fraction::swap(fraction& other)
{
	std::swap(this->numerator, other.numerator);
	std::swap(this->denominator, other.denominator);
}

fraction&	fraction::operator=(fraction other)
{
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	return (*this);
}

fraction	fraction::operator+=(const fraction& nb)
{
	long	tmp;

	if (this->denominator != nb.denominator)
	{
		tmp = nb.numerator * this->denominator;
		this->denominator *= nb.denominator;
		this->numerator *= nb.denominator;
	}
	else
		tmp = nb.numerator;
	this->numerator += tmp;
	this->reduce();
	return (*this);
}

fraction	fraction::operator-=(const fraction& nb)
{
	long	tmp;

	if (this->denominator != nb.denominator)
	{
		tmp = nb.numerator * this->denominator;
		this->denominator *= nb.denominator;
		this->numerator *= nb.denominator;
	}
	else
		tmp = nb.numerator;
	this->numerator -= tmp;
	this->reduce();
	return (*this);
}

fraction&	fraction::operator-()
{
	this->numerator *= -1;
	this->reduce();
	return (*this);
}


fraction	fraction::operator*=(const fraction& nb)
{
	this->numerator *= nb.numerator;
	this->denominator *= nb.denominator;
	this->reduce();
	return (*this);
}

fraction	fraction::operator/=(const fraction &nb)
{
	this->numerator *= nb.denominator;
	this->denominator *= nb.numerator;
	this->reduce();
	return (*this);
}
