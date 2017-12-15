/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_members.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:10:10 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/15 17:24:38 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_MEMBERS_H
# define EQUATION_MEMBERS_H

#include "fraction.h"

class equation_member
{
	public:
		equation_member(fraction& coef, const int power)
		{
			this->coef = coef;
			this->power = power;
			next = (equation_member*)0;
		}
		fraction		coef;
		int				power;
		equation_member	*next;
};

class	equation_members
{
	public:
		equation_members();
		equation_member	*list;

		void			add(fraction& coef, const int power);
		void			clean();
		int				get_biggest_power();
		fraction		get_coef(int power);
};

#endif
