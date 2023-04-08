# #=== Colors ===
NO_COLOR	= \033[0m
GRAY		= \033[0;1;3;90m
RED			= \033[0;1;3;91m
GREEN		= \033[0;1;3;92m
GREEN_L		= \033[0;1;3;36m
YELLOW		= \033[0;1;3;33m
BLUE		= \033[0;1;3;34m
# #==============

# #=== Standard ===
NAME		= minishell
AUTHOR		= BELKARTO && OHALIM
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT		= include/libft/libft.a
LEXER_DIR	= lexer/lexer lexer/quote lexer/tokens
PARSER_DIR	= parser/command_table
PARSER_UTILS_DIR	= parser/utils/char_utils parser/utils/path_utils parser/utils/expantion_utils \
					parser/utils/file_utils
UTILS_DIR	= utils/elem_utils utils/print_utils utils/env_utils utils/env_utils2 utils/var_utils \
			  utils/export_sort
BUILIN_DIR	= built/builtins built/ft_cd built/ft_pwd built/ft_exit built/ft_export built/ft_env built/ft_unset
SRC_FILES	= main signals $(LEXER_DIR) $(PARSER_UTILS_DIR) $(PARSER_DIR) $(UTILS_DIR) $(BUILIN_DIR)
CFLAGS		= -Wall -Wextra -Werror
#-g -fsanitize=address
CC			= cc 
OBJF		=	.cache_exists
# #================

# #=== check the user to detect readline path ===
ifeq ($(USER), belkarto)
	READLINE = -L ~/Desktop/homebrew/Cellar/readline/8.2.1/lib
endif
ifeq ($(USER), iiouma_ii)
	READLINE = -L ~/homebrew/Cellar/readline/8.2.1/lib
endif
ifeq ($(USER), ohalim)
	READLINE = -L ~/Desktop/brew/Cellar/readline/8.2.1/lib
endif
ifeq ($(USER), brahim)
	READLINE = -L ~/Desktop/homebrew/Cellar/readline/8.2.1/lib
endif
# #==============================================

# # ===Better not to touch ===#
SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
# #===========================#

all : header $(NAME)

# # == Rule that compile source files into object files ==
$(OBJ_DIR)%.o	: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GRAY)\r- Creating little shell ...⌛$(NO_COLOR)"
	@sleep 0.03
	@printf "$(GRAY)\r- Creating little shell ...⏳$(NO_COLOR)"
	@sleep 0.03
# #=======================================================

# #=== rule that compile the final program ===
$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline $(READLINE) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)\n- Little shell is ready ✅🥳\n$(NO_COLOR)"
# #===========================================

# #== creat bonus part ===
$(LIBFT)	:	include/libft
	@make -C include/libft
# #=======================
#
# #== rule that called if object folder doesn't exist ==
$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/lexer
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/parser/utils
	@mkdir -p $(OBJ_DIR)/built
# #=====================================================


## # == rule deleting compiled files : the cache folder ==
clean : header
	@rm -rf $(OBJ_DIR)
	@make clean -C include/libft
	@printf "$(BLUE)clean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n"
# # =====================================================

# # == Rule calling clean and deleting the final file ==
fclean	: header clean
	@make fclean -C include/libft
	@rm -f $(NAME)
	@printf "$(BLUE)fclean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n\n"
# # ====================================================

# # == HEADER DISPLAYS AUTHOR'S NAME AND COMILER AND FLAGS BEEN USED AND ===
header:
	@printf "$(GREEN)"
	@echo "  ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       "
	@echo " ██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       "
	@echo "███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       "
	@echo "███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       "
	@echo "███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       "
	@echo "███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       "
	@echo "███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ "
	@echo " ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ "
	@echo
	@printf  "$(GREEN_L)Author\t: $(BLUE)$(AUTHOR)\n"
	@printf  "$(GREEN_L)CC    \t: $(YELLOW)$(CC)\n\033[m"
	@printf  "$(GREEN_L)Flags \t: $(YELLOW)$(CFLAGS)\n\033[m"
	@echo
# # ========================================================================
re		:	fclean all

# @echo "----------------------------------------------------------------------"
# @echo " ||||  |||| |||||| ||    || ||||||    |||||| ||   || ||||| ||    ||  "
# @echo " || |||| ||   ||   |||   ||   ||     ||      ||   || ||    ||    ||  "
# @echo " ||  ||  ||   ||   || |  ||   ||     ||||    ||||||| ||||  ||    ||  "
# @echo " ||      ||   ||   ||  | ||   ||        |||  ||||||| ||||  ||    ||  "
# @echo " ||      ||   ||   ||   |||   ||         ||  ||   || ||    ||    ||   "
# @echo " ||      || |||||| ||    || ||||||   ||||||  ||   || ||||| ||||| |||||"
# @echo "----------------------------------------------------------------------"
