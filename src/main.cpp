/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/14 16:32:34 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "computor.h"
#include "equation.h"
#include "ft_math.h"

static void	print_results(equation equation, int result)
{
	std::string	discriminant_type;

	switch (result)
	{
		case SOLUTION_ERROR :
			std::cout << ERROR_SOLVING << std::endl;
			break ;
		case SOLUTION_NONE :
			std::cout << OUTPUT_SOLUTION_NONE << std::endl;
			break ;
		case SOLUTION_ONE :
			std::cout << OUTPUT_SOLUTION_ONE << equation.x1 << "; " << std::endl;
			break ;
		case SOLUTION_TWO :
			if (equation.discriminant < 0)
				discriminant_type = "strictly negative";
			else if (equation.discriminant == 0)
				discriminant_type = "null";
			else
				discriminant_type = "strictly positive";
			std::cout << "Discriminant is " << discriminant_type << OUTPUT_SOLUTION_TWO << equation.x1 << std::endl << equation.x2 << std::endl ;
			break ;
		case SOLUTION_INFINITE :
			std::cout << OUTPUT_SOLUTION_INFINITE << std::endl;
			break ;
		case SOLUTION_CANNOT_SOLVE_DEGREE :
			std::cout << OUTPUT_SOLUTION_CANNOT_SOLVE_DEGREE << std::endl;
			break ;
	}
}

static void	print_equation(equation equation)
{
	std::cout << "Reduced form: " << equation.getReducedForm() << std::endl;
	std::cout << "Polynomial degree: " << equation.degree << std::endl;
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
	print_results(equation, result);
	return (0);
}
