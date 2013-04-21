p4_fs : p4_fs.o log.o
	gcc -g -o p4_fs p4_fs.o log.o `pkg-config fuse --libs`

p4_fs.o : p4_fs.c log.h params.h
	gcc -g -Wall `pkg-config fuse --cflags` -c p4_fs.c

log.o : log.c log.h params.h
	gcc -g -Wall `pkg-config fuse --cflags` -c log.c

clean:
	rm -f p4_fs *.o

