/**
 * \file constants.h
 * \author Jean-Philippe, Elisa, Raphaël
 * \version 0.1
 * \date 29 mars 2019
 *
 * Protype de fonction 
 *
 */

#include "constants.h"
#include "struct.h"


#include "file_head.h"

#include "../prog/init.c"
#include "memory.h"
#include "util.h"

int new_memory(int fd);

int init_Memory_Systeme(int fd, char *buff);

int open_Memory(char *filename);

void init_Address_Table(int fd);
