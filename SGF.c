#include <stdio.h>

#include "SGF.h"

// ***** disk functions *****

void initialize_disk(Disk* disk){	
	disk->inodes = NULL;
	//disk->dataBloc = NULL;

	printf("Success of the disk initialization\n");
}

void save_disk(Disk* disk){ 
    FILE* file = fopen("disk", "wb");
	if (file != NULL){
		fwrite(&disk, sizeof(disk), 10000, file);  
		fclose(file);
	}
	else {
		printf("Disk error\n");
	}	
} 

void load_disk(Disk* disk){	
	FILE* file = fopen("disk", "rb");
	if (file != NULL){
		fread(&disk, sizeof(disk), 10000, file);
		printf("Success of the disk load\n");
		fclose(file);
	}
	else {
		printf("Disk error\n");
	}	
}  

// ***** inode functions *****

void init_permissions(Inode* inode) {
	char mode[3] = {'r', 'w', 'x'};
	int nbUsers = 0;
	while(nbUsers <= 3) {
		for(int i=0; i<=3; i++) {
			inode->permissions[nbUsers * 3 + i] = mode[i];
		}
		nbUsers++;
	}
}
