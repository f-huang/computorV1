/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:50:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/19 16:05:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

#include <string>
#include "equation_members.h"

class	equation
{
	public:
		equation(const char *av, bool debug);

		bool			is_correct();
		int				solve();
		std::string		get_reduced_form();

		equation_members	members;
		std::string		s_x1;
		std::string		s_x2;
		fraction		x1;
		fraction		x2;
		bool			debug;
		double			discriminant;
		int				degree;

	private:
		enum	e_equation_side { LEFT, RIGHT };

		bool	parse();
		void	do_debug();
		bool	is_overflowing();
		bool	set_variables(std::string str, bool negative, enum e_equation_side side);
		void	solve_two_solutions(fraction a, fraction b, fraction c);
		void	set_discriminant();

		std::string	str;
};

#endif
