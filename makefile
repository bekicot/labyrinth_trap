all:
	gcc main.c map.c position.c victim.c obstacles/rectangular.c maps/map_1.c door.c -lncurses -o labirin_trap