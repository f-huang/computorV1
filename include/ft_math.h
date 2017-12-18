/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:21:56 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/18 17:58:52 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH
# define FT_MATH

#define DOUBLE_NUMBER "-?\\d+(\\.\\d+)?"
#define FRACTION_NUMBER DOUBLE_NUMBER" */ *"DOUBLE_NUMBER
#define X_NUMBER "[xX] *(\\^ *\\d+)?"

class	ft_math
{
	public:

		static double		sqrt(double nb);
		static double		abs(double nb);
		static double		fmod(double a, double b);
		static double		remainder(double a, double b);
		static double		calculate_discriminant(double a, double b, double c);
		static long			abs(long nb);
		static long			pow(long nb, unsigned long power);
		static int			gcd(long a, long b);
		static int			count_precision(double nb);
		static bool			equals(double a, double b);
		static bool			is_digit(const std::string &str);
		static std::string	reduce(double numerator, double denominator);
		static std::string	double_to_string(double nb, int precision);
};

#endif
