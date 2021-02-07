SRCS			=	functions/errors.c\
                	functions/init.c\
					functions/cub.c\
					functions/get_next_line.c\
					functions/get_next_line_utils.c\
					functions/mlx.c\
					functions/init_utils.c\
					functions/parse.c\
					functions/parse_utils.c\
					functions/raycast.c\
					functions/raycast_sprites.c\
					functions/movement.c\
					functions/movement_utils.c\
					functions/validation.c\
					functions/screenshot.c\


INCS			=	header/cub.h\

OBJS			= $(SRCS:.c=.o)

CC				= clang
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g -Iinc/ -Imlx/ -Ilibft/inc/ 
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm -Llibft -lft libmlx.dylib
LIBFT			= ./libft/libft.a
NAME			= cub3D

all:			$(NAME)

$(NAME):		$(LIBFT) $(MLX) $(OBJS) $(INCS)
				clang ${CFLAGS} -o cub3D ${OBJS} ${LIBS}

$(LIBFT):
				@make -C libft

$(MLX):
				@make -C mlx

clean:
					$(RM) $(OBJS)
					@make clean -C libft

fclean:			clean
					$(RM) $(NAME) $(MLX) $(LIBFT)
					@make clean -C mlx 

re:				fclean $(NAME)

.PHONY:			all clean fclean re