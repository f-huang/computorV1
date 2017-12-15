/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:01:05 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/15 16:17:44 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include "computor.h"
#include "equation.h"
#include "ft_math.h"
#include "fraction.h"

static void	print_solutions(equation equation)
{
	size_t	pos1;
	size_t	pos2;
	size_t	length1;
	size_t	length2;
	std::string	tmp1;
	std::string	tmp2;

	pos1 = equation.x1.find('/');
	pos2 = std::string::npos;
	length1 = equation.x1.length();
	if ((length2 = equation.x2.length()) != 0)
		pos2 = equation.x2.find('/');
	std::cout << BOLD"\tx1 = ";
	tmp1 = equation.x1;
	if (pos1 != std::string::npos)
	{
		tmp1 = equation.x1.substr(0, pos1);
		std::cout << UNDERLINE << std::setw(length1 - pos1) << std::internal << tmp1;
	}
	else
		std::cout << equation.x1;
	if (equation.discriminant < 0)
		std::cout << UNDERLINE << "i";
	if (pos2 != std::string::npos)
	{
		tmp2 = equation.x2;
		std::cout << NO_UNDERLINE"\t\t x2 = ";
		if (length2 != 0)
		{
			tmp2 = equation.x2.substr(0, pos2);
			std::cout << UNDERLINE << std::setw(length2 - pos2) << std::internal << tmp2;
		}
		else
			std::cout << equation.x2;
		if (equation.discriminant < 0)
			std::cout << UNDERLINE << "i";
	}
	std::cout << NO_UNDERLINE"\n\t    ";
	for (int i = 0; i < tmp1.length() - (pos1 != std::string::npos ? equation.x1.substr(pos1 + 1, length1).length() : 0); i++)
		std::cout << " ";
	if (pos1 != std::string::npos)
		std::cout << equation.x1.substr(pos1 + 1, length1);
	if (pos2 != std::string::npos)
	{
		std::cout << "\t\t      ";
		for (int i = 0; i < tmp2.length() - equation.x2.substr(pos2 + 1, length2).length(); i++)
			std::cout << " ";
		std::cout << equation.x2.substr(pos2 + 1, length2);
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
		if (strcmp(av[1], "-d"))
		{
			std::cerr << ERROR_USAGE << std::endl;
			return (1);
		}
		else
			debug = true;
	}

	equation	equation(debug ? av[2] : av[1], debug);
	fraction	fraction1("0.25");
	if (!equation.is_correct())
	{
		std::cerr << ERROR_FORMAT << std::endl;
		return (1);
	}
	std::cout << "Correct" << std::endl;
	// result = equation.solve();
	// print_equation(equation);
	// print_results(equation, result);
	return (0);
}
