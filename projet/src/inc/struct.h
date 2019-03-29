//Toutes les structures de données du projet

//L'ionde est juste une adresse dans la mémoire
typedef int Inode;

//Tête de fichier
typedef struct{
  char file_type[1];
  int access;
  int links_number;
  int UID;//ID de l'utilisateur Pour vérifier qu'il à le droit de consulter le fichier
  int GID;//même chose mais pour le groupe
  int size;
  char name[SIZE_OF_FILE_NAME];
  Inode address;//adresse du block mémoire
}File_head;


typedef struct{
  Inode inode;
  int size;
}File;

typedef struct {
 char address[SIZE_OF_INODE_TABLE];
}Address_List;

typedef struct{
  Inode *inode;
}Data_Block_List;
