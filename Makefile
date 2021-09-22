NAME		=	minishell
LIBFT		=	libft.a

RED 			= \033[0;31m
GREEN 			= \033[0;32m
NONE 			= \033[0m

#Source directories:

MAIN_DIR	=	srcs/
SIG_DIR		=	signals/
ERR_DIR		=	error/
PARSE_DIR	=	parser/
EXEC_DIR	=	execute/
BLTIN_DIR	=	builtins/
LIBFT_DIR	=	libft/
FREE_DIR	=	freezer/

#Source files:

SRCS_FILES	= 	minishell \
				initialize \

SRC_BLTIN	= 	ft_pwd \
				ft_echo \
				ft_env \
				ft_exit \
				ft_cd \
				ft_export \
				ft_export_utils \
				ft_unset

SRC_PARSE	=	comma_parser \
				forbidden_stuff_parser \
				initial_parser \
				process_parse \
				here_doc_parser \
				here_doc_utils \
				string_manipulation \
				other_redirections \
				env_search_related \
				command_argument_gathering \
				string_envar_manipulation \
				expand_vars_outside_strings \
				do_redirection

SRC_SIG		= 	signal \
				signal_responses

SRC_EXEC	=	run_command \
				path_finder \
				local_environment_adding \
				local_environment_adding_utils \
				process_launching \
				several_process \
				exec_utils

SRC_ERR		=	stderr_outputs \
				stderr_outputs_extra \
				q_mark_related \
				builtin_errors

SRC_FREE	=	fundamental_frees \
				sophisticated_frees

SRCS		= 	$(addsuffix .c, $(addprefix $(MAIN_DIR),$(SRCS_FILES))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(SIG_DIR),$(SRC_SIG)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(ERR_DIR),$(SRC_ERR)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(PARSE_DIR),$(SRC_PARSE)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(EXEC_DIR),$(SRC_EXEC)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(BLTIN_DIR),$(SRC_BLTIN)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(FREE_DIR),$(SRC_FREE))))

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I ./includes/ -I ./libft/includes -I ~/.brew/opt/readline/include

CC		=	gcc

CFLAGS		=	-Wall -Wextra -Werror -g3 #-fsanitize=address

RM		=	rm -rf

RDL_MAC		= 	-L ~/.brew/opt/readline/lib -lreadline

LIBFT_MAC	= 	-L libft/ -lft

all:		$(NAME)

$(LIBFT_DIR)$(LIBFT): $(LIBFT_DIR)
			make -C $(dir $(LIBFT_DIR))

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME):	$(OBJS) $(LIBFT_DIR)$(LIBFT) 
			$(CC) $(INCLUDE) $(OBJS) $(RDL_MAC) $(LIBFT_MAC) -o $@ #-fsanitize=address

clean:
			$(RM) $(OBJS)
			make -C $(dir $(LIBFT_DIR)) clean

fclean:		clean
			make -C $(dir $(LIBFT_DIR)) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

