#!/bin/bash

echo "=== DEBUG CUB3D ==="
echo "1. Verificando archivos de texturas:"
ls -la assets/textures/*.xpm | head -10

echo -e "\n2. Verificando mapa bonus_doors.cub:"
cat assets/maps/bonus_doors.cub

echo -e "\n3. Verificando is_walk() en check_map_utils.c:"
grep -A5 "is_walk" src/parse/check_map_utils.c

echo -e "\n4. Verificando SPRITE_FRAMES:"
grep "SPRITE_FRAMES" include/*.h

echo -e "\n5. Compilando con debug..."
make re CFLAGS="-Wall -Wextra -Werror -g -DDEBUG"

echo -e "\n6. Ejecutando con valgrind:"
valgrind --leak-check=full --track-origins=yes ./cub3D assets/maps/bonus_doors.cub 2>&1 | head -50