all:init_disk u_fs
init_disk:init_disk.o
	gcc    init_disk.o -o init_disk
u_fs:u_fs.o
	gcc u_fs.o -o u_fs -Wall -D_FILE_OFFSET_BITS=64 -g -pthread -lfuse -lrt -ldl
u_fs.o:u_fs.h u_fs.c
	gcc  -Wall -D_FILE_OFFSET_BITS=64 -g   -c -o u_fs.o u_fs.c
init_disk.o:u_fs.h init_disk.c
	gcc  -Wall -D_FILE_OFFSET_BITS=64 -g   -c -o init_disk.o init_disk.c
.PHONY : all
clean :
	rm  -f u_fs init_disk u_fs.o init_disk.o