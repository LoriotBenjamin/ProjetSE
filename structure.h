#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>

typedef struct Disk Disk;
typedef struct Inode Inode;
typedef struct RepertoryBloc RepertoryBloc;
typedef struct DataBloc DataBloc;

struct Disk {
	Inode* inodes; // 15 inodes
	//DataBloc* dataBloc; // 30 blocs de 1024 octets 
};

struct Inode {
	char name[30];
	char permissions[8]; // rwxr--r--
	int type; // 1 = texte, 2 = binaire , ...
	int blockUsed[30]; // quels sont les blocs utilisés (max 30 ici)
	RepertoryBloc* repertoryBloc;  
	struct Inode* previousInode;
	struct Inode* nextInode;
};

struct RepertoryBloc {
	 Inode* tableInode;
	 int nbInode;
};

struct DataBloc {
	char data[1024]; // par exemple 1024 octets 
};

#endif // STRUCTURE_H
