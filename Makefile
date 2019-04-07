NAME	= mysh

CC	= gcc

RM	= rm -f

SRCS	= ./get_next_line.c \
	  ./minishell.c \
	  ./my_env_functions.c \
	  ./my_errors.c \
	  ./my_exec.c \
	  ./my_exec2.c \
	  ./my_getnbr.c \
	  ./my_pipe.c \
	  ./my_put_functions.c \
	  ./my_redirections.c \
	  ./my_str_functions.c \
	  ./my_str_to_word_array.c 

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./
CFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
