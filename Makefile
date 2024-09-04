# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 16:08:43 by anadal-g          #+#    #+#              #
#    Updated: 2024/09/04 12:42:28 by anadal-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME = pipex

# SOURCE FILES
SRC_DIR			=	src/
SRC_BONUS_DIR	=	src_bonus/

SRC_FILES =	main.c \
			errors.c \
			child_parent.c \
			check_path.c \

SRC_BONUS_FILES = main_bonus.c \
			check_path_bonus.c \
			errors_bonus.c \
			child_parent_bonus.c \
			here_doc_bonus.c \
	
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_BONUS	=	$(addprefix $(SRC_DIR), $(SRC_BONUS_FILES))

#OBJECT FILES
OBJ_DIR		= objs/
OBJ_FILES 	= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_BONUS_FILES = $(SRC_BONUS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#COMPILER
CC		= cc #-g -O3 -fsanitize=address
FLAGS	= -Wall -Wextra -Werror
INCLUDE = -I includes
RM		= rm -rf
LIBFT 	= libft/libft.a

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

#MAKEFILE RULES
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@


$(OBJ_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ_FILES)
	@make -C libft
	@echo "$(GREEN)Compiling the PIPEX program.$(CLEAR)"
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME) $(INCLUDE) -Llibft -lft
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"
	
clean:
	@echo "$(BLUE)Removing compiled files.$(CLEAR)"
	$(RM) $(OBJ_DIR)
	@make -C libft/ clean
	@echo "$(BLUE)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@echo "$(BLUE)Removing exec. files.$(CLEAR)"
	$(RM) $(NAME)
	@make -C libft/ fclean
	@echo "$(BLUE)Object files and binary removed correctly\n$(CLEAR)"

re: fclean all

bonus : $(OBJ_BONUS_FILES)
	@make all -sC libft
	@echo "$(GREEN)Compiling the PIPEX BONUS program.$(CLEAR)"
	$(CC) $(FLAGS) $(OBJ_BONUS_FILES) -o $(NAME) $(INCLUDE) -Llibft -lft
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

.PHONY: all clean fclean re  
