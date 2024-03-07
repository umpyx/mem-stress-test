all: main

main: main.c
	gcc -g -o mem-stress-test main.c
