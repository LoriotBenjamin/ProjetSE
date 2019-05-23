#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "SGF.h"
#include "primitives.h"

int main (){
		
	while(1){

		//printf("%d",sizeof(unbloc));
		
		Disk disk;
		initialize_disk(&disk);
		load_disk(&disk);
		
		createFile(&disk, "firstFile.txt");

		printf("user@user ");

		char nameOrder[40]="\0";

		char separator;

		char arg1[40]="\0";

		char arg2[40]="\0";

		char buffer[100];

		fgets(buffer, 100, stdin);

		sscanf(buffer, "%s%c%s%c%s", nameOrder, &separator, arg1, &separator, arg2);

		printf("Name order : %s\n", nameOrder);
		printf("arg1: %s\n", arg1 );
		printf("arg2: %s\n", arg2 );

		// traitement de la commande 
	}
	return 0; 
}
