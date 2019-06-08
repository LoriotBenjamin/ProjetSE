#include <stdio.h>
#include <stdlib.h>
#include "SGF.h"

// ***** disk functions *****

void initialize_disk(Disk* disk){	

	disk-> inodesList.first = NULL;
	disk-> inodesList.nb=0;

  //////////////////////////////
	Inode *new = malloc(sizeof(Inode));

  Inode *last =  disk->inodesList.first;
  new->nextInode = NULL;
  new->type=TYPE_REPERTOIRE;
  strcpy(new->name,"/"); //racine 
  
  //PERMISSIONS a faire ici

  //ajout dans la liste:
  if (disk->inodesList.first == NULL)
  {
    disk->inodesList.first = new;
    disk->inodesList.nb = 1;
    return;
  }
  while (last->nextInode != NULL)
    last = last->nextInode;
  last->nextInode = new;
  
  //mise a jour du nombre d'éléments
  disk->inodesList.nb += 1;

  //////////////////////////////

	printf("Success of the disk initialization\n");
}

void save_disk(Disk* disk){ 
    FILE* file = fopen("disk", "wb");
	if (file != NULL){
		fwrite(&disk, sizeof(disk), 10000, file);  
		fclose(file);
	}
	else {
		printf("Disk error\n");
	}	
} 

void load_disk(Disk* disk){	
	FILE* file = fopen("disk", "rb");
	if (file != NULL){
		fread(&disk, sizeof(disk), 10000, file);
		printf("Success of the disk load\n");
		fclose(file);
	}
	else {
		printf("Disk error\n");
	}	
}  

// ***** inode functions *****

void init_permissions(Inode* inode) {
	char mode[3] = {'r', 'w', 'x'};
	int nbUsers = 0;
	while(nbUsers <= 3) {
		for(int i=0; i<=3; i++) {
			inode->permissions[nbUsers * 3 + i] = mode[i];
		}
		nbUsers++;
	}
}

Inode *get_inode(int inodenum, Disk *disk)
{//renvoie le maillon à l'indice précisé, si c'est possible
  if (inodenum == 0)
    return disk->inodesList.first;
  if (inodenum > disk->inodesList.nb)
  {
    printf("System error trying to access inode %d: only %d inodes in disk\n"
           , inodenum, disk->inodesList.nb);
    return NULL;   
  }

  Inode *current = disk->inodesList.first;
  for (int i = 0; i < inodenum; i++){
    current = current->nextInode;
	}

  return current;
}

void ajoutInode(Disk *disk)
{//ajoute une inode libre dans le disque

  //initialisation:
  Inode *new = malloc(sizeof(Inode));
  Inode *last =  disk->inodesList.first;
  new->nextInode = NULL;
  new->type=0;
  
  //PERMISSIONS a faire ici

  //ajout dans la liste:
  if (disk->inodesList.first == NULL)
  {
    disk->inodesList.first = new;
    disk->inodesList.nb = 1;
    return;
  }
  while (last->nextInode != NULL)
    last = last->nextInode;
  last->nextInode = new;
  
  //mise a jour du nombre d'éléments
  disk->inodesList.nb += 1;
}
