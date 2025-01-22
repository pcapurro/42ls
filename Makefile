# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = 42ls

SRCS = srcs/main.c \
	srcs/help.c \
	srcs/heart/heart.c \
	srcs/heart/folder.c \
	srcs/heart/print.c \
	srcs/heart/order.c \
	srcs/heart/listing.c \
	srcs/heart/options.c \
	srcs/heart/paths.c \
	srcs/tools/tools.c \
	srcs/tools/print.c \
	srcs/tools/checkers.c \
	srcs/tools/library.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
