void ecriture(int fd, Inode inode, int taille, char *text){

  lseek(fd, inode, SEEK_SET);
  write(fd,text,taille);
}
