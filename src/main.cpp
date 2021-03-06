/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/19 16:36:53 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include "computor.h"
#include "equation.h"
#include "ft_math.h"
#include "fraction.h"

static void	print_solutions(equation equation, int result)
{
	double	tmp;

	tmp = equation.x1.get_value();
	std::cout << "x1 = " << equation.s_x1
	<< (equation.s_x1.find('/') != std::string::npos ? " = " + ft_math::double_to_string(tmp, -1) + (equation.discriminant<0 ? "i" : ""): "")
	<< std::endl;
	tmp = equation.x2.get_value();
	if (result == SOLUTION_TWO)
	{
		std::cout << "x2 = " << equation.s_x2
		<< (equation.s_x2.find('/') != std::string::npos ? " = " + ft_math::double_to_string(tmp, -1) + (equation.discriminant<0 ? "i" : ""): "")
		<< std::endl;
	}
}

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
			std::cout << (equation.discriminant == UNDEFINED ? "" : "Discriminant is "BOLD"null"NO_BOLD". ") << OUTPUT_SOLUTION_ONE;
			print_solutions(equation, result);
			break ;
		case SOLUTION_TWO :
			if (equation.discriminant < 0)
				discriminant_type = "strictly negative";
			else
				discriminant_type = "strictly positive";
			std::cout << "Discriminant is strictly " BOLD << (equation.discriminant < 0 ? "negative" : "positive") << NO_BOLD OUTPUT_SOLUTION_TWO;
			print_solutions(equation, result);
			break ;
		case SOLUTION_INFINITE :
			std::cout << OUTPUT_SOLUTION_INFINITE << std::endl;
			break ;
		case SOLUTION_CANNOT_SOLVE_DEGREE :
			std::cout << OUTPUT_SOLUTION_CANNOT_SOLVE_DEGREE << std::endl;
			break ;
		case SOLUTION_OVERFLOW :
			std::cout << OUTPUT_OVERFLOW << std::endl;
			break ;
	}
}

static void	print_equation(equation equation)
{
	std::cout <<
	RESULTS_TITLE << std::endl <<
	"Reduced form: " << BOLD << equation.get_reduced_form() << RESET << std::endl <<
	"Polynomial degree: " << equation.degree << std::endl;
}

int		main(int ac, char **av)
{
	bool	debug = false;
	int			result;

	if (ac != 2)
	{
		if (!av[1] || strcmp(av[1], "-d"))
		{
			std::cerr << ERROR_USAGE << std::endl;
			return (1);
		}
		else
			debug = true;
	}

	equation	equation(debug ? av[2] : av[1], debug);
	if (!equation.is_correct())
	{
		std::cerr << ERROR_FORMAT << std::endl;
		return (1);
	}
	result = equation.solve();
	print_equation(equation);
	print_results(equation, result);
	return (0);
}
