NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra
LIBFT = Libft/libft.a
SRC = init.c  main.c  routine.c  utils.c init_philo.c

OBJ = $(SRC:.c=.o)

GREEN = \033[32m
RESET = \033[0m

define PRINT_LOADING
	@printf "$(GREEN)Compiling... ["
	@for i in $(shell seq 0 10 1000); do \
		printf "▓"; \
		sleep 0.01; \
	done
	@printf "] 100%%$(RESET)\n"
endef

.SILENT:
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L./Libft -lft -o$(NAME) >/dev/null 2>&1
	@echo -n "$(GREEN)Creating library...$(RESET)"
	@echo "$(GREEN)Library created successfully!$(RESET)"
	@$(PRINT_LOADING)
	@echo "$(GREEN) Compilation complete!$(RESET)"	

$(LIBFT):
	$(MAKE) -sC ./Libft >/dev/null 2>&1	

clean:
	$(MAKE) clean -sC ./Libft >/dev/null 2>&1
	@$(RM) -rf $(OBJ)
	@echo "$(GREEN)Cleaning up...$(RESET)"
	@echo "$(GREEN)Cleanup complete!$(RESET)"

fclean: clean
	$(MAKE) clean -sC ./Libft >/dev/null 2>&1
	@$(RM) -rf $(NAME)
	@echo "$(GREEN)Removing library...$(RESET)"
	@echo "$(GREEN)Library removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re