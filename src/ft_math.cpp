/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:21:29 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/14 16:51:49 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ft_math.h"

static bool	closeEnough(double a, double b) {
	return (ft_math::abs(a - b) < .001);
}

static double	betterGuess(double x, double g) {
	return ((g + x/g) / 2);
}

static double	test(double x, double g) {
	if (closeEnough(x/g, g))
		return (g);
	else
		return (test(x, betterGuess(x, g)));
}

double	ft_math::sqrt(double nb)
{
	return test(nb, 1);
}

double	ft_math::abs(double nb)
{
	return (nb >= 0 ? nb : (nb * -1.0));
}

double	ft_math::fmod(double a, double b)
{
	return (a - b * (int)(a / b));
}

double	ft_math::calculateDiscriminant(double a, double b, double c)
{
	return (b * b  - 4 * a * c);
}

std::string	ft_math::double_to_string(double nb, int precision = 2)
{
	std::string	tmp;
	int			pos;

	if (fmod(nb, 1) == 0.0)
		return (std::to_string((int)nb));
	tmp = std::to_string(nb);
	pos = tmp.find('.') + 1;
	return (tmp.substr(0, pos + precision));
}

static int	count_precision(std::string number)
{
	int		pos;

	if ((pos = number.find('.')) != std::string::npos)
	{
		return (number.substr(pos + 1).length());
	}
	return (0);
}

std::string	ft_math::reduce(double numerator, double denominator)
{
	std::string	ret;
	int		numbers[] = {10000, 1000, 500, 100, 60, 50, 40, 20, 15, 10, 9, 6, 5, 4, 3, 2};
	double	tmp1;
	double	tmp2;

	for (int i = 0; i < 16; i++)
	{
		tmp1 = fmod(numerator, numbers[i]);
		if (!tmp1)
		{
			tmp2 = fmod(denominator, numbers[i]);
			if (!tmp2)
			{
				numerator /= numbers[i];
				denominator /= numbers[i];
				i = 0;
			}
		}
	}
	if (denominator == 0)
		return ("0");
	return (count_precision(std::to_string(numerator / denominator)) > 2 ?
		double_to_string(numerator).append("/").append(double_to_string(denominator)) : double_to_string(numerator/denominator));
}
