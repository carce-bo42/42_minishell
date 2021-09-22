NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

CC = gcc

SRC_DIR 	= srcs/

SRC_NAMES = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_numberlen.c \
		ft_isdigit.c \
		ft_isspace3.c \
		ft_isign.c \
		ft_strcmp.c \
		ft_maxlen.c \
		ft_matrixlen.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

SRCS 		= $(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJ_DIR 	= objs/
OBJ_NAMES 	= $(SRC_NAMES:.c=.o)
OBJS 		= $(addprefix $(OBJ_DIR), $(OBJ_NAMES))

HDR_NAMES 	= libft.h
HDR_DIR 	= includes/
HDRS 		= $(addprefix $(HDR_DIR),$(HDR_NAMES))

HDR_INC 	= $(addprefix -I./, $(HDR_DIR))

RED		= \033[0;31m
GREEN 		= \033[0;32m
NONE 		= \033[0m

all: $(NAME) $(HDRS)

$(NAME): $(OBJ_DIR) $(OBJS) $(HDRS)
	ar rc $@ $(OBJS)

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) $(HDR_INC) -c $< -o $@

clean:
	rm -Rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
