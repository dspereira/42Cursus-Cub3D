#!/bin/bash

echo $#

if [$# -eq 1];
then
	echo "Invalid Number of Args" && exit 1
else
	make re
	echo "------------------------------------------------"
	./cub3D $@
	echo "------------------------------------------------"
	make fclean
fi
