# 3D Maze Game project

## Description
This project aims to create a 3D Maze game using C, SDL2, and Raycasting.

## Directory Structure

|Directory or file name | Description |
|------------------------|-------------|
| ./dependencies/        | store all header files |
| ./src/                 | store all source code |
| ./README.md            | the main README of the project

## Building and Compilation
To compile the project, use the following GCC flags:
```
gcc -Wall -Werror -Wextra -pedantic -o maze src/*.c -Idependencies -lSDL2 -lSDL2_image
```

## Usage
- Run the executable to start the 3D Maze game.
```
./maze
```

## Style Guide
Follow the Betty styling guidelines for maintaining a consistent coding style.

## License
This project is licensed under the [MIT License](LICENSE).

