#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

void createFile(Inode* inodeParent,Disk* disk, char* name) {// 				touch


	Inode inode;

	int i =0;
	
	strcpy(inode.name, name);
	
	inode.type = TYPE_FICHIER;
	inode.test = 12;

	//init_permissions(&inode);
	
	if(inodeParent->type == TYPE_REPERTOIRE){
		//Pas trop compris la suite, j'sais pas si c'est bon :o
		DataBloc* dataBloc = malloc(sizeof(DataBloc));
		inode.dataBloc = dataBloc; 
	
		inode.previousInode = inodeParent;
	

	}
	ajoutInodeDisk(inode,disk);

	ajoutInode(inode,inodeParent);

}
	// comment savoir à quel dossier appartient ce fichier ?
void changerRepertoire(char* arg1,Inode* courant)	// 				cd 
{		
	if(strcmp(arg1,"..")==0){
		if(strcmp(arg1,"..")==0){
			if(courant->previousInode != NULL){
				printf("mon papoulle est : %s \n",courant->previousInode);
				
				if(courant->previousInode != NULL){
					*courant = *(courant->previousInode);
				}
			}
			else
				printf("vous êtes a la racine \n");
		}
	}
	else{
		for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
				 
			if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && strcmp(arg1,courant->repertoryBloc->mesInodes[i].name)==0){
				
				/*
				printf("retour de la fonction pour %s et %s est %d \n",arg1,courant.repertoryBloc->mesInodes[i].name,strcmp(arg1,courant.repertoryBloc->mesInodes[i].name) );
				
				printf("mon papou est %s \n",courant.previousInode->name);

				printf("ça devrait etre la racine et %s \n",courant.repertoryBloc->mesInodes[i].previousInode->name);

				Inode ino = courant.repertoryBloc->mesInodes[i];
				printf("je retourne %s \n",ino.name);
				printf("mon papa du retour %s  \n",ino.previousInode->name);
				*/
				Inode inoPere = *courant;
				*courant= courant->repertoryBloc->mesInodes[i];
				courant->previousInode= &inoPere;
				break;

			}
			
			printf("DEBUG : mon papa name : %s\n",courant->previousInode->name);
		}
		
	}


		
}
void showCurrentRepository(Inode courant){
	printf("%s \n",courant.name);
}
void afficherRepertoire(Inode* courant,Disk* disk) // 				ls
{		
		
		printf(" je suis : %s \n",courant->name);
		printf(" j'ai  : %d inodes \n",courant->repertoryBloc->nbDeMesInode);
		for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
			 
			if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE)
				printf ("\033[34;01m%s\033[00m  ",courant->repertoryBloc->mesInodes[i].name);
			else
				printf("%s  ",courant->repertoryBloc->mesInodes[i].name);
		}
		printf("\n");
}

void createRepertory(Inode* inodeParent,Disk* disk, char* name) {// 				mkdir
	
	Inode inode ;

	int i =0;
	
	strcpy(inode.name, name);
	
	inode.type = TYPE_REPERTOIRE;

	//init_permissions(&inode);
	if(inodeParent->type == TYPE_REPERTOIRE){
		//Pas trop compris la suite, j'sais pas si c'est bon :o
		DataBloc* dataBloc = malloc(sizeof(DataBloc));
		inode.dataBloc = dataBloc; 
		inode.previousInode = inodeParent;
		printf("le nom de mon pére est33 : %s \n",inodeParent->name);
		printf("j'ia enregistre: %s \n",inode.previousInode->name);
		inode.repertoryBloc= malloc(sizeof(RepertoryBloc));
  		inode.repertoryBloc->nbDeMesInode=0;

	}
	printf("le nom de mon pére est33 : %s \n",inodeParent->name);
		printf("j'ia enregistre: %s \n",inode.previousInode->name);
	ajoutInodeDisk(inode,disk);
	ajoutInode(inode,inodeParent);
}
