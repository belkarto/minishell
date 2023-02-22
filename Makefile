# #=== Colors ===
NO_COLOR    =   \033[0m
GRAY = \033[0;1;90m
RED = \033[0;1;91m
GREEN = \033[0;1;92m
# #==============

# #=== Standard ===
NAME		= minishell
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

all : $(NAME)
	@printf "$(GREEN)ALL DONE NOTHING TO BE MADE$(NO_COLOR)"

# # == Rule that compile source files into object files ==
$(OBJ_DIR)%.o	: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GRAY)\rcompiling...$(NO_COLOR)"
# #=======================================================

# #=== rule that compile the final program ===
$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)\r   ---> MINISHELL IS MADE <---      \n$(NO_COLOR)"
# #===========================================

# #== creat bonus part ===
$(LIBFT)	:	include/libft
	@make -C include/libft
# #=======================


# #== rule that called if object folder doesn't exist ==
$(OBJF):
	@mkdir -p $(OBJ_DIR)
# #=====================================================


# # == rule deleting compiled files : the cache folder ==
clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C include/libft
	@printf "$(RED)-->   CLEANED   <--$(NO_COLOR)"
# # =====================================================

# # == Rule calling clean and deleting the final file ==
fclean	:	clean
	@make fclean -C include/libft
	@rm -f $(NAME)
# # ====================================================

re		:	fclean all

