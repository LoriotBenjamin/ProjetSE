#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

void createFile(Inode* inodeParent,Disk* disk, char* name) {


	Inode inode;

	int i =0;
	
	strcpy(inode.name, name);
	
	inode.type = TYPE_FICHIER;
	inode.test = 12;

	init_permissions(&inode);
	
	 printf("ici mon type est : %d",inode.type);
	if(inodeParent->type == TYPE_REPERTOIRE){
		//Pas trop compris la suite, j'sais pas si c'est bon :o
		DataBloc* dataBloc = malloc(sizeof(DataBloc));
		inode.dataBloc = dataBloc; 
	
		inode.previousInode = inodeParent;
		printf("coucou");

	}
	ajoutInodeDisk(inode,disk);

	ajoutInode(inode,inodeParent);

}
	// comment savoir à quel dossier appartient ce fichier ?
Inode changerRepertoire(char* arg1,Inode courant)
{		
	if(strcmp(arg1,"..")==0){
		if(courant.previousInode != NULL){
			printf("mon pere est %s \n",courant.previousInode->name);
			return *(courant.previousInode);
		}
		else
			printf("vous êtes a la racine \n");
	}
	else{
		for(int i=0;i<(courant.repertoryBloc->nbDeMesInode);i++){
				 
			if(courant.repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && strcmp(arg1,courant.repertoryBloc->mesInodes[i].name)==0){
				printf("retour de la fonction pour %s et %s est %d \n",arg1,courant.repertoryBloc->mesInodes[i].name,strcmp(arg1,courant.repertoryBloc->mesInodes[i].name) );
				courant.repertoryBloc->mesInodes[i].previousInode = &courant;
				printf("mon pere est %s \n",courant.repertoryBloc->mesInodes[i].name);
				Inode ino = courant.repertoryBloc->mesInodes[i];
				printf("mon pere est %s \n",courant.previousInode->name);
				return ino;
			}
			
				
		}
	}
	printf("pas de repertoire du nom de %s \n",arg1);
	return courant;
		
}

void afficherRepertoire(Inode* courant,Disk* disk)
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
/*
void afficherRepertoire(RepertoryBloc* repertory)
{
		for(int i=0;i<(repertory->nbInode);i++)
		{
			for(int j=0;j<NAME_SIZE;j++)
			{
				printf("%c",repertory->tableInode[i].name[j]);
			}
			printf("\n");
		}
}*/
/*
void creerRepertoire(char* name) 
{
	ajoutInode(disk);
	Inode *inode = get_inode(disk->inodesList.nb-1 , disk);
	inode->type = 2; 
	RepertoryBloc* repertoryBloc=malloc(sizeof(RepertoryBloc));
	inode->repertoryBloc=repertoryBloc;
}*/
void createRepertory(Inode* inodeParent,Disk* disk, char* name) {
	
	Inode inode ;

	int i =0;
	
	strcpy(inode.name, name);
	
	inode.type = TYPE_REPERTOIRE;

	init_permissions(&inode);
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
	ajoutInodeDisk(inode,disk);
	ajoutInode(inode,inodeParent);
}
