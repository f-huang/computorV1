/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_members.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:10:10 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/13 18:34:21 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_MEMBERS_H
# define EQUATION_MEMBERS_H

class EquationMember
{
	public:
		EquationMember(double coef, int power)
		{
			this->coef = coef;
			this->power = power;
			next = (EquationMember*)0;
		}
		double			coef;
		int				power;
		EquationMember	*next;
};

class	EquationMembers
{
	public:
		EquationMembers();
		EquationMember	*list;

		void			add(double coef, int power);
		EquationMember	*find(int power);
};

#endif
