# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 15:01:22 by amweyer           #+#    #+#              #
#    Updated: 2025/09/26 12:36:01 by amweyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Sources
SRC =  $(SRC_DIR)/main.c \
       $(SRC_DIR)/parsing.c \
       $(SRC_DIR)/free.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/routine.c \
       $(SRC_DIR)/routine_utils.c \
       $(SRC_DIR)/eat_utils.c \
#        $(SRC_DIR)/pipe_utils.c \
#        $(SRC_DIR)/pipe_init.c \
#        $(SRC_DIR)/get_next_line_utils_bonus.c \
#        $(SRC_DIR)/get_next_line_bonus.c

# Objects
OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread #-g #-fsanitize=thread
CPPFLAGS = -I $(INC_DIR) 

# Commands
RM = rm -f

# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m

# Default target
all: $(NAME)


# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Clean object files
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(GREEN)Object files removed.$(DEF_COLOR)"

# Full clean
fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Binary removed.$(DEF_COLOR)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
