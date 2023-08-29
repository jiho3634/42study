NAME = libft.a
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
SRCS = ft_bzero.c ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_memcmp.c ft_power.c
SRCS_B = 
PRINTF_SRCS = ft_printf_err.c ft_print_x_err.c ft_print_u_err.c ft_print_s_err.c ft_print_p_err.c ft_print_di_err.c ft_print_c_err.c
GNL_SRCS = get_next_line_utils_bonus.c get_next_line_bonus.c
HEADER = -I ../../includes
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)
OBJS_PRINTF = $(PRINTF_SRCS:.c=.o)
OBJS_GNL = $(GNL_SRCS:.c=.o)

OB = $(OBJS) $(OBJS_B) $(OBJS_PRINTF) $(OBJS_GNL)

all : $(NAME)

$(NAME) : $(OB)
	@ar -rc $@ $^

%.o : %.c
	@$(CC) $(CFLAGS) $< -o $@ $(HEADER)

clean:
	@rm -rf $(OBJS) $(OBJS_B) $(OBJS_PRINTF) $(OBJS_GNL)

fclean : clean
	@rm -rf $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re
