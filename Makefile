NAME = minishell

SRC = test.c

D_SRC = src
D_OBJ = obj
D_LIB = libft
LIB = libft/libft.a
INCLUDES = minishell.h
LIB_INCLUDES = libft/libft.h libft/get_next_line.h

SRC := $(SRC:%.c=$(D_SRC)/%.c)
OBJ = $(SRC:$(D_SRC)/%.c=$(D_OBJ)/%.o)

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -C $(D_LIB)
	gcc $(OBJ) $(LIB) -I. -o $(NAME)
	@echo "You compiled the mandatory part of the project."

$(D_OBJ)/%.o : $(D_SRC)/%.c $(INCLUDES) $(LIB_INCLUDES)
	@mkdir -p $(D_OBJ)
	gcc $(FLAGS) -I. -c $< -o $@

clean :
	@rm -rf $(D_OBJ)
	@$(MAKE) clean -C $(D_LIB)

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(D_LIB)

re : fclean all

.PHONY :
	all clean fclean re lib