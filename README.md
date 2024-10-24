# 42Cursus-Cube3D
This project is an integral part of the 42 Lisboa curriculum and aims to create a demonstration/game based on raycasting, using the graphics library [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)
Raycasting is a technique introduced in Wolfenstein 3D to render 3D graphics based on a 2D map. Essentially, raycasting works by sending rays from the player's point of view towards obstacles, calculating the distance each ray travels until it hits an object. With this distance, it is possible to draw obstacles (usually cubes) in perspective, creating the illusion of 3D space. See more about [Raycasting](https://en.wikipedia.org/wiki/Ray_casting).

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
