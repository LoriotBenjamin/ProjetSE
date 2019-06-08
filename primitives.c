#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

void createFile(Inode* inodeParent,Disk* disk, char* name) {
	
	//ajoutInode(disk);


	Inode inode ;

	int i =0;
	
	strcpy(inode.name, name);
	
	inode.type = TYPE_FICHIER;

	init_permissions(&inode);
	if(inodeParent->type == TYPE_REPERTOIRE){
		//Pas trop compris la suite, j'sais pas si c'est bon :o
		DataBloc* dataBloc = malloc(sizeof(DataBloc));
		inode.dataBloc = dataBloc; 
		inode.previousInode = &inodeParent;
		printf("coucou");
		//inodeParent->repertoryBloc->tableInode = realloc(inodeParent->repertoryBloc->tableInode, inodeParent->repertoryBloc->nbInode+1 * sizeof(Inode));
		//inodeParent->repertoryBloc->nbInode++;
		//inodeParent->repertoryBloc->tableInode[inodeParent->repertoryBloc->nbInode]=inode;
	}
	ajoutInodeDisk(inode,disk);
	ajoutInode(inode,inodeParent);

}
	// comment savoir à quel dossier appartient ce fichier ?


void afficherRepertoire(Inode* courant,Disk* disk)
{		
		
		//printf(" je suis : %s \n",courant->name);
		for(int i=0;i<=(courant->repertoryBloc->nbDeMesInode);i++)
			printf("%s  ",courant->repertoryBloc->mesInodes[i].name);
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
	/*
	ajoutInode(disk);


	Inode *inode = get_inode(disk->inodesList.nb-1 , disk);

	strcpy(inode->name, name);
	inode->type = TYPE_REPERTOIRE;

	init_permissions(inode);
	if(inodeParent->type == TYPE_REPERTOIRE){
		
		
		//inode->repertoryBloc = malloc(sizeof(RepertoryBloc)); 
		inode->previousInode = inodeParent;
	}*/
}
