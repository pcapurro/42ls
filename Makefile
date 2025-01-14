# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = ft_ls

SRCS = srcs/main.c \
	srcs/heart.c \
	srcs/order.c \
	srcs/listing.c \
	srcs/getOptions.c \
	srcs/getPaths.c \
	srcs/tools.c \
	srcs/library.c \

CC = gcc

CFLAGS = -fsanitize=address -g

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
