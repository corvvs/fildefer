NAME		:= fdf
LFLAGS				:= -framework OpenGL -framework AppKit -lz
MLIBX_MMS_NAME		:= libmlx.dylib
MLIBX_MMS_DIR		:= ./minilibx_mms_20191025_beta
MLIBX_MMS			:= $(MLIBX_MMS_DIR)/$(MLIBX_MMS_NAME)
MLIBX_OPENGL_DIR	:= ./minilibx_mms_20191025_beta
MLIBX_OPENGL		:= $(MLIBX_OPENGL_DIR)/libmlx.a

LIBFT_DIR		:= libft
LIBFT_NAME		:= libft.a
LIBFT_A			:= $(LIBFT_DIR)/$(LIBFT_NAME)

INCLUDES	:= -I$(MLIBX_MMS_DIR) -I$(LIBFT_DIR)
GNL_SRCS	:= get_next_line.c get_next_line_utils.c
SRCS		:=	ff_main.c ff_alloc.c ff_read_map.c ff_write.c\
				ff_strs.c ff_atoi.c ff_split.c\
				$(GNL_SRCS)
OBJS		:= $(SRCS:.c=.o)


CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror $(INCLUDES)

all			: $(NAME)

.PHONY			: libft
libft			: $(LIBFT_A)
$(LIBFT_A)		:
			$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME)		: $(OBJS) $(LIBFT_A) $(MLIBX_MMS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(MLIBX_MMS):
	make -C $(MLIBX_MMS_DIR)
	cp ./$(MLIBX_MMS) .

clean		:
	$(RM) $(OBJS)
	$(RM) $(NAME) $(MLIBX_MMS_NAME)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	$(MAKE) -C $(MLIBX_MMS_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re:	fclean all

name: $(NAME)
	nm -u $(NAME)
