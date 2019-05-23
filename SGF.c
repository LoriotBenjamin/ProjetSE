#include <stdio.h>

#include "SGF.h"

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
		fclose(file);
	}
	else {
		printf("Disk error\n");
	}	
}  
