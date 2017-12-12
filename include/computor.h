/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:17:09 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/12 18:03:36 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_H
# define COMPUTOR_H

# define PROGRAM_NAME "computor"

# define SOLUTION_ERROR -1
# define SOLUTION_NONE 0
# define SOLUTION_ONE 1
# define SOLUTION_TWO 2
# define SOLUTION_CANNOT_SOLVE_DEGREE 124
# define SOLUTION_INFINITE 125

#define ERROR_FORMAT PROGRAM_NAME": Not well formatted"
#define ERROR_USAGE  PROGRAM_NAME": illegal arguments\nusage: computor <equation>"
#define ERROR_SOLVING PROGRAM_NAME": Cannot solve"

#define OUTPUT_SOLUTION_NONE "No solution."
#define OUTPUT_SOLUTION_ONE "The solution is: \n"
#define OUTPUT_SOLUTION_TWO ", the two solutions are: \n"
#define OUTPUT_SOLUTION_INFINITE "Infinite solutions."
#define OUTPUT_SOLUTION_CANNOT_SOLVE_DEGREE "The polynomial degree is stricly greater than 2, I can't solve."

#endif
