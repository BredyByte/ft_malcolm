NAME = ft_malcolm

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = inc
LIBFT_PATH = assets/libft

LIBS = $(LIBFT_PATH)/libft.a

HEADERS = -I ./$(INC_PATH)

CC = gcc -g -o $(NAME)
CFLAGS = -Wall -Wextra -Werror -g3

REMOVE = rm -rf

SRC = $(wildcard $(SRC_PATH)/*.c)
OBJ = $(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))

all: $(LIBS) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(HEADERS) $(LIBS) -o $@
	@echo "ft_malcolm is compiled!"


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBS):
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH)

clean:
	@$(REMOVE) $(OBJ_PATH)
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH) clean
	@echo "ft_malcolm is cleaned!"

fclean:
	@$(REMOVE) $(OBJ_PATH)
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH) fclean
	@$(REMOVE) $(NAME)
	@echo "ft_malcolm is fcleaned!"

re: fclean all

test: $(NAME)
	@echo "Running tests..."
	@if [ -f $(NAME) ]; then \
		./assets/run_tests.sh; \
	else \
		echo "Error: $(NAME) is not compiled. Please run 'make' to compile."; \
		exit 1; \
	fi
