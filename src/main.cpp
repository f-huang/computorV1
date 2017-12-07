/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/07 12:34:17 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "computor.h"
#include "equation.h"
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

	equation	equation(av[1]);
	if (!equation.isCorrect())
	{
		cerr << ERROR_FORMAT << endl;
		return (1);
	}
	return (0);
}
