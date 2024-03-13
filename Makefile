all: main

main: main.c
	gcc -g -o mem-stress-test main.c
debug: main
	gdb --args mem-stress-test -m 200
test: main
	./mem-stress-test -m 500 1000
