#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdio.h>
#include "structure.h"

void createFile(Inode* inodeParent,Disk* disk, char* name);

//void afficherRepertoire(RepertoryBloc* repertory);

void afficherRepertoire(Inode* courant,Disk* disk);

void creerRepertoire(char* name);

void createRepertory(Inode* inodeParent,Disk* disk, char* name);

void changerRepertoire(char* arg1,Inode* courant, Inode* pere);

void showCurrentRepository(Inode courant);

void supprimeFichier (Inode* courant,char* arg1,Disk* disk);

void supprimeFichier2 (Inode* courant,char* arg1,Disk* disk);

void supprimeRepertoire (Inode* courant,char* arg1,Disk* disk);

void supprimeFileDisk(char* arg1,Disk* disk,int typeAEffacer);

void afficherAllInodes(Disk* disk);

void decoupeCibleChemin (char* arg);

Inode chercheCibleChemin(char* name,char * nameOfParent,Disk* disk);
#endif // PRIMITIVES_H
