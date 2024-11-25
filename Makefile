NAME = ft_malcolm

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = inc

HEADERS = -I ./$(INC_PATH)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

REMOVE = rm -rf

SRC =	\
		main.c \
		data_visualization.c \
		libft_utils.c \
		
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(HEADERS) -o $@
	@echo "ft_malcolm is compiled!"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
	@$(REMOVE) $(OBJ_PATH)
	@echo "ft_malcolm is cleaned!"

fclean:
	@$(REMOVE) $(OBJ_PATH)
	@$(REMOVE) $(NAME)
	@echo "ft_malcolm is fcleaned!"

re: fclean all
