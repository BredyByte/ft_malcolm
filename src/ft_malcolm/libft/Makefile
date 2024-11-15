NAME = libft.a

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = inc

HEADERS = -I $(INC_PATH)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

ARFLAGS = -rcs

REMOVE = rm -rf

SRC = $(wildcard $(SRC_PATH)/*.c)
OBJ = $(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	@ar $(ARFLAGS) $@ $^
	@echo "Libft is compiled!"


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@$(REMOVE) $(OBJ_PATH)
	@echo "Libft is cleaned!"

fclean:
	@$(REMOVE) $(OBJ_PATH)
	@$(REMOVE) ./$(NAME)
	@echo "Libft is fcleaned!"

re: fclean all
