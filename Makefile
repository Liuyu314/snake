snake : snake.c set_ticker.c
	gcc -o snake -l curses snake.c set_ticker.c
clean :
	rm -fr *.o
