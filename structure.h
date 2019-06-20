#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include "constantes.h"

/***************************
Déclaration
***************************/

// Structure Inode
typedef struct Inode Inode;

// Structure Disque
typedef struct Disque Disque;

// Structure BlocRepertoire
typedef struct BlocRepertoire BlocRepertoire;

// Structure BlocDonnees
typedef struct BlocDonnees BlocDonnees;


/***************************
Définition
***************************/

// Structure Inode
struct Inode { 
	char nom[NOM_TAILLE];
	char permissions[PERMISSION_TAILLE];
	int type; // 0 = fichier, 1 = répertoire
	int blocUtilise[NB_BLOCS_UTILISES]; // 30 blocs utilisés max
	int test;
	BlocRepertoire* blocRepertoire;
	BlocDonnees* blocDonnees;  
	Inode* inodePre;
	Inode* inodePost;
};

// Structure Disque
struct Disque {
	Inode listeInodes[MAX_INODES_DISQUE]; // 200 inodes max sur le disque
	int nbInodes;
};

// Structure BlocRepertoire
struct BlocRepertoire {
	 Inode listeInodes[MAX_INODES_REP];	// 20 inodes max par dossier 
	 int nbInodes ;
};

// Structure BlocDonnees
struct BlocDonnees {
	char donnees[BLOC_DONNEES_TAILLE];
};

#endif // STRUCTURE_H
