/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:33:29 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/15 13:28:03 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTION_H
# define FRACTION_H

#include <iostream>

class	fraction
{
	public:
		fraction(long numerator, long denominator);
		fraction(double numerator, double denominator);
		fraction(std::string str);

		int		get_gcd();

		long	numerator;
		long	denominator;
	private:
		void	init_fraction(long numerator, long denominator);
};

#endif
