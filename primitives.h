#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdio.h>
#include "structure.h"

void createFile(Inode* inodeParent,Disk* disk, char* name);

//void afficherRepertoire(RepertoryBloc* repertory);

void afficherRepertoire(Inode* courant,Disk* disk);

void creerRepertoire(char* name);

void createRepertory(Inode* inodeParent,Disk* disk, char* name);

void changerRepertoire(char* arg1,Inode* courant);

void showCurrentRepository(Inode courant);

void supprimeFile (Inode* courant,char* arg1,Disk* disk);

void supprimeFileDisk(char* arg1,Disk* disk);
#endif // PRIMITIVES_H
