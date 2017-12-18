/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:21:29 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/18 18:20:07 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ft_math.h"

double	ft_math::sqrt(double nb)
{
	double	res;
	double	x;
	int		i;

	if (nb < 1)
		return (1);
	i = -1;
	x = 1;
	while (++i < 100)
	{
		res = (x + (nb / x)) / 2;
		x = res;
	}
	return (res);
}

double	ft_math::abs(double nb)
{
	return (nb >= 0 ? nb : (nb * -1.0));
}

long	ft_math::abs(long nb)
{
	return (nb >= 0 ? nb : (nb * -1L));
}

double	ft_math::fmod(double a, double b)
{
	if (((int)a / b) == 0)
		return (-1.0);
	return (a - b * (int)(a / b));
}

int		ft_math::gcd(long a, long b)
{
	a = abs(a);
	b = abs(b);
	while (a && b && a != b)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return (a);
}

double	ft_math::remainder(double a, double b)
{
	return (a - ((int)(a / b) * b));
}

double	ft_math::calculate_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
}

bool	ft_math::equals(double a, double b)
{
	a = ((abs(a - (int)a)) < 0.0001) ? (int)a : a;
	b = ((abs(b - (int)b)) < 0.0001) ? (int)b : b;
	return (a == b);
}

bool	ft_math::is_digit(const std::string &str)
{
	return ((std::isdigit(str.front()) || str.front() == '+' || str.front() == '-')
		&& std::all_of(str.begin() + 1, str.end(), ::isdigit));
}

std::string	ft_math::double_to_string(double nb, int precision = 2)
{
	std::string	tmp;
	int			pos;

	if (equals(remainder(nb, 1), 0.0))
		return (std::to_string((int)nb));
	tmp = std::to_string(nb);
	pos = tmp.find('.') + 1;
	return (tmp.substr(0, pos + precision));
}

int		ft_math::count_precision(double nb)
{
	int		ret = 0;

	nb = abs(nb);
	while (!equals(remainder(nb, 1), 0.0))
	{
		nb *= 10;
		ret++;
	}
	return (ret);
}

long	ft_math::pow(long nb, unsigned long power)
{
	int tmp;

	if (power == 0)
		return (1);
	tmp = pow(nb, power / 2);
	if (power % 2 == 0)
		return (tmp * tmp);
	else
		return (nb * tmp * tmp);
}
