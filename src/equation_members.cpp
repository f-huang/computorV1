/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_members.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:18:58 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/18 15:29:14 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <iostream>
#include "equation_members.h"

equation_member::equation_member(fraction& coef, const int power)
{
	this->coef = fraction(coef);
	this->power = power;
	this->next = (equation_member*)0;
}

equation_members::equation_members()
{
	list = NULL;
}

void	equation_members::add(fraction& coef, const int power)
{
	equation_member	*iterator;
	equation_member	*prev;
	equation_member	*toAdd = new equation_member(coef, power);

	iterator = list;
	prev = list;
	// std::cout << toAdd->coef.numerator << std::endl;
	while (iterator)
	{
		if (iterator->power > power)
			break ;
		else if (iterator->power == power)
		{
			iterator->coef += toAdd->coef;
			return ;
		}
		prev = iterator;
		iterator = iterator->next;
	}
	if (prev == list)
	{
		toAdd->next = list;
		list = toAdd;
	}
	else
	{
		toAdd->next = prev->next;
		prev->next = toAdd;
	}
}

fraction	equation_members::get_coef(int power)
{
	equation_member	*iterator;

	iterator = list;
	while (iterator)
	{
		if (iterator->power == power)
			return (iterator->coef);
		iterator = iterator->next;
	}
	return (fraction());
}

int	equation_members::get_biggest_power()
{
	equation_member	*iterator;

	iterator = list;
	while (iterator && iterator->next)
		iterator = iterator->next;
	return (iterator ? iterator->power : 0);
}

void	equation_members::clean()
{
	equation_member	*iterator;
	equation_member	*prev;

	iterator = list;
	prev = NULL;
	while (iterator)
	{
		if (iterator->coef.get_value() == 0.0)
		{
			if (!prev)
				list = iterator->next;
			else
				prev->next = iterator->next;
		}
		else
			prev = iterator;
		iterator = iterator->next;
	}
}
