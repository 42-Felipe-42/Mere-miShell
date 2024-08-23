NAME        =   minishell

CC          =   cc

FLAG        =   -Wall -Wextra -Werror -g3

LIBFT_PATH  =   .libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILE		 = 	$(addsuffix .c,						\
				$(addprefix builtins/, 				\
					echo 							\
					exit 							\
					env 							\
					export 							\
					export2							\
					unset 							\
					cd 								\
					cd2								\
					pwd								\
				)									\
				env/get_env							\
				env/set_no_env						\
				$(addprefix exec/, 					\
					exec 							\
					exec_utils						\
					convert_env						\
					find_cmds						\
					redir 							\
					here_doc 						\
					builtins 						\
				)									\
				$(addprefix expander/, 				\
					expander 						\
					expander_utils 					\
					expander_utils_1 				\
					expander_utils_2 				\
				)									\
				$(addprefix free_shell/, 			\
					exit_free 						\
					free 							\
				)									\
				$(addprefix lexer/, 				\
					lexer_utils 					\
					store_token 					\
				)									\
				$(addprefix parser/, 				\
					parser_utils 					\
					create_cmds						\
					parser 							\
				)									\
				prompt/readline						\
				prompt/signal						\
				main								\
				utils								\
				)									\

OBJS        =   $(C_FILE:.c=.o)
DEPS		=	$(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

.c.o:
	@printf "\r\033[K[Mere-MiShell] \033[0;32mBuilding : $<\033[0m"
	@$(CC) $(FLAG) -c $< -o $@ -MMD -MP

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@printf "\r\033[K[Mere-MiShell] \033[0;32mLinking...\033[0m"
	@$(CC) $(OBJS) $(LIBFT_LIB) -o $(NAME) -lm -lreadline
	@printf "\r\033[K[Mere-MiShell] \033[0;32mDone!\033[0m\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJS) $(DEPS)
	@printf "[Mere-MiShell] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make fclean -C $(LIBFT_PATH)
	@printf "[Mere-MiShell] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
