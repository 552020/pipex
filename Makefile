
NAME = pipex 
CC = cc 
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
INCLUDES = -I./include  -I./libft
GREEN   = \033[32;1m
RESET	= \033[0m
MLX42_DIR = ./MLX42
SRC_DIR = src/
OBJ_DIR = objs/

SRCS	= utils.c	pipex.c

SRC	= $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

all:	$(NAME) 

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) 
	@echo "$(GREEN) Compiled with $(CFLAGS)$(RESET)"

$(LIBFT):
	@$(MAKE) -C ./libft
	@echo "$(GREEN) Libft compiled $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

clean: 
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Cleaned $(RESET)"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@echo "$(GREEN) Full cleaned $(RESET)"

re:	fclean all

.PHONY: all clean fclean re
