
int open_Memory(char *filename){
  if (strcmp(filename, "")!=0) {
      int fd = open(filename,O_RDWR, 0666);
      if(fd == -1)
      printf("ERROR OPEN: %s\n", strerror(errno));
      else return fd;
  }
  else return open("memory.txt", O_CREAT|O_RDWR, 0666);

}

void init_Address_Table(int fd){
	int i=0;

		if (write(fd, "1", 1) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  		}
	for(i=1; i<SIZE_OF_INODE_TABLE-1; i++){
		if (write(fd, "0", 1) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  		}
	}
}

int new_memory(int fd) {
  char str[200] ="";
  int curpos =0;
  int size_str = sprintf(str, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                                                                              FILE_SYSTEM_NAME,
                                                                              MAX_MEMORY_SIZE,
                                                                              BLOCK_SIZE_FOR_FILE,
                                                                              SIZE_OF_INODE,
                                                                              SIZE_OF_INODE_TABLE,
                                                                              SIZE_OF_FILE_HEAD,
                                                                              SIZE_OF_ACCESS,
                                                                              SIZE_OF_LINKS_NUMBER,
                                                                              SIZE_OF_UID,
                                                                              SIZE_OF_GID,
                                                                              SIZE_OF_FILE
                                                                            );

  char buff[size_str];
  strcpy(buff, str);

  if (write(fd, buff, sizeof(buff)) == -1) {
    printf("ERROR WRITE: %s\n", strerror(errno));
  }
  curpos = size_str;
  init_Address_Table(fd);

  return curpos;
}

void load_Memory(char *filename){

}
