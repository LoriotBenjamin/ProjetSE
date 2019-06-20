#include <stdio.h>
#include <stdlib.h>
#include "SGF.h"

/***************************
Fonctions liées au disque
***************************/

void initialise_disque(Disque* disque) {	
  Inode new ;

  new.inodePost = NULL;
  new.type = TYPE_REPERTOIRE;
  new.inodePre = NULL;
  new.blocRepertoire = malloc(sizeof(BlocRepertoire));
  new.blocRepertoire->nbInodes = 0;
  strcpy(new.nom, "/"); // racine 

  //PERMISSIONS a faire ici

  disque->nbInodes = 0;

  //ajout dans la liste:
  disque->listeInodes[disque->nbInodes] = new;

  //mise a jour du nombre d'éléments
  disque->nbInodes += 1;

  printf("Success of the disque initialization\n");
}

void save_disque(Disque* disque) { 
  FILE* file = fopen("disque", "wb");

	if (file != NULL) {
		fwrite(&disque, sizeof(disque), 10000, file);  
		fclose(file);
	} else {
		printf("Disque error\n");
	}	
} 

void recuperer_disque(Disque* disque) {	
	FILE* file = fopen("disque", "rb");

	if (file != NULL) {
		fread(&disque, sizeof(disque), 10000, file);
		printf("Success of the disque load\n");
		fclose(file);
	}	else {
		printf("Disque error\n");
	}	
}  

/***************************
Fonctions liées aux inodes
***************************/

void init_permissions(Inode* inode) {
  /*
	char mode[3] = {'r', 'w', 'x'};
	int nbUsers = 0;
	while(nbUsers <= 3) {
		for(int i=0; i<=3; i++) {
			inode->permissions[nbUsers * 3 + i] = mode[i];
		}
		nbUsers++;
	}*/
}

void ajoutInodeDisque(Inode inode, Disque* disque) {
  if(disque->nbInodes < 200) {
    disque->listeInodes[disque->nbInodes] = inode; 
    disque->nbInodes += 1;
  } else {
    printf("plus d'espace disque");
  }
}

void ajoutInode(Inode inode, Inode* inodeParent) {
  if(inodeParent->blocRepertoire->nbInodes < 30) {
    inodeParent->blocRepertoire->listeInodes[inodeParent->blocRepertoire->nbInodes] = inode; 
    // printf("le nom de mon pere a peut etre change: %s \n", inode.inodePre->nom);
    inodeParent->blocRepertoire->nbInodes += 1;
  } else {
    printf("plus d'espace dans ce répertoire");
  }
}

/*
Inode *get_inode(int inodenum, Disque *disque) {//renvoie le maillon à l'indice précisé, si c'est possible
  if(inodenum == 0) { 
    return disque->inodesList.first;
  }

  if(inodenum > disque->inodesList.nb) {
    printf("System error trying to access inode %d: only %d inodes in disque\n", inodenum, disque->inodesList.nb);
    return NULL;   
  }

  Inode *current = disque->inodesList.first;
  for(int i = 0; i < inodenum; i++) {
    current = current->inodePost ;
	}
  return current;
}

void ajoutInode(Disque *disque) {//ajoute une inode libre dans le disque
  //initialisation:
  Inode *new = malloc(sizeof(Inode));
  Inode *last =  disque->inodesList.first;
  new->inodePost = NULL;
  new->type=0;
  
  //PERMISSIONS a faire ici

  //ajout dans la liste:
  if(disque->inodesList.first == NULL) {
    disque->inodesList.first = new;
    disque->inodesList.nb = 1;
    return;
  }
 
  while (last->inodePost != NULL) { 
    last = last->inodePost;
  } 
  last->inodePost = new;
  
  //mise a jour du nombre d'éléments
  disque->inodesList.nb += 1;
}*/
