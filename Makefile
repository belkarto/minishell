# #=== Colors ===
NO_COLOR    =   \033[0m
GRAY = \033[0;1;3;90m
RED = \033[0;1;3;91m
GREEN = \033[0;1;3;92m
GREEN_L = \033[0;1;3;36m
YELLOW = \033[0;1;3;33m
BLUE	= \033[0;1;3;34m
# #==============

# #=== Standard ===
NAME		= minishell
AUTHOR		= BELKARTO && OHALIM
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT		= include/libft/libft.a
SRC_FILES	= main 
CFLAGS = -Wall -Wextra -Werror
#-g -fsanitize=address
CC = cc 
OBJF		=	.cache_exists
# #================

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
	@$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)
	@printf "$(GREEN)\n- Little shell is ready ✅🥳\n$(NO_COLOR)"
# #===========================================

# #== creat bonus part ===
$(LIBFT)	:	include/libft
	@make -C include/libft
# #=======================


# #== rule that called if object folder doesn't exist ==
$(OBJF):
	@mkdir -p $(OBJ_DIR)
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
	@printf "$(BLUE)fclean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n"
# # ====================================================


# # == HEADER DISPLAYS AUTHOR'S NAME AND COMILER AND FLAGS BEEN USED AND ===
header:
	@printf "$(GREEN)"
	@echo "----------------------------------------------------------------------"
	@echo " ||||  |||| |||||| ||    || ||||||    |||||| ||   || ||||| ||    ||  "
	@echo " || |||| ||   ||   |||   ||   ||     ||      ||   || ||    ||    ||  "
	@echo " ||  ||  ||   ||   || |  ||   ||     ||||    ||||||| ||||  ||    ||  "
	@echo " ||      ||   ||   ||  | ||   ||        |||  ||||||| ||||  ||    ||  "
	@echo " ||      ||   ||   ||   |||   ||         ||  ||   || ||    ||    ||   "
	@echo " ||      || |||||| ||    || ||||||   ||||||  ||   || ||||| ||||| |||||"
	@echo "----------------------------------------------------------------------"
	@echo
	@printf  "$(GREEN_L)Author\t: $(BLUE)$(AUTHOR)\n"
	@printf  "$(GREEN_L)CC    \t: $(YELLOW)$(CC)\n\033[m"
	@printf  "$(GREEN_L)Flags \t: $(YELLOW)$(CFLAGS)\n\033[m"
	@echo
# # ========================================================================


re		:	fclean all

