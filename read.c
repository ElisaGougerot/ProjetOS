
int read( int fd, Inode inode, int taille) {

  fd = open( "donnee.txt"  ,O_RDONLY);

  lseek( fd , inode, SEEK_SET);
  fread( inode, taille, DIM,fd);

}
