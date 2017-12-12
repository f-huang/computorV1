/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:50:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/12 18:12:00 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

#include <string>

class	equation
{
	public:
		equation(const char *av);

		struct	Member
		{
			double	coef;
			int		power;
		};

		bool	isCorrect();
		int		solve();
		double	sqrt(double nb);

		int			degree;
		double		x1;
		double		x2;
		double		discriminant;
		double		a;
		double		b;
		double		c;

	private:
		enum	EquationSide { LEFT, RIGHT };

		bool	parse();
		void	findDegree(std::string str);
		void	setVariables(std::string str, bool negative, enum EquationSide side);
		void	setDiscriminant();

		std::string	str;
};

#endif
