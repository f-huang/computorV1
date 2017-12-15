/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:35:39 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/15 14:36:45 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
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
	std::cout << this->numerator <<  "/" << this->denominator << std::endl;
}

fraction::fraction(long numerator, long denominator)
{
	init_fraction(numerator, denominator);
}

fraction::fraction(double numerator, double denominator)
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

fraction::fraction(std::string str)
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

int		fraction::get_gcd()
{
	return (ft_math::gcd(numerator, denominator));
}
//
// fraction	fraction::reduce()
// {
// 	long	numerator;
// 	long	denominator;
// }
