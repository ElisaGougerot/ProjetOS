#include "../prog/memory.c"

Address_List init_Address_List();

Inode find_available_block(int fd, int cursor);

void free_block(Address_List al, Inode inode_al, Inode inode);

void write_f(int fd, Inode inode, int size, char *text);

void read_f( int fd, Inode inode, int size, char *text);
