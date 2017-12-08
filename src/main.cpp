/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/08 15:08:24 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "computor.h"
#include "equation.h"

#define ERROR_FORMAT PROGRAM_NAME": Not well formatted"
#define ERROR_USAGE  PROGRAM_NAME": illegal arguments\nusage: computor <equation>"

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << ERROR_USAGE << std::endl;
		return (1);
	}

	equation	equation(av[1]);
	if (!equation.isCorrect())
	{
		std::cerr << ERROR_FORMAT << std::endl;
		return (1);
	}
	return (0);
}
