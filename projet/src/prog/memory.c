

void write_f(int fd, Inode inode, int size, char *text){

  lseek(fd, inode, SEEK_SET);
  write(fd,text,size);
}

void read_f( int fd, Inode inode, int size, char *text) {
  bzero(text, sizeof(text));
  lseek( fd , inode, SEEK_SET);

  if (read(fd, text, size) == -1) {
    printf("ERROR WRITE: %s\n", strerror(errno));
    }

}

void clean_file(int fd, Inode inode){
  File_head fh;
  char text[SIZE_OF_FILE_HEAD];

  read_f(fd, inode, SIZE_OF_FILE_HEAD, text);
  fh = str_to_file_head(text);
  int number_of_inode = fh.size/BLOCK_SIZE_FOR_FILE +1;
  char tmp[BLOCK_SIZE_FOR_FILE]="\0\0\0\0\0\0";
  char str_inode[SIZE_OF_INODE];
  int index=0;
  Inode inode_to_clear;


  read_f(fd, inode, (number_of_inode+1)*SIZE_OF_INODE, text);
  for (size_t i = 0; i < number_of_inode; i++) {
    strncpy(str_inode, text+(i*SIZE_OF_INODE), SIZE_OF_INODE);
    inode_to_clear = atoi(str_inode);
    printf("[%d]\n", inode_to_clear);
    write_f(fd, INDEX_OF_INODE_TABLE+(inode_to_clear/BLOCK_SIZE_FOR_FILE), 1,"0");
  }
  write_f(fd, inode, SIZE_OF_INODE*(number_of_inode+1), tmp);
}


Address_List init_Address_List(){
  Address_List al;
  char list[SIZE_OF_INODE_TABLE];
  strcpy(list, "1");
	int i=0;
  for (i = 1; i < SIZE_OF_INODE_TABLE-1; i++) {
    strcpy(list+i, "0");
  }
  strcpy(al.address, list);
  return al;
}

void affiche_address_list(Address_List al){
  int i=0;
  for (i = 1; i < SIZE_OF_INODE_TABLE-1; i++) {
    printf("[%s]\n", al.address +i);
  }
}

Inode find_available_block(int fd, int cursor){
  Inode inode = 0;
  int index = 0;
  char chr[2];
  lseek(fd, cursor, SEEK_SET);
  do {
    index++;
    read(fd,chr,1);
  } while((strcmp(chr, "1") == 0) && (index<SIZE_OF_INODE_TABLE));
  write_f(fd, cursor+index-1, 1, "1");
  inode = (index-1)*BLOCK_SIZE_FOR_FILE;


  return inode;
}

void free_block(Address_List al, Inode inode_al, Inode inode){
  int index = inode/BLOCK_SIZE_FOR_FILE;
  strcpy(al.address+index, "0");



}

void create_file(int fd, char* filename, Inode inode, int root, int cursor_address_table, char file_type[1]){
  char text[BLOCK_SIZE_FOR_FILE];
  char str_inode[SIZE_OF_INODE];
  char info[SIZE_OF_INODE];
  char cat[SIZE_OF_FILE_HEAD+1];
  strcpy(cat, "0");
  File_head fh;
  int number_of_inode;
  Data_Block_List dbl;
  int sizeofinfo;
  Inode file_inode = find_available_block(fd, cursor_address_table);


  if (root) {

    fh = new_File_head();
    strcpy(fh.file_type, "d");
    strcpy(fh.name, filename);
    fh.address = file_inode;
    file_head_to_str(fh, text);
    write_f(fd, inode, SIZE_OF_FILE_HEAD, text);
    read_f(fd, inode, SIZE_OF_FILE_HEAD, text);
    //  print_File_head(fh);
    printf("Tete de fichier créé [%s]\n", text);


    //on ajoute l'inode
    sizeofinfo = sprintf(info, "%d", inode);
    while (sizeofinfo<SIZE_OF_INODE) {
      strcat(cat, info);
      strcpy(info, cat);
      bzero(cat, sizeof(cat));
      strcpy(cat, "0");
      sizeofinfo++;
    }

    bzero(text, sizeof(text));
    strncat(text, info, SIZE_OF_INODE);

    strcat(text, text);
    write_f(fd, fh.address, SIZE_OF_INODE*2, text);
    read_f(fd, fh.address, SIZE_OF_INODE*2, text);
    printf("Liste de blocs [%s]\n", text);


  }
  else{
    Inode data_block_inode = find_available_block(fd, cursor_address_table);
    Inode data_inode = find_available_block(fd, cursor_address_table);
    File_head new_fh = new_File_head();




    read_f(fd, inode, SIZE_OF_FILE_HEAD, text);
    fh = str_to_file_head(text);

    //on ajoute l'inode du fichier à la suite des inodes existantes
    read_f(fd, fh.address, SIZE_OF_INODE*(fh.size/BLOCK_SIZE_FOR_FILE), text);

    sizeofinfo = sprintf(info, "%d", file_inode);
    while (sizeofinfo<SIZE_OF_INODE) {
      strcat(cat, info);
      strcpy(info, cat);
      bzero(cat, sizeof(cat));
      strcpy(cat, "0");
      sizeofinfo++;
    }
    bzero(text, sizeof(text));
    strncat(text, info, SIZE_OF_INODE);
    fh.size += BLOCK_SIZE_FOR_FILE;
    number_of_inode = fh.size/BLOCK_SIZE_FOR_FILE;

    //mise à jout de la taille du dissier courant
    file_head_to_str(fh, text);
    write_f(fd, inode, SIZE_OF_FILE_HEAD, text);
    read_f(fd, inode, SIZE_OF_FILE_HEAD, text);

    bzero(text, sizeof(text));
    read_f(fd, fh.address, SIZE_OF_INODE*(number_of_inode-1), text);

    bzero(info, sizeof(info));
    sizeofinfo = sprintf(info, "%d", file_inode);
    while (sizeofinfo<SIZE_OF_INODE) {
      strcat(cat, info);
      strcpy(info, cat);
      bzero(cat, sizeof(cat));
      strcpy(cat, "0");
      sizeofinfo++;
    }
    strncat(text, info, SIZE_OF_INODE);
    write_f(fd, fh.address, SIZE_OF_INODE*(number_of_inode), text);


    //on écrit l'entête du fichier à l'adresse disponible

    strcpy(new_fh.file_type, "f");
    strcpy(new_fh.name, filename);
    new_fh.size = 0;
    new_fh.address = data_block_inode;
    file_head_to_str(new_fh, text);

    write_f(fd, file_inode, SIZE_OF_FILE_HEAD, text);
    read_f(fd, file_inode, SIZE_OF_FILE_HEAD, text);

    sizeofinfo = sprintf(info, "%d", data_inode);
    while (sizeofinfo<SIZE_OF_INODE) {
      strcat(cat, info);
      strcpy(info, cat);
      bzero(cat, sizeof(cat));
      strcpy(cat, "0");
      sizeofinfo++;
    }
    bzero(text, sizeof(text));
    strncat(text, info, SIZE_OF_INODE);

    write_f(fd, data_block_inode, SIZE_OF_INODE, text);
    read_f(fd, data_block_inode, SIZE_OF_INODE, text);
  }
}

void get_data_block(int fd, Inode inode, int block_number){

  char text[SIZE_OF_FILE_HEAD];
  read_f(fd, inode, SIZE_OF_FILE_HEAD, text);
  File_head fh = str_to_file_head(text);
  if (strcmp(fh.file_type, "d") == 0) {

    read_f(fd, fh.address + (block_number*SIZE_OF_INODE), SIZE_OF_INODE, text);
    printf("5 %s\n",text );
  }




}
