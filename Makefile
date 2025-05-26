# Platform-specific settings
ifeq ($(OS),Windows_NT)
    RM = del /q
    RM_DIR = rmdir /s /q
    LIB_EXT = .lib
else
    RM = rm -f
    RM_DIR = rm -rf
    LIB_EXT = .a
endif

# Program name
NAME			:= miniRT

# Submodule MLX42
SUBM_MLX_DIR	:= lib/mlx42

# Submodule libft
SUBM_LIBFT_DIR	:= lib/libft
SUBM_LIBFT_LIB	:= $(SUBM_LIBFT_DIR)/libft$(LIB_EXT)

# Compilation variables
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror
HDRS			:= -Iinclude -I$(SUBM_MLX_DIR)/include -I$(SUBM_LIBFT_DIR)/include
LIBS			:= -L$(SUBM_MLX_DIR)/build -lmlx42 \
				   -L$(SUBM_LIBFT_DIR) -lft \
				   -ldl -lglfw \
				   -lm

# Directories
OBJ_DIR			:= obj
SRC_DIR			:= src

# Sources and objects
SRCS			:= src/constructor/rt_init_info.c src/constructor/rt_init_objects.c \
				   src/constructor/rt_init_canvas.c \
				   \
				   src/destructor/rt_destroy_exit.c src/destructor/rt_free_arr.c \
				   src/destructor/rt_perror.c \
				   \
				   src/parser/parser_utils.c src/parser/rt_parse_ambient.c \
				   src/parser/rt_parse_camera.c src/parser/rt_parse_light.c \
				   src/parser/rt_parse_scene.c src/parser/rt_read_scene.c \
				   src/parser/rt_validate_input.c src/parser/rt_parse_cylinder.c \
				   src/parser/rt_parse_plane.c src/parser/rt_parse_sphere.c \
				   src/parser/objects_transform.c \
				   \
				   src/hook/hook_close_window.c src/hook/hook_resize_window.c \
				   src/hook/hook_render_scene.c \
				   \
				   src/renderer/camera.c src/renderer/color.c src/renderer/ray.c \
				   \
				   src/calculations/math.c \
				   \
				   src/calculations/matrices/create_base_matrix.c \
				   src/calculations/matrices/create_base_transform.c \
				   src/calculations/matrices/create_shearing_transform.c \
				   src/calculations/radians.c src/calculations/matrices/operations.c \
				   src/calculations/matrices/get_submatrix.c \
				   src/calculations/matrices/inverse.c \
				   \
				   src/shapes/sphere.c \
				   \
				   \
				   \
				   src/display-config/debug_utils.c src/display-config/test_matrix_math.c \
				   src/display-config/test_matrix_transformation.c
				   
SRC_MAIN		:= src/main.c

OBJS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_MAIN		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_MAIN))

#for tarcking changes in header files
H_FILES			:= include/minirt_data.h include/minirt.h include/minirt_renderer.h \
				   include/minirt_matrix.h include/display_config.h

# RULES
all: update-submodule build-submodule $(NAME)

$(NAME): $(OBJS) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJS) $(OBJ_MAIN) $(HDRS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(H_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HDRS) -c $< -o $@

clean:
	$(RM_DIR) $(OBJ_DIR)
	$(MAKE) -C $(SUBM_LIBFT_DIR) clean

fclean: clean
	$(RM_DIR) $(SUBM_MLX_DIR)/build 
	$(RM) $(NAME)
	$(MAKE) -C $(SUBM_LIBFT_DIR) fclean

re: fclean all

# Rule: update submodules (MLX42 and libft)
update-submodule:
	@git submodule init
	@git submodule update --recursive

# Rule: build submodule MLX42 and compile libft
build-submodule:
	cd $(SUBM_MLX_DIR) && cmake -B build && cmake --build build -j4
	@echo "\nMLX42 is ready.\n"
	$(MAKE) -C $(SUBM_LIBFT_DIR) 

.PHONY: all clean fclean re update-submodule build-submodule