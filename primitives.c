#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

void createFile(Disk* disk, char* name) {
	Inode* inode = malloc(sizeof(Inode));
	
	strcpy(inode->name, name);
	
	init_permissions(inode);
	
	DataBloc* dataBloc = malloc(sizeof(DataBloc));
	inode->dataBloc = dataBloc; 
	
	//disk->inodes->nextInode = inode;
}
