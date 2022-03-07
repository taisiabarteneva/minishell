SRCS	=	./sources/minishell_main.c \
			./sources/readline_prompt.c \
			./sources/command_parsing1.c \
			./sources/command_parsing2.c \
			./sources/environ_vars_utils1.c \
			./sources/environ_vars_utils2.c \
			./sources/catch_signals.c \
			./sources/built_ins_main.c \
			./sources/built_in_cd.c \
			./sources/built_in_echo.c \
			./sources/built_in_env.c \
			./sources/built_in_exit.c \
			./sources/built_in_pwd.c \
			./sources/built_in_unset.c \

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes

NAME	=	minishell

LNAME	=	libft/libft.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c ./inclues/minishell.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS) ./libft/libft.h
	$(MAKE) -C libft all
	$(GCC) $(FLAGS) $(OBJS) $(LNAME) -L/Users/${USER}/.brew/opt/readline/lib -lreadline -o $(NAME)

all:	$(NAME)

clean:
		@$(MAKE) fclean -C ./libft
		@$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all