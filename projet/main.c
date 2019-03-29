
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

////////////////
#include "src/inc/init.h"

//////////////


int main(int argc, char const *argv[]) {
  // char input[100]="", scn[100]="";
  // printf("\t\tFILE MANAGER\n\tby pauquet jean-philippe\n>");
  // for (size_t i = 0; sizeof("100")+i < 8; i++) {
  //   printf("|");
  // }
  // printf("%s", "100\n");
  // int val = 100 - 16;
  // char str[7]="";
  // sprintf(str, "%d", val);
  // for (size_t i = 0; sizeof(str)+i < 8; i++) {
  //   printf("|");
  // }
  // printf("%s\n", str);
  // /*
  // int fd = new_memory(30);
  // getMemoryMaxSize(fd);
  // getCurrentMemorySize(fd);
  // getCmd();
  // */



int fd = open_Memory("");
char text[SIZE_OF_INODE_TABLE+1];
char test[SIZE_OF_FILE_HEAD];
int cursor = new_memory(fd);
int cursor_address_table = cursor;
Inode current_folder_inode;
printf("TAB[%d]\n", cursor);
read_f(fd, cursor_address_table, SIZE_OF_INODE_TABLE, text);
printf("[%s]\n", text);
Inode current = find_available_block(fd, cursor_address_table);
read_f(fd, cursor_address_table, SIZE_OF_INODE_TABLE, text);
printf("[%s]\n", text);

create_file(fd, ".", current, 1, cursor_address_table, "d");

create_file(fd, "file.txt", current, 0, cursor_address_table, "f");

char pk[30] = "YEEEEEEEES YESSSSS !";
write_in_file(fd, 3072, pk, sizeof(pk));

//get_data_block(fd, current, 0);

  return 0;
}
