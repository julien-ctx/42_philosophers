NAME = philo

SRCS = main.c \
		$(addprefix utils/, ft_atoi.c) \
		$(addprefix thread_functions/, philos_threads.c checker_death.c checker_must_eat.c time.c printer.c activities.c) \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Ofast

GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n✅ $(GREEN)SUCCESS: $(NAME) has been created$(RESET)\n" 
	@gcc $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	@rm -rf $(OBJS)
	@echo "\n$(RED)SUCCESS: object files have been deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "\n$(RED)SUCCESS: object files $(NAME) has been deleted$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus
