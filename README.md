<div align="center">
<p><a href="https://www.hive.fi/en/curriculum">Hive (42 School Network)</a></p>  

<h1>MiniRT</h1> 

</div>

#### Introduction   
MiniRT is a rendering program that uses ray tracing technology to create realistic images with a given configuration.  

#### Table of Contents  
- [Features](#features)  
- [Project structure](#project-structure)  
- [Installation](#installation)  

## Features  

- [x] Scene description parsed from `.rt` files.  
- [ ] Custom math and vector utilities.   
- [ ] Real-time rendering with MLX42 (42 School's graphical library).  
- [ ] Simple ray tracer supporting spheres, planes, and cylinders.  
- [ ] Point and ambient lighting with basic shading.  
- [ ] Camera with field of view and orientation control.  

## Project structure

```css
ray-tracing/
│
├── include/                  # Header files
│   ├── minirt_data.h
│   └── minirt.h
│
├── lib/                      # Libraries
│   ├── libft/                # Submodule libft
│   └── mlx42/                # Submodule MLX42
│
├── scene/                    # Scene config files
│   └── simple.rt
│
├── src/                      # Source files
│   ├── constructor/
│   │   └── *.c
│   ├── destructor/
│   │   └── *.c
│   ├── parser/
│   │   └── *.c
│   └── main.c
│
├── ...
└── Makefile                  # Building project tool

```   

## Installation   

1. Clone the repository and build the project using the provided `Makefile`:  
```bash
git clone https://github.com/ipersids/ray-tracing.git
cd ray-tracing
make
```   

2. Run the ray tracer with the path to the config file:  
```bash
./miniRT scene/simple.rt
```  

**Other commands:**  
	* `make clean` will remove all .o' files.  
	* `make fclean` will remove all .o' and executable files.  
	* `make re` will trigger the fclean command and rebuild the program.    

**Linker dependencies:**   

| Flag | Library | Purpose|
|------|---------|--------|
| `-ldl` | libdl | Dynamic linking support |
| `-lglfw` | GLFW | OpenGL window/context/input handling |
| `-lm` | libm | C math library |
| `-lmlx42`| MLX42 | Cross-platform, minimal windowing graphics library |
| `-lft`  | libft |  Own customized version of the standard C library |   

________  
<div align="center">

<p>Developed by <a href="https://github.com/EggInAVest">Roni Eerikainen</a> and <a href="https://github.com/ipersids">Julia Persidskaia</a>.</p>

</div>