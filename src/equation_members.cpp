/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_members.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:18:58 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/14 16:26:02 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <iostream>
#include "equation_members.h"

EquationMembers::EquationMembers()
{
	list = NULL;
}

void	EquationMembers::add(double coef, int power)
{
	EquationMember	*iterator;
	EquationMember	*prev;
	EquationMember	*toAdd = new EquationMember(coef, power);

	iterator = list;
	prev = list;
	while (iterator)
	{
		if (iterator->power > power)
			break ;
		else if (iterator->power == power)
		{
			iterator->coef += coef;
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
	else if (prev->next == NULL)
		prev->next = toAdd;
	else
	{
		toAdd->next = prev->next;
		prev->next = toAdd;
	}
}

double	EquationMembers::getCoef(int power)
{
	EquationMember	*iterator;

	iterator = list;
	while (iterator)
	{
		if (iterator->power == power)
			return (iterator->coef);
		iterator = iterator->next;
	}
	return (0.0);
}

int	EquationMembers::getBiggestPower()
{
	EquationMember	*iterator;

	iterator = list;
	while (iterator && iterator->next)
		iterator = iterator->next;
	return (iterator ? iterator->power : 0);
}

void	EquationMembers::clean()
{
	EquationMember	*iterator;
	EquationMember	*prev;

	iterator = list;
	prev = NULL;
	while (iterator)
	{
		if (iterator->coef == 0.0)
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
