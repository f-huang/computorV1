/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_members.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:18:58 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/13 18:58:10 by fhuang           ###   ########.fr       */
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
	std::cout << "New -> " << coef << "/" << power << std::endl;
	while (iterator)
	{
		if (iterator->power > power)
			break ;``
		else if (iterator->power == power)
		{
			iterator->coef += coef;
			return ;
		}
		prev = iterator;
		std::cout << "o" << std::endl;
		iterator = iterator->next;
	}
	if (prev == list)
	{
		toAdd->next = list;
		list->next = toAdd;
	}
	else if (prev->next == NULL)
		prev->next = toAdd;
	else
	{
		toAdd->next = prev->next;
		prev->next = toAdd;
	}
}

EquationMember	*EquationMembers::find(int power)
{
	EquationMember	*iterator;

	iterator = list;
	while (iterator)
	{
		if (iterator->power == power)
			return (iterator);
		iterator = iterator->next;
	}
	return (NULL);
}
