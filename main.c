#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"


int main(){

	Disk disk;
	initialize_disk(&disk);
	load_disk(&disk);
	//createFile(&disk, "firstFile.txt");
	Inode courant;
	Inode pere; 
	courant= disk.listeDesInodes[0];
	pere = courant; 

	//char test [200];

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

		//printf("Name order : %s\n", nameOrder);
		//printf("arg1: %s\n", arg1 );
		//printf("arg2: %s\n", arg2 );

	
		//Inode test = decoupeCibleChemin (arg1,&disk);
		//printf("nom du fichier cible: %s \n",test.name);



		if(strcmp(nameOrder,"touch") == 0){
			if(strcmp(arg1,"\0")){
				createFile(&courant,&disk,arg1);
				printf("DEBUG : Nombre d'inodes : %d\n",disk.nombreDinode);
			}

		}else if(strcmp(nameOrder,"cd") == 0){
			if(strcmp(arg1,"\0")){

					printf("pére avant sortie de la fonction %s \n",pere.name);
					printf("parent avant entrée de la fonction %s \n",courant.previousInode->name);
				
					changerRepertoire(arg1,&courant,&pere);
					printf("parent de courant aprés sortie de la fonction %s \n",courant.previousInode->name);
					printf("pére aprés sortie de la fonction %s \n",pere.name);

					//printf("DEBUG : mon papa name : %s\n",courant.previousInode->name);
					//printf("DEBUG : mon premier frere de mes freres : %s\n",courant.previousInode->repertoryBloc->mesInodes[0].name);
					//printf("DEBUG : je suis : %s\n",courant.name);
					//printf("DEBUG : mon papa name : %s\n",courant.previousInode->name);	
			}

		}else if(strcmp(nameOrder,"rm") == 0){
			if(strcmp(arg1,"\0")){
				supprimeFichier(&courant,arg1,&disk);
			}

		}else if(strcmp(nameOrder,"rmdir") == 0){
			if(strcmp(arg1,"\0")){
				supprimeRepertoire(&courant,arg1,&disk);
			}

		}else if(strcmp(nameOrder,"ecrit") == 0){
			ecrireDansFichier(arg1,arg2,&disk);
		

		}else if(strcmp(nameOrder,"ls") == 0){
			afficherRepertoire(arg1,&courant,&disk);
		

		}else if(strcmp(nameOrder,"cat") == 0){
			if(strcmp(arg1,"\0"))
				afficherDataFichier(&courant,arg1,&disk);
		

		}else if(strcmp(nameOrder,"echo") == 0){
			if(strcmp(arg1,"\0"))
				afficheArg(arg1,arg2);
		

		}else if(strcmp(nameOrder,"pwd") == 0){
			showCurrentRepository(courant);
		

		}else if(strcmp(nameOrder,"wc") == 0){
			if(strcmp(arg1,"\0"))
				compterMots(&courant,arg1);
		

		}else if(strcmp(nameOrder,"mkdir") == 0){
			if(strcmp(arg1,"\0")){
				createRepertory(&courant,&disk,arg1);
				printf("DEBUG : Nombre d'inodes : %d\n",disk.nombreDinode);
			}

		}else if(strcmp(nameOrder,"exit") == 0){
            //save_disk(&disk);
		    return 0;

		}else if(strcmp(nameOrder,"cp") == 0){
			
			copyFile(chercheCibleChemin(arg1,courant.name,&disk),arg2,&disk);	

		}else if(strcmp(nameOrder,"mv") == 0){
			
			deplacerFile(chercheCibleChemin(arg1,courant.name,&disk),arg2,&disk);
		}else{
			printf("%s : command not found\n", nameOrder);

		}

		// traitement de la commande 

		afficherAllInodes(&disk);
	}// fin du shell

	free(courant.repertoryBloc);
	free(pere.repertoryBloc);

	return 0; 
}
