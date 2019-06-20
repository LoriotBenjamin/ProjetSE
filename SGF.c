#include <stdio.h>
#include <stdlib.h>
#include "SGF.h"

/***************************
Fonctions liées au disque
***************************/

// sauvegarde le disque
void sauver_disque(Disque* disque) { 
  FILE* file = fopen("disque", "wb");

	if (file != NULL) {
		fwrite(&disque, sizeof(disque), 10000, file);  
		fclose(file);
	} else {
		printf("Disque error\n");
	}	
} 

// initialise le disque
void initialise_disque(Disque* disque) {	
  Inode new ;

  new.inodePost = NULL;
  new.type = TYPE_REPERTOIRE;
  new.inodePre = NULL;
  new.blocRepertoire = malloc(sizeof(BlocRepertoire));
  new.blocRepertoire->nbInodes = 0;
  strcpy(new.nom, "/"); // racine 

  disque->nbInodes = 0;

  //ajout dans la liste:
  disque->listeInodes[disque->nbInodes] = new;

  //mise a jour du nombre d'éléments
  disque->nbInodes += 1;
}

// télécharge le disque
void recuperer_disque(Disque* disque) {	
	FILE* file = fopen("disque", "rb");

	if (file != NULL) {
		fread(&disque, sizeof(disque), 10000, file);
		fclose(file);
	}
} 

// affiche les inodes contenus dans le disque
void afficherInodes(Disque* disque) {	
	printf(" liste des inodes: ");
	for(int i=0; i<(disque->nbInodes); i++) { 
		printf(" %s  ", disque->listeInodes[i].nom);
	}	
	printf("\n");
}

/***************************
Fonctions liées aux inodes
***************************/

// initilise les permissions
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

// récupère un inode grâce à son nom
Inode* getInodeParNom(char* nomInode, Disque* disque){
	for(int i=0; i<(disque->nbInodes); i++) {
		if(strcmp(nomInode, disque->listeInodes[i].nom) == 0 ){
			return &(disque->listeInodes[i]);
		}
	}
	return NULL;	
}

// ajoute un inode
void ajoutInodeDisque(Inode inode, Disque* disque) {
  if(disque->nbInodes < MAX_INODES_DISQUE) {
    disque->listeInodes[disque->nbInodes] = inode; 
    disque->nbInodes += 1;
  } else {
    printf("plus d'espace disque");
  }
}

// ajoute un inode au disque
void ajoutInode(Inode inode, Inode* inodeParent) {
  if(inodeParent->blocRepertoire->nbInodes < MAX_INODES_REP) {
    inodeParent->blocRepertoire->listeInodes[inodeParent->blocRepertoire->nbInodes] = inode; 
    inodeParent->blocRepertoire->nbInodes += 1;
  } else {
    printf("plus d'espace dans ce répertoire");
  }
}


/***************************
Fonctions autres
***************************/

// décompose le chemin cible
Inode decouperCibleChemin (char* arg, Disque* disque) {  
	char* tab[MAX_INODES_DISQUE];
	char* cs = NULL;
	int i = 0;
	int nombreDeSeparateur = 0;

	for(int i=0; i<strlen(arg); i++){
		if(arg[i] == 47) { //  code ASCII du "/"
			nombreDeSeparateur++;
		}	
	}	

	char string[500]; // commande de 500 caracteres max
	strcpy(string, arg);
  char *p;
 	p = strtok(string, "/");
	while (p != NULL) {
		tab[i] = p;
		i++;
		p = strtok(NULL, "/");
	}
	return chercherCibleChemin(tab[nombreDeSeparateur-1], tab[nombreDeSeparateur-2], disque);
}

// cherche la cible
Inode chercherCibleChemin(char* nom, char * nomParent, Disque* disque) {	// Pour les futurs chemins 
	for(int i=0; i<(disque->nbInodes); i++) {
		if(strcmp(nom,disque->listeInodes[i].nom) == 0 && strcmp(nomParent,disque->listeInodes[i].inodePre->nom) == 0) {
			return disque->listeInodes[i];
		}
	}
}