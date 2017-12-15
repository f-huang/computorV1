/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:21:29 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/15 17:24:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ft_math.h"

static bool	close_enough(double a, double b) {
	return (ft_math::abs(a - b) < .001);
}

static double	better_guess(double x, double g) {
	return ((g + x/g) / 2);
}

static double	test(double x, double g) {
	if (close_enough(x/g, g))
		return (g);
	else
		return (test(x, better_guess(x, g)));
}

double	ft_math::sqrt(double nb)
{
	return test(nb, 1);
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
	return ((b * b)  - (4 * a * c));
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

std::string	ft_math::reduce(double numerator, double denominator)
{
	static int	numbers[] = {10000, 1000, 500, 100, 60, 50, 40, 20, 15, 10, 9, 6, 5, 4, 3, 2};
	int			i;
	std::string	ret;
	double		tmp1;
	double		tmp2;

	i = -1;
	while (++i < 16 && !equals(numerator, 0.0) && !equals(denominator, 0.0) && !equals(denominator, 1.0))
	{
		tmp1 = remainder(numerator, numbers[i]);
		if (equals(tmp1, 0.0))
		{
			tmp2 = remainder(denominator, numbers[i]);
			if (equals(tmp2, 0.0))
			{
				numerator /= numbers[i];
				denominator /= numbers[i];
				i = 0;
			}
		}
	}
	numerator = (equals(remainder(numerator, 1), 0.0)) ? (int)numerator : numerator;
	denominator = (equals(remainder(denominator, 1), 0.0)) ? (int)denominator : denominator;
	if (numerator < 0 && denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
	if (numerator == 0.0 || denominator == 0.0)
		return ("0");
	else if (denominator == 1.0)
		return (double_to_string(numerator));
	return (count_precision(numerator / denominator) > 2 ?
		double_to_string(numerator).append("/").append(double_to_string(denominator)) : double_to_string(numerator/denominator));
}
