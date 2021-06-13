NAME = libft.a

MAND_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strmapi.c \
	ft_strtrim.c ft_substr.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_tolower.c ft_toupper.c ft_wchar.c
BONUS_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
MAND_OBJS = $(MAND_FILES:%.c=%.o)
BONUS_OBJS = $(BONUS_FILES:%.c=%.o)
ifdef WITH_BONUS
	OBJS = $(MAND_OBJS) $(BONUS_OBJS)
else
	OBJS = $(MAND_OBJS)
endif

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o $*.o

$(NAME):	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${MAND_OBJS} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:
	$(MAKE) WITH_BONUS=1

.PHONY: all clean fclean re bonus
