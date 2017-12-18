/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:33:29 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/18 15:52:28 by fhuang           ###   ########.fr       */
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
		std::string	to_string();

		fraction		operator+=(const fraction& nb);
		fraction		operator-=(const fraction& nb);
		fraction		operator*=(const fraction& nb);
		fraction		operator/=(const fraction& nb);
		// fraction&		operator=(fraction& other);
		fraction&		operator=(fraction other);
		fraction&		operator-();

		long	numerator;
		long	denominator;
	private:
		void	swap(fraction& other);
		void	init_fraction(long numerator, long denominator);
		void	init_fraction_double(double numerator, double denominator);
		void	init_fraction_div(std::string str);
};

inline fraction	operator+(fraction a, const fraction& b);
inline fraction	operator-(fraction a, const fraction& b);
inline fraction	operator*(fraction a, const fraction& b);
inline fraction	operator*(long a, const fraction& b);
inline fraction	operator/(fraction a, const fraction& b);

inline fraction	operator+(fraction a, const fraction& b)
{
	a += b;
	return (a);
}


inline fraction	operator-(fraction a, const fraction& b)
{
	a -= b;
	return (a);
}

inline fraction	operator*(fraction a, const fraction& b)
{
	a *= b;
	return (a);
}

inline fraction	operator*(long a, const fraction &b)
{
	fraction	tmp(a);

	tmp *= b;
	return (tmp);
}

inline fraction	operator/(fraction a, const fraction& b)
{
	a /= b;
	return (a);
}

#endif
