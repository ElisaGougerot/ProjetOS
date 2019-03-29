

File_head new_File_head(){
	File_head fh;

	strcpy(fh.file_type, "-");
	fh.access = 777;
	fh.links_number = 1;
	fh.UID = 1;
	fh.GID = 1;
	fh.size = 2*BLOCK_SIZE_FOR_FILE;
	fh.address = 0;
	strcpy(fh.name, "fichier vide");
	return fh;
}

File_head get_File_head(int fd, Inode inode){
	File_head fh;
	char text[SIZE_OF_FILE_HEAD+1]="";
	lseek(fd, inode, SEEK_SET);
	int access, links_number, UID, GID, size, adresse;

    //initialisation  du type de fichier
	if (read(fd, fh.file_type, SIZE_OF_FILE_TYPE) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  }
	bzero(text, sizeof(text));

  //initialisation  du type d'acces
	if (read(fd, text, SIZE_OF_ACCESS) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  }
	fh.access = atoi(text);
	bzero(text, sizeof(text));

  //initialisation  du nombre de lien
	if (read(fd, text, SIZE_OF_LINKS_NUMBER) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  }
	fh.links_number = atoi(text);
	bzero(text, sizeof(text));

  //initialisation  du numero utilisateur
	if (read(fd, text, SIZE_OF_UID) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  }
	fh.UID = atoi(text);
	bzero(text, sizeof(text));

  //initialisation  du nombre de lien
	if (read(fd, text, SIZE_OF_GID) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  }
	fh.GID = atoi(text);
	bzero(text, sizeof(text));

  //initialisation  de la taille du fichier
	if (read(fd, text, SIZE_OF_FILE) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  }
	fh.size = atoi(text);
	bzero(text, sizeof(text));

  //initialisation  de la taille de l'adresse
	if (read(fd, text, SIZE_OF_INODE) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
  }
	fh.address= atoi(text);
	bzero(text, sizeof(text));

	// initialisation du nom
	if (read(fd, fh.name, SIZE_OF_FILE_NAME) == -1) {
			printf("ERROR WRITE: %s\n", strerror(errno));
	}
	bzero(text, sizeof(text));

	return fh;
}

void file_head_to_str(File_head fh, char * str){
	char info[SIZE_OF_FILE_HEAD+1];
	char cat[SIZE_OF_FILE_HEAD+1];
	strcpy(cat, "0");
	int sizeofinfo = 0;
	int index = 0;
	bzero(str, sizeof(str));

	//on ajoute le type de fichier
	sizeofinfo = sizeof(fh.file_type);

	if (sizeofinfo<SIZE_OF_FILE_TYPE) {strcat(info, "-");}
	else{str = strncat(str, fh.file_type,1);}

	// on ajoute les autorisation d'acces
	sizeofinfo = sprintf(info, "%d", fh.access);
	while (sizeofinfo<SIZE_OF_ACCESS) {
		sizeofinfo = sprintf(info, "0%s", info);
	}
	strcat(str, info);
	bzero(info, sizeof(info));

	//on ajoute le nombre de liens
	sizeofinfo = sprintf(info, "%d", fh.links_number);
	while (sizeofinfo<SIZE_OF_LINKS_NUMBER) {
		strcat(cat, info);
		strcpy(info, cat);
		bzero(cat, sizeof(cat));
		strcpy(cat, "0");
		sizeofinfo++;
	}
	strcat(str, info);
	bzero(info, sizeof(info));

	//on ajoute l'ID de l'utilisateur
	sizeofinfo = sprintf(info, "%d", fh.UID);
	while (sizeofinfo<SIZE_OF_UID) {
		strcat(cat, info);
		strcpy(info, cat);
		bzero(cat, sizeof(cat));
		strcpy(cat, "0");
		sizeofinfo++;
	}
	strcat(str, info);
	bzero(info, sizeof(info));

	//on ajoute l'ID du groupe
	sizeofinfo = sprintf(info, "%d", fh.GID);
	while (sizeofinfo<SIZE_OF_GID) {
		strcat(cat, info);
		strcpy(info, cat);
		bzero(cat, sizeof(cat));
		strcpy(cat, "0");
		sizeofinfo++;
	}
	strcat(str, info);
	bzero(info, sizeof(info));

	//on ajoute la taille du fichier
	sizeofinfo = sprintf(info, "%d", fh.size);
	while (sizeofinfo<SIZE_OF_FILE) {
		strcat(cat, info);
		strcpy(info, cat);
		bzero(cat, sizeof(cat));
		strcpy(cat, "0");
		sizeofinfo++;
	}
	strcat(str, info);
	bzero(info, sizeof(info));

	//on ajoute l'inode
	sizeofinfo = sprintf(info, "%d", fh.address);
	while (sizeofinfo<SIZE_OF_INODE) {
		strcat(cat, info);
		strcpy(info, cat);
		bzero(cat, sizeof(cat));
		strcpy(cat, "0");
		sizeofinfo++;
	}
	strcat(str, info);
	bzero(info, sizeof(info));

	//on ajoute le nom du fichier
	strcat(str, fh.name);

}

File_head str_to_file_head(char *str){
	int index = 0;
	char info[32]="";
	File_head fh = new_File_head();
	char text[50];
	strcpy(text, str);

	//printf("info[%s]\n", info);
	strncat(info, str,SIZE_OF_FILE_TYPE);
	strcpy(fh.file_type, info);
	index = SIZE_OF_FILE_TYPE;
	bzero(info, sizeof(info));

	strncat(info, str+index,SIZE_OF_ACCESS);
	fh.access = atoi(info);
	index+=SIZE_OF_ACCESS;
	bzero(info, sizeof(info));

	strncat(info, str+index,SIZE_OF_LINKS_NUMBER);
	fh.links_number = atoi(info);
	index+=SIZE_OF_LINKS_NUMBER;
	bzero(info, sizeof(info));

	strncat(info, str+index,SIZE_OF_UID);
	fh.UID = atoi(info);
	index+=SIZE_OF_UID;
	bzero(info, sizeof(info));

	strncat(info, str+index,SIZE_OF_GID);
	fh.GID = atoi(info);
	index+=SIZE_OF_GID;
	bzero(info, sizeof(info));


	strncat(info, str+index,SIZE_OF_FILE);
	fh.size = atoi(info);
	index+=SIZE_OF_FILE;
	bzero(info, sizeof(info));

	strncat(info, str+index,SIZE_OF_INODE);
	fh.address = atoi(info);
	index+=SIZE_OF_INODE;
	bzero(info, sizeof(info));

	strcpy(fh.name, str+index);

	 return fh;
}

void print_File_head(File_head fh){
	printf("type de fichier [%s]\nacces [%d]\nnombre de lien [%d]\nID utilisateur [%d]\nID groupe [%d]\ntaille du fichier [%d]\nInode [%d]\nname [%s]\n",
					 	fh.file_type,
						fh.access,
						fh.links_number,
						fh.UID,
						fh.GID,
						fh.size,
						fh.address,
						fh.name
				);
}
