#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "SGF.h"
#include "primitives.h"

int main (){
		
	Disk disk;
	initialize_disk(&disk);
	load_disk(&disk);
	//createFile(&disk, "firstFile.txt");
	Inode courant;
	courant= disk.listeDesInodes[0];
	while(1){

		//printf("%d",sizeof(unbloc));

		printf("user@%s ",courant.name);

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


		if(strcmp(nameOrder,"touch") == 0){
			if(strcmp(arg1,"\0")){
				createFile(&courant,&disk,arg1);
				printf("DEBUG : Nombre d'inodes : %d\n",disk.nombreDinode);
			}

		}else if(strcmp(nameOrder,"ls") == 0){
			afficherRepertoire(&courant,&disk);
		

		}else if(strcmp(nameOrder,"mkdir") == 0){
			if(strcmp(arg1,"\0")){
				createRepertory(&courant,&disk,arg1);
				printf("DEBUG : Nombre d'inodes : %d\n",disk.nombreDinode);
			}

		}else if(strcmp(nameOrder,"cd") == 0){
			if(strcmp(arg1,"\0")){
				courant=changerRepertoire(arg1,courant);
				printf("DEBUG : mon papa : %s\n",courant.previousInode->name);
			}

		}else
			printf("erreur il faut entrer un nom de fichier \n");

		// traitement de la commande 
	}
	return 0; 
}


