#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdio.h>
#include "structure.h"

void createFile(Inode* inodeParent,Disk* disk, char* name);
void afficherRepertoire(RepertoryBloc* repertory);
void creerRepertoire(char* name);

void createRepertory(Inode* inodeParent,Disk* disk, char* name);
#endif // PRIMITIVES_H
