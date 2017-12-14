/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:50:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/14 16:37:00 by fhuang           ###   ########.fr       */
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

		bool			isCorrect();
		int				solve();
		std::string		getReducedForm();

		EquationMembers	members;
		std::string		x1;
		std::string		x2;
		double			discriminant;
		int				degree;

	private:
		enum	EquationSide { LEFT, RIGHT };

		bool	parse();
		void	setVariables(std::string str, bool negative, enum EquationSide side);
		void	setDiscriminant();

		std::string	str;
};

#endif
