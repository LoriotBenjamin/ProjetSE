#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"
#include "structure.h"
int main(){
	Disk disk;
	initialize_disk(&disk);
	load_disk(&disk);
	//createFile(&disk, "firstFile.txt");
	Inode courant;
	Inode pere; 
	courant= disk.listeDesInodes[0];
	pere = courant; 

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

		}else if(strcmp(nameOrder,"cd") == 0){
			if(strcmp(arg1,"\0")){
				
					printf("DEBUG : mon papa name : %s\n",courant.previousInode->name);	// todo ici le pére est déja perdu

					changerRepertoire(arg1,&courant,&pere);
					//printf("DEBUG : mon papa name : %s\n",courant.previousInode->name);
					//printf("DEBUG : mon premier frere de mes freres : %s\n",courant.previousInode->repertoryBloc->mesInodes[0].name);
					//printf("DEBUG : je suis : %s\n",courant.name);

			}

		}else if(strcmp(nameOrder,"rm") == 0){
			if(strcmp(arg1,"\0")){
				supprimeFichier(&courant,arg1,&disk);
			}

		}else if(strcmp(nameOrder,"rmdir") == 0){
			if(strcmp(arg1,"\0")){
				supprimeRepertoire(&courant,arg1,&disk);
			}

		}else if(strcmp(nameOrder,"ls") == 0){
			afficherRepertoire(&courant,&disk);
		

		}else if(strcmp(nameOrder,"pwd") == 0){
			showCurrentRepository(courant);
		

		}else if(strcmp(nameOrder,"mkdir") == 0){
			if(strcmp(arg1,"\0")){
				createRepertory(&courant,&disk,arg1);
				printf("DEBUG : Nombre d'inodes : %d\n",disk.nombreDinode);
			}

		}else if(strcmp(nameOrder,"quitter") == 0){
            		printf("je vais quitter\n");
            		save_disk(&disk);
		    	break;

		}else{
			printf("erreur il faut entrer un nom de fichier \n");

		}

		// traitement de la commande 
	}
	return 0; 
}
