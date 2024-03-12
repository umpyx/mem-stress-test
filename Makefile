all: main

main: main.c
	gcc -g -o mem-stress-test main.c
debug:
	gdb --args mem-stress-test -m 200
