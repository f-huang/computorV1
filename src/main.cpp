/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/14 20:48:12 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include "computor.h"
#include "equation.h"
#include "ft_math.h"

static void	print_solutions(equation equation)
{
	size_t	pos1;
	size_t	pos2;
	size_t	length1;
	size_t	length2;

	pos1 = equation.x1.find('/');
	pos2 = std::string::npos;
	length1 = equation.x1.length();
	if ((length2 = equation.x2.length()) != 0)
		pos2 = equation.x2.find('/');
	std::cout << BOLD"\tx1 = ";
	if (pos1 != std::string::npos)
		std::cout << UNDERLINE << std::setw(length1 - pos1) << std::internal << equation.x1.substr(0, pos1);
	else
		std::cout << equation.x1;
	if (equation.discriminant < 0)
		std::cout << UNDERLINE << "i";
	if (pos2 != std::string::npos)
	{
		std::cout << NO_UNDERLINE"\t\t x2 = ";
		if (length2 != 0)
			std::cout << UNDERLINE << std::setw(length2 - pos2) << std::internal << equation.x2.substr(0, pos2);
		else
			std::cout << equation.x2;
		if (equation.discriminant < 0)
			std::cout << UNDERLINE << "i";
	}
	std::cout << NO_UNDERLINE"\n";
	if (pos1 != std::string::npos)
		std::cout << "\t    " << std::setw(length1 - (length1 - pos1)) << std::internal << equation.x1.substr(pos1 + 1, length1);
	if (pos2 != std::string::npos)
	{
		std::cout << "\t\t      ";
		std::cout << std::setw(length2 - (length2 - pos2)) << std::internal << equation.x2.substr(pos2 + 1, length2);
	}
	std::cout << RESET"\n";
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
			std::cout << OUTPUT_SOLUTION_ONE;
			print_solutions(equation);
			break ;
		case SOLUTION_TWO :
			if (equation.discriminant < 0)
				discriminant_type = "strictly negative";
			else if (equation.discriminant == 0)
				discriminant_type = "null";
			else
				discriminant_type = "strictly positive";
			std::cout << "Discriminant is " << discriminant_type << OUTPUT_SOLUTION_TWO;
			print_solutions(equation);
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
	std::cout << "Reduced form: " << BOLD << equation.getReducedForm() << RESET << std::endl;
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
