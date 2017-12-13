/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:50:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/13 18:44:00 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

#include <string>
#include "equation_members.h"

class	equation
{
	public:
		equation(const char *av);

		bool	isCorrect();
		int		solve();
		double	sqrt(double nb);

		EquationMembers	members;
		int			degree;
		double		x1;
		double		x2;
		double		discriminant;
		// double		a;
		// double		b;
		// double		c;

	private:
		enum	EquationSide { LEFT, RIGHT };

		bool	parse();
		void	findDegree(std::string str, int *power);
		void	setVariables(std::string str, bool negative, enum EquationSide side);
		void	setDiscriminant();

		std::string	str;
};

#endif
