/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:21:56 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/12 18:35:45 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH
# define FT_MATH

class	ft_math
{
	public:

		static double	sqrt(double nb);
		static double	abs(double nb);
		static double	fmod(double a, double b);
		static double	calculateDiscriminant(double a, double b, double c);
		static std::string	reduce(double numerator, double denominator);
};

#endif
