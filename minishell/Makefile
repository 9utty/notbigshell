NAME			=	minishell

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g3
#DEBUG			=	-fsanitize=address -fsanitize=leak -g

RLDIR			=	$(shell brew --prefix)
LIBREADLINE		=	$(RLDIR)/opt/readline/lib

INCLUDE_DIRS	=	-I includes -I $(RLDIR)/opt/readline/include
LIB_DIR			=	-L$(LIBREADLINE) -lreadline

PARSER			= parser.c						\
					parser_insert.c				\
					parser_replace_utils_1.c	\
					parser_replace.c			\
					parser_syntax_1.c			\
					parser_syntax_2.c			\
					parser_token_utils.c		\
					parser_tokenize.c			\
					parser_tree_init.c			\

BUILTIN			= ft_cd.c						\
					ft_echo.c					\
					ft_env.c					\
					ft_exit.c					\
					ft_export.c					\
					ft_export2.c				\
					ft_pwd.c					\
					ft_unset.c					\
					builtin_utils.c				\

EXECUTER		= execute.c						\
					execute_heredoc.c			\
					execute_pipe.c				\
					execute_command.c			\
					execute_redir.c				\
					execute_bash.c				\
					execute_utils.c				\


UTILS			= error_print.c					\
					print_main_cover.c			\
					set_env.c					\
					sig_action.c				\
					table_set.c					\
					utils_clear.c				\
					utils_env.c					\
					utils_ft_1.c				\
					utils_ft_2.c				\
					utils_ft_3.c				\
					utils_ft_4.c				\
					utils_ft_5.c				\
					utils_init.c				\
					utils_is.c					\
					utils_list.c				\
					utils_term.c


SRC 			=	$(addprefix src/parser/, $(PARSER))	\
					$(addprefix src/builtin/, $(BUILTIN))	\
					$(addprefix src/execute/, $(EXECUTER))	\
					$(addprefix src/utils/, $(UTILS))		\
					src/main.c

OBJ_DIR			=	obj

OBJ				=	$(addprefix obj/,$(SRC:%.c=%.o)) \



all				:	$(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o	:	%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $^ -o $@

$(NAME)			:	$(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) $(INCLUDE_DIRS) $(LIB_DIR) -o $(NAME)

$(OBJ_DIR)		:
				mkdir -p obj

clean			:
				$(RM) obj

fclean			:
				$(RM) obj
				$(RM) $(NAME)

re				:
				$(RM) obj
				$(RM) $(NAME)
				make all

./PHONY			:	all, clean, fclean, re
