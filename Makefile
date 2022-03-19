SRCS	=	./sources/builtins/cd.c \
			./sources/builtins/pwd.c \
			./sources/builtins/echo.c \
			./sources/builtins/env.c \
			./sources/builtins/exit.c \
			./sources/builtins/unset.c \
			./sources/builtins/export.c \
			./sources/executor/executor.c \
			./sources/executor/builtins.c \
			./sources/executor/binary.c \
			./sources/executor/bins_utils.c \
			./sources/main/minishell_main.c \
			./sources/main/readline_prompt.c \
			./sources/signals/catch_signals.c \
			./sources/environ/environ_vars_utils1.c \
			./sources/environ/environ_vars_utils2.c \
			./sources/parser/clear_commands_array.c \
			./sources/parser/parse_and_add_commands.c \
			./sources/parser/remove_redirects_spaces.c \
			./sources/parser/get_command_information.c \
			./sources/parser/wildcard_find_all_utils.c \
			./sources/parser/remove_quotes_change_path.c \
			./sources/parser/wildcard_find_all_arguments.c \
			./sources/parser/get_total_commands_validate_line.c \

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes

NAME	=	minishell

LNAME	=	libft/libft.a

RL_LIB	=	readline/libreadline.a

HS_LIB	=	readline/libhistory.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra -g

RM		=	rm -f

%.o: %.c ./includes/minishell.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS) ./libft/libft.h
	$(MAKE) -C libft bonus
	$(GCC) $(FLAGS) $(OBJS) $(LNAME) $(RL_LIB) $(HS_LIB) -ltermcap -L/Users/${USER}/.brew/opt/readline/lib -lreadline -o $(NAME)

all:	$(NAME)

clean:
		$(MAKE) -C libft clean
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all