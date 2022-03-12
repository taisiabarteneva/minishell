SRCS	=	./sources/minishell_main.c \
			./sources/readline_prompt.c \
			./sources/get_command_information.c \
			./sources/rm_redirects_spaces_quotes.c \
			./sources/line_check_and_replace_path.c \
			./sources/parse_and_add_or_clear_commands.c \
			./sources/environ_vars_utils1.c \
			./sources/environ_vars_utils2.c \
			./sources/sig/catch_signals.c \
			./sources/built_ins/cd.c \
			./sources/built_ins/pwd.c \
			./sources/built_ins/echo.c \
			./sources/built_ins/env.c \
			./sources/built_ins/exit.c \
			./sources/built_ins/unset.c \
			./sources/built_ins/export.c \
			./sources/built_ins/builtins_main.c \

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes

NAME	=	minishell

LNAME	=	libft/libft.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c ./includes/minishell.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS) ./libft/libft.h
	$(MAKE) -C libft all
	$(GCC) $(FLAGS) $(OBJS) $(LNAME) -L/Users/${USER}/.brew/opt/readline/lib -lreadline -o $(NAME)

all:	$(NAME)

clean:
		$(MAKE) -C libft clean
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all