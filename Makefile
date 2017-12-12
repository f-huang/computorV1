# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/16 23:26:49 by fhuang            #+#    #+#              #
#    Updated: 2017/12/12 16:24:14 by fhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Editable =====
NAME	:=	computor
# ====================

# ===== Standard =====
CC		:=	clang++
CFLAGS	:=	-Wall
SRCDIR	:=	src/
OBJDIR	:=	obj/
INCDIR	:=	include/
LIBDIR	:=	lib/
SRC		:=	main.cpp				\
			equation.cpp			\
			ft_math.cpp
OBJ		:=	$(SRC:%.cpp=$(OBJDIR)%.o)
INC		:=	-I./$(INCDIR)
CACHEF	:=	.cache_exists
# ====================

# ====== Colors ======
CLEAR		= "\033[2K"
UP			= "\033[A"
EOC			= "\033[0;0m"
BLACK		= "\033[0;30m"
RED			= "\033[0;31m"
GREEN		= "\033[0;32m"
YELLOW		= "\033[0;33m"
BLUE		= "\033[0;34m"
PURPLE		= "\033[0;35m"
CYAN		= "\033[0;36m"
WHITE		= "\033[0;37m"
# ====================

.PHONY: all norme clean fclean re
.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC)
	printf $(BLUE)" $@ compiled!\n"$(EOC)

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(CACHEF)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	printf $(BLUE)"|"$(EOC)

$(CACHEF):
	test -d $(OBJDIR) || mkdir $(OBJDIR)
	test -d $(CACHEF) || touch $(CACHEF)

%.c:
	printf $(RED)"Missing file : $@\n"$(EOC)

norme:
	norminette $(SRCDIR) $(INCDIR) | grep -v Norme -B1 || true

clean:
	rm -rf $(OBJDIR) $(CACHEF)
	printf $(YELLOW)"All objects removed\n"$(EOC)

fclean: clean
	rm -f $(NAME)
	printf $(RED)"$(NAME) removed\n"$(EOC)

re: fclean all
