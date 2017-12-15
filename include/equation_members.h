/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_members.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:10:10 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/15 14:41:03 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_MEMBERS_H
# define EQUATION_MEMBERS_H

#include "fraction.h"

class equation_member
{
	public:
		equation_member(double coef, int power)
		{
			this->coef = coef;
			this->power = power;
			next = (equation_member*)0;
		}
		double			coef;
		int				power;
		equation_member	*next;
};

class	equation_members
{
	public:
		equation_members();
		equation_member	*list;

		void			add(double coef, int power);
		void			clean();
		int				get_biggest_power();
		double			get_coef(int power);
};

#endif
