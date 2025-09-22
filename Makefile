NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
RM = rm -f

SRCS = core/add.c core/command.c core/execution.c core/free.c core/heredoc.c \
       core/mini.c core/redir.c core/redirinout.c core/routing.c core/routing2.c \
       core/token.c core/update.c core/under.c \
       builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/pwd.c \
       builtin/unset.c builtin/export.c \
       helpers/execution.c helpers/print.c helpers/print2.c helpers/token_flow.c \
       helpers/under_flow.c \
       execution/path.c execution/signals.c \
       utils/ft_atoi.c utils/ft_isalpha.c utils/ft_itoa.c utils/ft_listlen.c \
       utils/ft_matrixlen.c utils/ft_putchar_fd.c utils/ft_putstr.c \
       utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strcat.c utils/ft_strchr.c \
       utils/ft_strcmp.c utils/ft_strcpy.c utils/ft_strdup.c utils/ft_strjoin.c \
       utils/ft_strlcpy.c utils/ft_strlen.c utils/ft_strncmp.c utils/ft_strspn.c \
       utils/ft_substrdup.c utils/is_numeric.c utils/skip.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c mini.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
