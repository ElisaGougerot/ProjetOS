
int lecture ( int fd, Inode inode, int taille, char *text) {

  lseek( fd , inode, SEEK_SET);
   text = read( inode, taille, DIM,fd);
  return text;

}
