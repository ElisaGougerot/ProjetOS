

void printShell(char *msg){
  printf("%s\n>", msg);
}

void getCmd(void) {
  int quit=0;
  char cmd[30]="";
  while (quit!=1) {
    scanf("%s", cmd);
    if (strcmp(cmd, "")==0) {
      printf("rien :[%s]\n", cmd);
      printShell("");
    }
    else if (strcmp(cmd, "help")==0) {
      printShell("command help");
    }
    else if (strcmp(cmd, "q")==0) {
      quit=1;
    }
    else{
      printShell("invalid cmd type help for help");
    }
    strcpy(cmd, "");
  }
}

int getMemoryMaxSize(int fd){
  char buff[100]="";
  char ch[2];
  lseek(fd, 0, SEEK_SET);
  while ((read(fd, ch, 1) == 1) && (strcmp(ch, "\n")!=0)) {
    strcat(buff, ch);
    strcpy(ch, "");
  }
  return atoi(buff);
}

int getCurrentMemorySize(int fd){
  char buff[100]="";
  char ch[2];
  lseek(fd, 0, SEEK_SET);
  while ((read(fd, ch, 1) == 1) && (strcmp(ch, "\n")!=0)) {
  }

  while ((read(fd, ch, 1) == 1) && (strcmp(ch, "\n")!=0)) {
    strcat(buff, ch);
    strcpy(ch, "");
  }
  return atoi(buff);
}

void affiche_memory(){
	char chr[2];
	int fd = open("memory.txt", O_CREAT|O_RDWR, 0666);
	while(read(fd, chr, 1) == 1){
		printf("%s", chr);
	}
  printf("\n");
}

void write_in_file(int fd, Inode inode, char *text, int size_text){
  File_head fh;
  char text_file_head[SIZE_OF_FILE_HEAD];
  char info[BLOCK_SIZE_FOR_FILE];
  char new[BLOCK_SIZE_FOR_FILE];
  char cat[SIZE_OF_FILE_HEAD+1]="0";
  Inode new_inode;
  int sizeofinfo;

  read_f(fd, inode, SIZE_OF_FILE_HEAD, text_file_head);
  fh = str_to_file_head(text_file_head);
  fh.size = sizeof(text);

  clean_file(fd, fh.address);
  int i = 0;

  for (i = 0; i < (size_text/BLOCK_SIZE_FOR_FILE); i++) {
      new_inode = find_available_block(fd, INDEX_OF_INODE_TABLE);

      write_f(fd, new_inode, BLOCK_SIZE_FOR_FILE, text+(i*BLOCK_SIZE_FOR_FILE));
      read_f(fd, new_inode, BLOCK_SIZE_FOR_FILE, new);
      printf("[%s] current read\n", new);
      sizeofinfo = sprintf(info, "%d", new_inode);
      while (sizeofinfo<SIZE_OF_INODE) {
        strcat(cat, info);
        strcpy(info, cat);
        bzero(cat, sizeof(cat));
        strcpy(cat, "0");
        sizeofinfo++;
      }
      strncpy(new, info, SIZE_OF_INODE);
  }
  new_inode = find_available_block(fd, INDEX_OF_INODE_TABLE);

  write_f(fd, new_inode, size_text-(i*BLOCK_SIZE_FOR_FILE), text+(i*BLOCK_SIZE_FOR_FILE));
  read_f(fd, new_inode, size_text-(i*BLOCK_SIZE_FOR_FILE), info);


  sizeofinfo = sprintf(info, "%d", new_inode);
  while (sizeofinfo<SIZE_OF_INODE) {
    strcat(cat, info);
    strcpy(info, cat);
    bzero(cat, sizeof(cat));
    strcpy(cat, "0");
    sizeofinfo++;
  }
  strncpy(new, info, SIZE_OF_INODE);

  printf("[%s] current read\n", new);
  write_f(fd, fh.address, BLOCK_SIZE_FOR_FILE, new);
  write_f(fd, new_inode, size_text-(i*BLOCK_SIZE_FOR_FILE), text+(i*BLOCK_SIZE_FOR_FILE));
  read_f(fd, new_inode, size_text-(i*BLOCK_SIZE_FOR_FILE), new);
  printf("[%s]fin\n", new);

}
