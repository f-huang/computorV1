/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/09 20:20:12 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "computor.h"
#include "equation.h"

#define ERROR_FORMAT PROGRAM_NAME": Not well formatted"
#define ERROR_USAGE  PROGRAM_NAME": illegal arguments\nusage: computor <equation>"
#define ERROR_SOLVING PROGRAM_NAME": Cannot solve"
#define NO_SOLUTION PROGRAM_NAME": No solution"
#define ONE_SOLUTION PROGRAM_NAME": One solution : "
#define TWO_SOLUTIONS PROGRAM_NAME": Two solutions : "
#define INFINITE_SOLUTIONS PROGRAM_NAME": Infinite solutions"

static void	explain_results(equation equation, int result)
{
	switch (result)
	{
		case -1 :
			std::cout << ERROR_SOLVING << std::endl;
			break ;
		case 0 :
			std::cout << NO_SOLUTION << std::endl;
			break ;
		case 1 :
			std::cout << ONE_SOLUTION << equation.x1 << "; " << std::endl;
			break ;
		case 2 :
			std::cout << TWO_SOLUTIONS << equation.x1 << "; "<< equation.x2 << std::endl ;
			if (equation.discriminant < 0)
				std::cout << "Complexe" << std::endl;
			break ;
		case SOLUTION_INFINITE :
			std::cout << INFINITE_SOLUTIONS << std::endl;
			break ;
	}
}

static void	print_equation(equation equation)
{
	std::string	discriminant_type;

	if (equation.discriminant == 0)
		discriminant_type = "nul";
	else if (equation.discriminant < 0)
		discriminant_type = "negative";
	else
		discriminant_type = "positive";
	std::cout << "Reduced form: ";
	if (equation.c)
		std::cout << equation.c << "* X ^ 0 ";
	if (equation.b)
		std::cout << equation.b << "* X ^ 1 ";
	if (equation.a)
		std::cout << equation.b << "* X ^ 2 ";
	std::cout << "= 0" << std::endl;
	if (equation.a)
		std::cout << "Discriminant is " << discriminant_type << ", solutions are: ";
	else
		std::cout << "Only one solution : " ;
	std::cout << equation.x1;
	if (equation.discriminant != 0)
	std::cout << " and "<< equation.x2 << std::endl;

}

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << ERROR_USAGE << std::endl;
		return (1);
	}

	equation	equation(av[1]);
	int			result;
	if (!equation.isCorrect())
	{
		std::cerr << ERROR_FORMAT << std::endl;
		return (1);
	}
	result = equation.solve();
	print_equation(equation);
	explain_results(equation, result);
	return (0);
}
