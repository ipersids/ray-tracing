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
# Flags hints:
# -O2 (level of optimisation) 
# -flto (Link Time Optimization)
CFLAGS			:= -O2 -flto -Wall -Wextra -Werror
HDRS			:= -Iinclude -I$(SUBM_MLX_DIR)/include -I$(SUBM_LIBFT_DIR)/include
LIBS			:= -L$(SUBM_MLX_DIR)/build -lmlx42 \
				   -L$(SUBM_LIBFT_DIR) -lft \
				   -ldl -lglfw \
				   -lm

# Directories
OBJ_DIR			:= obj
SRC_DIR			:= src

# Sources and objects
SRCS			:= src/constructor/init_info.c src/constructor/init_objects.c \
				   src/constructor/init_window.c src/constructor/init_material.c \
				   \
				   src/destructor/destroy_exit.c src/destructor/free_arr.c \
				   src/destructor/handle_errors.c \
				   \
				   src/parser/parser_utils.c src/parser/parse_ambient.c \
				   src/parser/parse_camera.c src/parser/parse_light.c \
				   src/parser/parse_scene.c src/parser/read_scene.c \
				   src/parser/validate_input.c src/parser/parse_cylinder.c \
				   src/parser/parse_plane.c src/parser/parse_sphere.c \
				   src/parser/set_transformations.c src/parser/set_material.c \
				   src/parser/set_cursor.c \
				   \
				   src/hook/hook_close_window.c src/hook/hook_resize_window.c \
				   src/hook/hook_render_scene.c src/hook/hook_rotate_camera.c \
				   src/hook/hook_handle_mouse.c src/hook/hook_zoom_camera.c \
				   \
				   src/renderer/camera.c src/renderer/color_at.c \
				   src/renderer/intersect_world.c src/renderer/normal_at.c \
				   src/renderer/ray.c src/renderer/ray_utils.c \
				   \
				   src/calculations/vectors/vector_operations.c \
				   src/calculations/vectors/vector_math.c src/calculations/colors.c \
				   src/calculations/math_utils.c \
				   src/calculations/matrices/create_base_matrix.c \
				   src/calculations/matrices/create_base_transform.c \
				   src/calculations/matrices/create_shearing_transform.c \
				   src/calculations/matrices/matrix_operations.c \
				   src/calculations/matrices/get_submatrix.c \
				   src/calculations/matrices/inverse.c \
				   src/calculations/matrices/rotation_between_vectors.c \
				   \
				   src/shapes/sphere.c src/shapes/plane.c \
				   \
				   src/transformation/objects_transform.c src/transformation/view_transform.c \
				   \
				   \
				   \
				   src/display-config/debug_utils.c src/display-config/test_matrix_math.c \
				   src/display-config/test_matrix_transformation.c src/display-config/test_camera.c \
				   
				   
SRC_MAIN		:= src/main.c

OBJS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_MAIN		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_MAIN))

#for tarcking changes in header files
H_FILES			:= include/minirt_data.h include/minirt.h include/minirt_renderer.h \
				   include/minirt_math.h include/minirt_parser.h include/display_config.h

# RULES
all: update-submodule build-submodule $(NAME)

run: all
	./miniRT scene/simple.rt

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

# TESTING
TEST_MAIN		:= src/display-config/test_main.c
OBJ_TEST_MAIN		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_MAIN))

NAME_TEST		:= miniRT_test
CFLAGS_TEST		:= $(CFLAGS) -g -fsanitize=address

test: update-submodule build-submodule $(NAME_TEST)
	./miniRT_test

$(NAME_TEST): $(OBJS) $(OBJ_TEST_MAIN)
	$(CC) $(CFLAGS_TEST) $(OBJS) $(OBJ_TEST_MAIN) $(HDRS) $(LIBS) -o $(NAME_TEST)

tclean:
	$(RM) $(NAME_TEST)

.PHONY: all clean fclean re update-submodule build-submodule
