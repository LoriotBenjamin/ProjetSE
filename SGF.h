#ifndef SGF_H
#define SGF_H

#include <stdio.h>
#include "structure.h"

// ***** disk functions *****

void save_disk(Disk* disk); 

void load_disk(Disk* disk);

void initialize_disk(Disk* disk);

// ***** inode functions *****

void init_permissions(Inode* inode);

#endif // SGF_H
