/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/06 17:55:45 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "computor.h"
#include "Equation.h"
using namespace std;

#define ERROR_FORMAT	PROGRAM_NAME": Not well formatted"
#define ERROR_USAGE PROGRAM_NAME": illegal arguments\nusage: computor <equation>"

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		cerr << ERROR_USAGE << endl;
		return (1);
	}

	Equation	equation(av[1]);
	if (!equation.isWellFormatted())
	{
		cerr << ERROR_FORMAT << endl;
		return (1);
	}
	return (0);
}
