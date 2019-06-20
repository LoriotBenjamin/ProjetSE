#ifndef SGF_H
#define SGF_H

#include <stdio.h>
#include "structure.h"
#include "constantes.h"
#include <string.h>

/***************************
Fonctions liées au disque
***************************/

void sauver_disque(Disque* disque); 

void recuperer_disque(Disque* disque);

void initialise_disque(Disque* disque);


/***************************
Fonctions liées aux inodes
***************************/

void init_permissions(Inode* inode);

//void ajoutInode(Disque *disque);

//Inode *get_inode(int inodenum, Disque *disque);

void ajoutInode(Inode inode, Inode*	inodeParent);

void ajoutInodeDisque(Inode inode, Disque* disque);

#endif // SGF_H
