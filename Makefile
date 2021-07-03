# comment out this line for macOS!!
#FDF_MAC			:= 1
# comment out this line for macOS with mlx_mms!!
#MLX_MMS		:= 1

NAME		:= fdf
ifdef MLX_MMS
	MLIBX_NAME		:= libmlx.dylib
	MLIBX_DIR		:= ./minilibx_mms_20191025_beta
	LFLAGS			:= -framework OpenGL -framework AppKit -lz
else
	ifdef FDF_MAC
		MLIBX_NAME	:= libmlx_Darwin.a
	else
		MLIBX_NAME	:= libmlx.a
	endif
	MLIBX_DIR		:= minilibx_linux
	LFLAGS			:= -L$(MLIBX_DIR) -lXext -lX11 -lm
endif
MLIBX		:= $(MLIBX_DIR)/$(MLIBX_NAME)

LIBFT_DIR	:= libft
LIBFT_NAME	:= libft.a
LIBFT_A		:= $(LIBFT_DIR)/$(LIBFT_NAME)

INCLUDES	:=	-I$(MLIBX_DIR) -I$(LIBFT_DIR)
GNL_SRCS	:=	get_next_line.c get_next_line_utils.c get_next_line_destroy.c
SRCS		:=	ff_main.c ff_exit.c ff_read_map.c ff_points.c\
				ff_image.c ff_line.c ff_clipping.c ff_transform.c ff_projection.c ff_affine.c\
				ff_window.c ff_camera.c ff_hook_key.c ff_hook_mouse.c\
				ff_atoi.c ff_split.c\
				$(GNL_SRCS)
OBJS		:=	$(SRCS:.c=.o)


CC			:= gcc
#CFLAGS		:= -fsanitize=address -Wall -Wextra -Werror $(INCLUDES)
CFLAGS		:= -Wall -Wextra -Werror $(INCLUDES)
ifdef FDF_MAC
	CFLAGS	:= $(CFLAGS) -D FDF_MAC=1
endif
ifdef MLX_MMS
	CFLAGS	:= $(CFLAGS) -D MLX_MMS=1
endif

.PHONY		: all
all			: $(NAME)

.PHONY		: bonus
bonus		: all

.PHONY		: libft
libft		: $(LIBFT_A)
$(LIBFT_A)	:
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME)		: $(OBJS) $(LIBFT_A) $(MLIBX)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(MLIBX):
	make -C $(MLIBX_DIR)
	cp ./$(MLIBX) .

.PHONY		: clean_ff
clean_ff	:
	$(RM) $(OBJS)

.PHONY		: fclean_ff
fclean_ff	: clean_ff
	$(RM) $(NAME)

.PHONY		: clean_mlx
clean_mlx	:
	$(RM) $(MLIBX_NAME)

.PHONY		: fclean_mlx
fclean_mlx	: clean_mlx
	$(MAKE) -C $(MLIBX_DIR) clean

.PHONY		: clean
clean		: clean_ff clean_mlx
	$(MAKE) -C $(LIBFT_DIR) clean

.PHONY		: fclean
fclean		: fclean_ff fclean_mlx
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY		: re
re			: fclean all

.PHONY		: re_mlx
re_mlx		: fclean_ff fclean_mlx all

name		: $(NAME)
	nm -u $(NAME)

norm		:
	python3 -m norminette *.c *.h libft/
	python3 -m norminette -v
