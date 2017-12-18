/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:35:39 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/18 13:07:44 by fhuang           ###   ########.fr       */
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
	return (ret);
}

fraction	fraction::operator+(const double& nb) { return (plus(fraction(nb))); }
fraction	fraction::operator+(const long& nb) { return (plus(fraction(nb))); }
fraction	fraction::operator+(const fraction& nb) { return (plus(nb)); }

fraction	fraction::operator-(const double& nb) { return (minus(fraction(nb))); }
fraction	fraction::operator-(const long& nb) { return (minus(fraction(nb))); }
fraction	fraction::operator-(const fraction& nb) { return (minus(nb)); }

void	fraction::operator+=(const double& nb)
{
	fraction	tmp = plus(fraction(nb));
	*this = tmp;
}


void	fraction::operator+=(const long& nb)
{
	fraction	tmp = plus(fraction(nb));
	*this = tmp;
}

void	fraction::operator+=(const fraction& nb)
{
	fraction	tmp = plus(nb);
	*this = tmp;
}

fraction	fraction::minus(fraction a)
{
	fraction	ret = fraction(a.numerator, a.denominator);

	if (ret.denominator != a.denominator)
	{
		ret.denominator *= a.denominator;
		ret.numerator *= a.denominator;
		a.denominator *= ret.denominator;
		a.numerator *= ret.denominator;
	}
	ret.numerator -= a.numerator;
	ret.reduce();
	return (ret);
}

void	fraction::operator-=(const double& nb)
{
	fraction	tmp = minus(fraction(nb));
	*this = tmp;
}


void	fraction::operator-=(const long& nb)
{
	fraction	tmp = minus(fraction(nb));
	*this = tmp;
}

void	fraction::operator-=(const fraction& nb)
{
	fraction	tmp = minus(nb);
	*this = tmp;
}

fraction	fraction::divide(fraction a)
{
	fraction	ret = fraction(a.numerator, a.denominator);

	ret.numerator *= a.denominator;
	ret.denominator *= a.numerator;
	ret.reduce();
	return (ret);
}

void	fraction::operator/=(const double& nb)
{
	fraction	tmp = divide(fraction(nb));
	*this = tmp;
}


void	fraction::operator/=(const long& nb)
{
	fraction	tmp = divide(fraction(nb));
	*this = tmp;
}

void	fraction::operator/=(const fraction& nb)
{
	fraction	tmp = divide(nb);
	*this = tmp;
}

fraction	fraction::multiply(fraction a)
{
	fraction	ret = fraction(a.numerator, a.denominator);

	ret.numerator *= a.numerator;
	ret.denominator *= a.denominator;
	ret.reduce();
	return (ret);
}

void	fraction::operator*=(const double& nb)
{
	fraction	tmp = multiply(fraction(nb));
	*this = tmp;
}


void	fraction::operator*=(const long& nb)
{
	fraction	tmp = multiply(fraction(nb));
	*this = tmp;
}

void	fraction::operator*=(const fraction& nb)
{
	fraction	tmp = multiply(nb);
	*this = tmp;
}
