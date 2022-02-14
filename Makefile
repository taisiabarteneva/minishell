NAME = minishell

SRC = main.c parser/parser_main.c \
\
parser/funcs_for_lists/first_pars_list/ft_new_list.c\
\
parser/first_pars_step/first_pars_step.c parser/first_pars_step/first_pars_step_modified_lib_funcs.c\
parser/first_pars_step/ft_updated_split.c\
\


D_SRC = src
D_OBJ = obj
D_LIB = libft
LIB = libft/libft.a
INCLUDES = minishell.h
LIB_INCLUDES = libft/libft.h libft/get_next_line.h

SRC := $(SRC:%.c=$(D_SRC)/%.c)
OBJ = $(SRC:$(D_SRC)/%.c=$(D_OBJ)/%.o)

FLAGS =  -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -C $(D_LIB)
	gcc $(OBJ) $(LIB) -I. -o $(NAME) -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include
	@echo "You compiled the mandatory part of the project."

$(D_OBJ)/%.o : $(D_SRC)/%.c $(INCLUDES) $(LIB_INCLUDES)
	@mkdir -p $(D_OBJ)
	@mkdir -p $(D_OBJ)/parser
	@mkdir -p $(D_OBJ)/parser/first_pars_step
	@mkdir -p $(D_OBJ)/parser/funcs_for_lists
	@mkdir -p $(D_OBJ)/parser/funcs_for_lists/first_pars_list
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