NAME:= ft_ssl

FILES:= main.c\
		ft_get_input.c\
		ft_print_hash.c\
		ft_md5.c\
		ft_sha256.c

SOURCE_DIR:=source
SOURCE:= $(addprefix $(SOURCE_DIR)/, $(FILES))

OBJECT_DIR:=object
OBJECT:= $(addprefix $(OBJECT_DIR)/, $(FILES:.c=.o))

WWW:= -Wall -Wextra -Werror

INCLUDE_DIR:=include
H_FILES:= ssl.h\

HEADERS:= $(addprefix $(INCLUDE_DIR)/, $(H_FILES))
INCLUDE:= -I $(INCLUDE_DIR)

LIBFTPRINTF:= libftprintf/libftprintf.a

.PHONY = clean re fclean all libftprintf

all: lib $(NAME)

lib:
	@make -C libftprintf

$(NAME): $(OBJECT_DIR) $(OBJECT)
	@clang $(WALL) $(INCLUDE) $(OBJECT) $(LIBFTPRINTF) -o $(NAME)
	@printf "\033[?25h"
	@printf "\r\033[32;1m$(NAME) have been created!                                                  \n\033[0m"

$(OBJECT_DIR):
	@mkdir -p $(OBJECT_DIR)
	@printf "\033[32m$(OBJECT_DIR) have been created!                                                  \n\033[0m"

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
	@printf "\033[?25l"
	@printf "\r\033[34;1mNow compiling $<!                                                                    "
	@gcc $(WALL) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJECT_DIR)
	@printf "\033[31m$(OBJECT_DIR) have been deleted!                                                   \n\033[0m"
	@make -C libftprintf fclean

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[31;1m$(NAME) have been deleted!                                                        \n\033[0m"

re: fclean all
