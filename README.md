# 42Cursus-Cube3D
This project is an integral part of the 42 Lisboa curriculum and aims to create a demonstration/game in C based on raycasting, using the graphics library [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)
Raycasting is a technique introduced in Wolfenstein 3D to render 3D graphics based on a 2D map. Essentially, raycasting works by sending rays from the player's point of view towards obstacles, calculating the distance each ray travels until it hits an object. With this distance, it is possible to draw obstacles (usually cubes) in perspective, creating the illusion of 3D space. See more about [Raycasting](https://en.wikipedia.org/wiki/Ray_casting).

## Table of Content

* [Map](#map)
* [Controls](#controls)
* [Examples](#examples)
* [Installation / Usage](#installation--usage)
* [License](#license)


## Map
The map is an essential part of raycasting because it defines the position of every object relative to the player. The player can navigate through the map to every allowed position.
The first four lines of the map file define the texture images that will be used in the four cardinal directions. Therefore, every wall will use the same texture based on its orientation in the map.
Above, there are two lines starting with 'F' and 'C' that define the colors of the floor and ceiling of the map. Above this is where the actual map starts.

```
NO ./textures/mossy.xpm  
SO ./textures/redbrick.xpm  
WE ./textures/redbrick.xpm  
EA ./textures/mossy.xpm

F 31,100,32  
C 140,189,214

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
1E00000000110000011DGC11111111111
111DGC11111111011100000010001
11110111111111011101010010001
1100000011010101A10000001000111A11111111
1000000000000000G00000001000000G00000001
1000000000000000B10101001000111B11110001
110000011101010111110111A000111    111101
11110111 1110101 1010000G0001          1
11111111 1111111 1111111B111
```

Map components:
- 1 -> Wall
- 0 -> Floor
- E -> Player start position
- G -> Gate (A, B, D, C are used to indicate the door orientation on the map, to correctly draw the sides of the door on the adjacent walls).

## Controls

- W, S, A, D -> Movement forward, backward, left, and right.
- Left and Right Arrow Keys -> Camera rotation.
- Mouse -> Camera rotation.
- ESC -> Exit.

## Examples

### Demo 3D
https://github.com/user-attachments/assets/7b76eb3a-500e-45c4-91fa-fb70a6381476

### Demo 2D
https://github.com/user-attachments/assets/0e81af1b-917a-4922-914e-55df97ab4d49

Here will be put images and videos

## Installation / Usage
This project is designed to work on Debian-based Linux distributions and macOS.

MiniLibX requires xorg, x11, and zlib to work on Debian-based Linux systems. For more information, see [MiniLibX Getting Started Guide](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html).
```shell
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

Clone repo:
```shell
git clone --recursive git@github.com:dspereira/42Cursus-Cube3D.git cub3d && cd cub3d
```

Build:
```shell
make
```

Usage example:
```shell
./cub3D maps/MapTest_001.cub
```

## License
This project is licensed under the [MIT License](https://github.com/dspereira/42Cursus-Cube3D/edit/main/LICENSE).
