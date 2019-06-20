#ifndef SGF_H
#define SGF_H

#include <stdio.h>
#include "structure.h"
#include "constantes.h"
#include <string.h>

/***************************
Fonctions liées au disque
***************************/

// sauvegarde le disque
void sauver_disque(Disque* disque); 

// initialise le disque
void initialise_disque(Disque* disque);

// télécharge le disque
void recuperer_disque(Disque* disque);

// affiche les inodes contenus dans le disque
void afficherInodes(Disque* disque);


/***************************
Fonctions liées aux inodes
***************************/

// initilise les permissions
void init_permissions(Inode* inode);

// récupère un inode grâce à son nom
Inode* getInodeParNom(char* nomInode, Disque* disque);

// ajoute un inode
void ajoutInode(Inode inode, Inode*	inodeParent);

// ajoute un inode au disque
void ajoutInodeDisque(Inode inode, Disque* disque);


/***************************
Fonctions autres
***************************/

// décompose le chemin cible
Inode decouperCibleChemin(char* arg, Disque* disque);

// cherche la cible
Inode chercherCibleChemin(char* nom, char * nomParent, Disque* disque);

#endif // SGF_H
