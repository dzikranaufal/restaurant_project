main: main.c menu.c utils.c order.c
	gcc main.c menu.c utils.c order.c -o main

clean:
	del *.o
	del main.exe
