int write(int fd, Inode inode, int taille){

  fd = open("donnee.txt", O_CREAT|O_RDWR, 0666);

  lseek(fd, inode, SEEK_SET);
  fwrite(inode,taille,DIM,fd);

}
