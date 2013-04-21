p4_fs : p4_fs.o
	gcc -g -o p4_fs p4_fs.o `pkg-config fuse --libs`

p4_fs.o : p4_fs.c params.h
	gcc -g -Wall `pkg-config fuse --cflags` -c p4_fs.c

clean:
	rm -f p4_fs *.o

