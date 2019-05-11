all: res_sys.c
	gcc -Wall -std=c99 -g -o fta res_sys.c
clean:
	rm fta
