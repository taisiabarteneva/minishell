NAME = libft.a

MAIN =	ft_isdigit.c		ft_strchr.c		ft_tolower.c\
		ft_isprint.c		ft_strlcat.c	ft_toupper.c\
		ft_atoi.c			ft_memchr.c		ft_strlcpy.c\
		ft_memcmp.c			ft_strlen.c\
		ft_isalnum.c		ft_memcpy.c		ft_strncmp.c\
		ft_isalpha.c		ft_memmove.c\
		ft_isascii.c		ft_memset.c		ft_strrchr.c\
		ft_bzero.c 			ft_strnstr.c 	ft_calloc.c\
		ft_strdup.c 		ft_substr.c 	ft_strjoin.c\
		ft_strtrim.c 		ft_itoa.c 		ft_strmapi.c\
		ft_striteri.c 		ft_putchar_fd.c ft_putstr_fd.c\
		ft_putendl_fd.c 	ft_putnbr_fd.c 	ft_split.c\
		get_next_line.c\

BONUS =	ft_lstnew_bonus.c	ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c	ft_lstlast_bonus.c\

OBJ = $(patsubst %.c,%.o,$(MAIN))
OBJ_BONUS = $(patsubst %.c,%.o,$(BONUS))

INCLUDES	=	libft.h

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $?

%.o : %.c $(INCLUDES)
	gcc $(FLAGS) -c $< -o $@

bonus :
	@make OBJ="$(OBJ_BONUS)" all ${INCLUDES}

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY :
	all clean fclean re bonus