# 42Cursus-Cube3D

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
