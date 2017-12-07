/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:47:53 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/07 12:34:44 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <regex>
#include "equation.h"
using namespace std;

equation::equation(const char *av)
{
	str = av;
}

bool	equation::parse()
{
	regex	pattern("([xX] *\^ *[0-2] *\* *\d|\d *\* *[xX] *(\^ *[0-2])*|\d) *[+-=]");


	return true;
}

bool	equation::isCorrect()
{
	if (str.find('=') == string::npos)
		return false;
	return true;
}

/*

	5 * X^0 + 4 * X^1 + 8 * X^2 = 0
	5 * X^0 * 4 * X^1 + 8 * X^2 = 0
	5 + 4 * X^1 + 8 * X^2 = 0
	5 + 4 * X + 8 * X^2 = 0
*/
