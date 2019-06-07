‘#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

void createFile(Disk* disk, char* name) {
	
	ajoutInode(disk);


	Inode *inode = get_inode(disk->inodesList.nb-1 , disk);

	strcpy(inode->name, name);
	inode->type = 0;

	init_permissions(inode);
	
	//Pas trop compris la suite, j'sais pas si c'est bon :o
	DataBloc* dataBloc = malloc(sizeof(DataBloc));
	inode->dataBloc = dataBloc; 
	
	// comment savoir à quel dossier appartient ce fichier ?
}
void afficherRepertoire(RepertoryBloc* repertory)
{
		for(int i=0;i<(repertory->nbInode);i++)
		{
			for(int j=0;j<NAME_SIZE;j++)
			{
				printf("%c",repertory->tableInode[i]->name[j]);
			}
			printf("\n");
		}
}
void creerRepertoire(char* name) 
{
	ajoutInode(disk);
	Inode *inode = get_inode(disk->inodesList.nb-1 , disk);
	inode->type = 2; 
	RepertoryBloc* repertoryBloc=malloc(sizeof(RepertoryBloc));
	inode->repertoryBloc=repertoryBloc;
}
