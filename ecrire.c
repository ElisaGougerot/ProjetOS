int ecriture(int fd, Inode inode, int taille, char *text){

  lseek(fd, inode, SEEK_SET);
  text = write(inode,taille,DIM,fd);

  return text;
}
