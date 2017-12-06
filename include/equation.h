/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:50:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/06 18:50:03 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

#include <string>

using namespace std;

class	equation
{
	public:
		equation(const char *av);
		bool	isCorrect();
	private:
		string	str;
		int		a;
		int		b;
		int		c;

		bool	parse();
};

/*
**		ax2 + bx + c = 0
**		/_\ = b2 - 4ac
**		x1 = (-b - √/_\) / 2a
**		x2 = (-b + √/_\) / 2a
*/
#endif
