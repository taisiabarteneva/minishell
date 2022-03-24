SRCS	=	./sources/builtins/cd/cd.c \
			./sources/builtins/cd/cd_utils.c \
			./sources/builtins/pwd/pwd.c \
			./sources/builtins/echo/echo.c \
			./sources/builtins/env/env.c \
			./sources/builtins/export/export.c \
			./sources/builtins/export/export_utils.c \
			./sources/builtins/exit/exit.c \
			./sources/builtins/unset/unset.c \
			./sources/executor/builtins.c \
			./sources/executor/binary.c \
			./sources/executor/wait_child_process.c \
			./sources/executor/bins_utils.c \
			./sources/executor/pipes.c \
			./sources/executor/get_command_position.c \
			./sources/executor/parse_command.c \
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

FLAGS	=	-Wall -Werror -Wextra #-g -fsanitize=address

RM		=	rm -f

%.o: %.c ./includes/minishell.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS) ./libft/libft.h
	$(MAKE) -C libft bonus
	$(GCC) $(FLAGS) $(OBJS) $(LNAME) $(RL_LIB) $(HS_LIB) -ltermcap -lreadline -o $(NAME)

all:	$(NAME)

clean:
		$(MAKE) -C libft clean
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all