# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 13:12:15 by tde-la-r          #+#    #+#              #
#    Updated: 2024/05/21 17:33:32 by tde-la-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c \
	   parsing.c \
	   init_sim.c \
	   start_sim.c \
	   routine.c \
	   routine_utils.c \
	   utils/lst_utils.c \
	   utils/ft_atoi.c \
	   utils/utils.c \
	   utils/ft_fprintf.c \
	   utils/ft_fprintf_utils.c

SRCS_DIR = sources/
OBJS_DIR = objects/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

INCLUDES = -I$(INCLUDE_DIR)
INCLUDE_DIR = include/

CC = clang
FSANITIZE = -fsanitize=thread
FLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) 
	@echo "$(NAME) compiled"

fsanitize : fclean $(OBJS)
	@$(CC) $(OBJS) $(FSANITIZE) -o $(NAME) 
	@echo "$(NAME) compiled"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean :
	@$(RM) $(OBJS_DIR)
	@echo "Files cleaned"

fclean : clean
	@$(RM) $(NAME)
	@echo "Full clean"

re : fclean all

.PHONY : all clean fclean re fsanitize 
