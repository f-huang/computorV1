/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:35:39 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/15 18:23:48 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <regex>
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
	// std::cout << this->numerator <<  "/" << this->denominator << std::endl;
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
	init_fraction_double(numerator, 1.0);
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

int		fraction::get_gcd()
{
	return (ft_math::gcd(numerator, denominator));
}

double	fraction::get_value()
{
	if (denominator == 0)
		throw std::string(EXCEPTION_PARAMETERS);
	return (numerator ? numerator / denominator : 0.0);
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
	else if (numerator < 0 || denominator < 0)
	{
		numerator = -(ft_math::abs(denominator));
		denominator = ft_math::abs(denominator);
	}
}

void	fraction::swap(fraction& other)
{
	std::swap(this->numerator, other.numerator);
	std::swap(this->denominator, other.denominator);
}

fraction&	fraction::operator=(fraction& other)
{
	this->swap(other);
	return (*this);
}

fraction	fraction::plus(fraction a)
{
	fraction	ret = fraction(a.numerator, a.denominator);

	if (ret.denominator != a.denominator)
	{
		ret.denominator *= a.denominator;
		ret.numerator *= a.denominator;
		a.denominator *= ret.denominator;
		a.numerator *= ret.denominator;
	}
	ret.numerator += a.numerator;
	ret.reduce();
	// std::cout << a.numerator << " / " << a.denominator << std::endl;
	std::cout << ret.numerator << " / " << ret.denominator << std::endl;
	return (ret);
}

fraction	fraction::operator+=(const double& nb)
{
	return (plus(fraction(nb)));
}


fraction	fraction::operator+=(const long& nb)
{
	return (plus(fraction(nb)));
}

fraction	fraction::operator+=(const fraction& nb)
{
	return (plus(nb));
}

void	fraction::minus(fraction a)
{
	if (this->denominator != a.denominator)
	{
		this->denominator *= a.denominator;
		this->numerator *= a.denominator;
		a.denominator *= this->denominator;
		a.numerator *= this->denominator;
	}
	this->numerator -= a.numerator;
	this->reduce();
}

void	fraction::operator-=(const double& nb)
{
	minus(fraction(nb));
}


void	fraction::operator-=(const long& nb)
{
	minus(fraction(nb));
}

void	fraction::operator-=(const fraction& nb)
{
	minus(nb);
}


void	fraction::div(fraction a)
{
	this->numerator *= a.denominator;
	this->denominator *= a.numerator;
	this->reduce();
}

void	fraction::operator/=(const double& nb)
{
	div(fraction(nb));
}


void	fraction::operator/=(const long& nb)
{
	div(fraction(nb));
}

void	fraction::operator/=(const fraction& nb)
{
	div(nb);
}

void	fraction::multiply(fraction a)
{
	this->numerator *= a.numerator;
	this->denominator *= a.denominator;
	this->reduce();
}

void	fraction::operator*=(const double& nb)
{
	multiply(fraction(nb));
}


void	fraction::operator*=(const long& nb)
{
	multiply(fraction(nb));
}

void	fraction::operator*=(const fraction& nb)
{
	multiply(nb);
}


void	fraction::negative()
{
	this->numerator *= -1;
	this->reduce();
}

void	fraction::operator-()
{
	negative();
}
