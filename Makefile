NAME			= fdf.a

INC				= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/
MLX_DIR			= minilibx-linux/
LIBFT_DIR		= src/libft

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I$(INC) -Wno-unused-result
MLX_FLAGS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lXext -lX11
RM				= rm -rf
AR				= ar rcs

FDF_FILES		= setup_mlx.c draw_lines.c data_parse.c color.c main.c
OBJ				= $(addprefix $(OBJ_DIR), $(FDF_FILES:.c=.o))

all: 			$(NAME)

$(NAME): 		$(OBJ)
				@make -C $(LIBFT_DIR)
				@make -C $(MLX_DIR)
				@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o fdf

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@
clean:
				@$(RM) $(OBJ_DIR)
				@$(RM) .cache_exists
				@make clean -C $(LIBFT_DIR)
				@make clean -C $(MLX_DIR)

fclean: clean
				@$(RM) $(NAME)
				@$(RM) fdf
				@make fclean -C $(LIBFT_DIR)
				@make clean -C $(MLX_DIR)

re: 			fclean all

.PHONY: 		all clean fclean re