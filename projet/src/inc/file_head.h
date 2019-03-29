/**
 * \file constants.h
 * \author Jean-Philippe, Elisa, Raphaël
 * \version 0.1
 * \date 29 mars 2019
 *
 * Définition des macros de notre file system
 *
 */

#include "../prog/file_head.c"


File_head new_File_head();

File_head str_to_file_head(char *str);

void print_File_head(File_head fh);

File_head get_File_head(int fd, Inode inode);
