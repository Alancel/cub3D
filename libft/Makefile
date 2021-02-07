# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alancel <alancel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 19:22:08 by alancel           #+#    #+#              #
#    Updated: 2020/11/26 21:43:51 by alancel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRC			=	ft_isprint.c \
				ft_memset.c \
				ft_bzero.c \
				ft_strlcat.c \
				ft_calloc.c \
				ft_memccpy.c \
				ft_strlcpy.c \
				ft_tolower.c \
				ft_isalnum.c \
				ft_memchr.c \
				ft_toupper.c \
				ft_isalpha.c \
				ft_memcmp.c \
				ft_strncmp.c \
				ft_isascii.c \
				ft_memcpy.c \
				ft_strchr.c \
				ft_strnstr.c \
				ft_strlen.c \
				ft_isdigit.c \
				ft_memmove.c \
				ft_strdup.c \
				ft_strrchr.c \
				ft_atoi.c \
				ft_substr.c\
				ft_strjoin.c\
				ft_itoa.c\
				ft_putchar_fd.c\
				ft_putnbr_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_strmapi.c\
				ft_strtrim.c\
				ft_split.c\
				ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\
				ft_putstr.c\
				ft_putendl.c\
			
	

OBJS		=	$(SRC:.c=.o)

BONUS		=	ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\
			
BONUS_OBJS	=	$(BONUS:.c=.o)

RM			=	rm -f

CFLAGS		= -Wall -Wextra -Werror

all:	$(NAME)

%.o : %.c
		gcc $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
		ar rc $(NAME) $^
		ranlib $(NAME)
		
bonus	:
		gcc $(CFLAGS) -c $(BONUS)
		ar rc $(NAME) $(BONUS_OBJS)
		ranlib $(NAME)
		
	
clean	:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all