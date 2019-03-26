
void lecture ( int fd, Inode inode, int taille, char *text) {
  bzero(text, sizeof(text));
  lseek( fd , inode, SEEK_SET);
  read(fd, text, taille);

}
