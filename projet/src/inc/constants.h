/**
 * \file constants.h
 * \author Jean-Philippe, Elisa, Raphaël
 * \version 0.1
 * \date 29 mars 2019
 *
 * Définition des macros de notre file system
 *
 */


#ifndef CONSTANTS
#define CONSTANTS

#define FILE_SYSTEM_NAME "--FILE SYSTEME--\n"
//  Memory
#define MAX_MEMORY_SIZE 1048576 //taille total de la mémoire
#define BLOCK_SIZE_FOR_FILE 1024  //taille d'un block
#define SIZE_OF_INODE 6 //nombre de caractère pour ecrire un inode
#define SIZE_OF_INODE_TABLE 128 //nombre d'inode dans la table d'inodes
#define INDEX_OF_INODE_TABLE 50

//macros pour une tête de fichier
#define SIZE_OF_FILE_TYPE 1
#define SIZE_OF_ACCESS 3
#define SIZE_OF_LINKS_NUMBER 2
#define SIZE_OF_UID 3
#define SIZE_OF_GID 3
#define SIZE_OF_FILE 7
#define SIZE_OF_FILE_NAME 30
#define SIZE_OF_FILE_HEAD SIZE_OF_FILE_TYPE + SIZE_OF_ACCESS + SIZE_OF_LINKS_NUMBER + SIZE_OF_UID + SIZE_OF_GID + SIZE_OF_FILE + SIZE_OF_INODE + SIZE_OF_FILE_NAME

#endif
