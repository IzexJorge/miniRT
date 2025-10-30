# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 14:06:40 by jescuder          #+#    #+#              #
#    Updated: 2025/10/30 10:18:02 by jescuder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color codes for terminal output
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# The name of the executable
NAME = miniRT

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Command to remove files/directories
REMOVE = rm -rf
# Command to create directories
MKDIR = mkdir -p

# Paths
SRCS_PATH = src/
OBJS_PATH = obj/
INCS_PATH = inc/
LIBFT_PATH = $(INCS_PATH)libft/
MLX_PATH = $(INCS_PATH)minilibx-linux/

# Source files
SRCS = $(wildcard $(SRCS_PATH)*.c)

# Object files
OBJS = $(patsubst $(SRCS_PATH)%.c, $(OBJS_PATH)%.o, $(SRCS))

# Include files
INCS = $(INCS_PATH)$(NAME).h

# Libraries
LIBFT = $(LIBFT_PATH)libft.a
MLX = $(MLX_PATH)libmlx.a

# Compiler flags to link libraries
LFLAGS = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx -lXext -lX11 -lbsd -lm

# Prevents all commands from showing in the shell.
.SILENT:

.PHONY: all libft mlx clean fclean re norm

all: libft mlx $(NAME)

# Runs the libft Makefile, which will compile libft.a if its dependencies have changed.
libft:
	$(MAKE) -C $(LIBFT_PATH) --no-print-directory

# Runs the mlx Makefile, which will compile libmlx.a if its dependencies have changed.
mlx:
	$(MAKE) -C $(MLX_PATH) --no-print-directory

# Compiles the mandatory part.
$(NAME): $(LIBFT) $(MLX) $(OBJS_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
	echo "$(GREEN)[$(NAME)] executable compiled.$(DEF_COLOR)"

# Compiles libft.a if it's missing.
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) --no-print-directory

# Compiles libmlx.a if it's missing.
$(MLX):
	$(MAKE) -C $(MLX_PATH) --no-print-directory

# Creates the objects directory if it doesn't exist.
$(OBJS_PATH):
	$(MKDIR) $(OBJS_PATH)
	echo "$(YELLOW)[$(OBJS_PATH)] directory created.$(DEF_COLOR)"

# Compiles C source files into object files.
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INCS)
	$(CC) $(CFLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I $(MLX_PATH) -c $< -o $@
	echo "$(CYAN)[$@] object compiled.$(DEF_COLOR)"

clean:
	$(REMOVE) $(OBJS_PATH)
	echo "$(MAGENTA)[$(NAME)] objects directory and files cleaned.$(DEF_COLOR)"
	$(MAKE) clean -C $(LIBFT_PATH) --no-print-directory
	$(MAKE) clean -C $(MLX_PATH) --no-print-directory

fclean:
	$(REMOVE) $(OBJS_PATH)
	echo "$(MAGENTA)[$(NAME)] objects directory and files cleaned.$(DEF_COLOR)"
	$(REMOVE) $(NAME)
	echo "$(BLUE)[$(NAME)] executable cleaned.$(DEF_COLOR)"
	$(MAKE) fclean -C $(LIBFT_PATH) --no-print-directory
	$(MAKE) clean -C $(MLX_PATH) --no-print-directory

re: fclean all

norm:
	norminette $(SRCS_PATH) $(INCS) $(LIBFT_PATH)
