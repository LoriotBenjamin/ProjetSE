#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include "constantes.h"

//typedef struct InodeList InodeList;
typedef struct Disk Disk;
typedef struct Inode Inode;
typedef struct RepertoryBloc RepertoryBloc;
typedef struct DataBloc DataBloc;



struct Inode {
	char name[NAME_SIZE];
	char permissions[PERMISSION_SIZE];
	int type; // 1 = texte, 2 = binaire , ...
	int blockUsed[30]; // quels sont les blocs utilisés (max 30 ici)
	int test;
	RepertoryBloc* repertoryBloc;
	DataBloc* dataBloc;  
	Inode* previousInode;
	Inode* nextInode;
};


struct Disk {
	//Inode* inodes; // 15 inodes
	Inode listeDesInodes[200]; // 200 inodes max 

	int nombreDinode;
};

struct RepertoryBloc {
	 Inode mesInodes[20];
	 int nbDeMesInode ;
};

struct DataBloc {
	char data[DATA_BLOC_SIZE];
};

#endif // STRUCTURE_H
