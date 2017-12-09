/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:50:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/09 19:58:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

#include <string>

class	equation
{
	public:
		equation(const char *av);

		bool	isCorrect();
		int		solve();
		double	sqrt(double nb);

		double		x1;
		double		x2;
		double		discriminant;
		double		a;
		double		b;
		double		c;

	private:
		enum	EquationSide { LEFT, RIGHT };

		bool	parse();
		void	setVariables(std::string str, bool negative, enum EquationSide side);
		void	setDiscriminant();

		std::string	str;
};

/*
**		ax2 + bx + c = 0
**		/_\ = b2 - 4ac
**		x1 = (-b - √/_\) / 2a
**		x2 = (-b + √/_\) / 2a
*/
#endif
