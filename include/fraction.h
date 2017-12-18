/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:33:29 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/18 15:11:06 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTION_H
# define FRACTION_H

#include <iostream>

class	fraction
{
	public:
		fraction();
		fraction(double numerator);
		fraction(long numerator);
		fraction(long numerator, long denominator);
		fraction(double numerator, double denominator);
		fraction(std::string str);

		int			get_gcd();
		double		get_value();
		void		reduce();
		// fraction	plus(const fraction &nb);
		// // fraction	plus(fraction &a);
		// fraction	minus(fraction a);
		// fraction	divide(fraction a);
		// fraction	multiply(fraction a);

		fraction		operator+=(const fraction& nb);
		fraction		operator-=(const fraction& nb);
		fraction		operator*=(const fraction& nb);
		fraction		operator/=(const fraction& nb);
		fraction&		operator=(fraction& other);
		friend fraction	operator+(fraction a, const fraction& b);
		friend fraction	operator-(fraction a, const fraction& b);
		friend fraction	operator*(fraction a, const fraction& b);
		friend fraction	operator/(fraction a, const fraction& b);

		long	numerator;
		long	denominator;
	private:
		void	swap(fraction& other);
		void	init_fraction(long numerator, long denominator);
		void	init_fraction_double(double numerator, double denominator);
		void	init_fraction_div(std::string str);
};

#endif
