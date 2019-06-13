#ifndef SGF_H
#define SGF_H

#include <stdio.h>
#include "structure.h"
#include "constantes.h"
#include <string.h>

// ***** disk functions *****

void save_disk(Disk* disk); 

void load_disk(Disk* disk);

void initialize_disk(Disk* disk);

// ***** inode functions *****

void init_permissions(Inode* inode);

//void ajoutInode(Disk *disk);

//Inode *get_inode(int inodenum, Disk *disk);

void ajoutInode(Inode inode,Inode*	 inodeParent);

void ajoutInodeDisk(Inode inode,Disk* disk);


#endif // SGF_H
