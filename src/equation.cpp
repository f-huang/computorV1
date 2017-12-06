/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:47:53 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/06 18:51:17 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Equation.h"
using namespace std;

equation::equation(const char *av)
{
	str = av;

}

bool	equation::parse()
{
	// regex	pattern("X^\d");
	return true;
}

bool	equation::isCorrect()
{
	return true;
}
