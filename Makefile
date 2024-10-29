NAME			= cub3D
OBJ_DIR			= obj/
SRC_DIR			= sources/

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I./includes
MLX_FLAGS_C		= -O3 -Imlx_linux
MLX_FLAGS_L		= -O3 -Imlx_linux -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
RM				= rm -rf

MAKE_MLX		= make -C mlx_linux/
CLEAN_MLX 		= make clean -C mlx_linux/

#$(VERBOSE).SILENT:

SRCS_NAME	=	main.c										\
				map_file_checker/check_file_type.c			\
				map_file_checker/check_map_walls.c			\
				map_file_checker/check_textures.c			\
				map_file_checker/check_file.c				\
				map_file_checker/check_map.c				\
				map_file_checker/check_map_elements.c		\
				map_file_checker/checker_utils.c			\
				map_file_checker/get_doors_info.c			\
				map_file_checker/get_map_textures.c			\
				map_file_checker/get_map_textures_rgb.c		\
				map_file_checker/get_map_content.c			\
				map_file_checker/get_next_line.c			\
				map_file_checker/get_map_utils.c			\
				map_file_checker/map_resizer.c				\
				map_file_checker/get_player_info.c			\
				map_file_checker/map.c						\
				minimap/minimap.c							\
				minimap/minimap_draw_player.c				\
				minimap/minimap_utils.c						\
				player/player.c								\
				player/player_rot_mouse.c					\
				mouse/mouse.c								\
				mouse/mouse_hook.c							\
				raycast/raycast.c							\
				raycast/raycast_update.c					\
				raycast/raycast_door.c						\
				raycast/raycast_wall.c						\
				raycast/raycast_utils.c						\
				raycast/raycast_utils2.c					\
				draw_utils/draw_utils.c						\
				draw_utils/draw_utils2.c					\
				draw_utils/draw_utils_2d.c					\
				init_data_pointers.c						\
				free_map_memory.c							\
				free_memory_utils.c							\
				alloc_memory.c								\
				error_handler.c								\
				math_utils.c								\
				utils.c										\
				render_scene_2d.c							\
				render_scene_3d.c							\
				ray.c										\
				time.c										\
				key_controls.c								\
				collisions.c								\
				doors.c										\
				setup_textures.c							\
				frame_count.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_NAME))

OBJS	= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/map_file_checker
	@mkdir -p $(OBJ_DIR)/minimap
	@mkdir -p $(OBJ_DIR)/player
	@mkdir -p $(OBJ_DIR)/mouse
	@mkdir -p $(OBJ_DIR)/raycast
	@mkdir -p $(OBJ_DIR)/draw_utils
	$(CC) $(CFLAGS) $(MLX_FLAGS_C) -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE_MLX)
	$(CC) $(OBJS) $(CFLAGS) $(MLX_FLAGS_L) -o $(NAME)
	@echo "\033[1;36m[cub3D COMPILED]\033[0m"

clean:
	$(CLEAN_MLX)
	$(RM) $(OBJ_DIR)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	$(RM) $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re norminette
