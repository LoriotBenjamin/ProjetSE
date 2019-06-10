#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

void createFile(Inode* inodeParent,Disk* disk, char* name) {// 				touch


	Inode inode;

	int i =0;

	for(i=0;i< (inodeParent->repertoryBloc->nbDeMesInode);i++){

	}
	
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

void supprimeFichier (Inode* courant,char* arg1,Disk* disk){
	
	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
		if(courant->repertoryBloc->mesInodes[i].type==TYPE_FICHIER && strcmp(arg1,courant->repertoryBloc->mesInodes[i].name)==0){
			supprimeFileDisk(arg1,disk,courant->repertoryBloc->mesInodes[i].type);
			
			courant->repertoryBloc->nbDeMesInode = courant->repertoryBloc->nbDeMesInode-1;
			for(i;i<(courant->repertoryBloc->nbDeMesInode);i++){// faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
				 // si on arrive au bout du tableau
				if(courant->repertoryBloc->mesInodes[i+1].type == TYPE_FICHIER || courant->repertoryBloc->mesInodes[i+1].type == TYPE_REPERTOIRE )
					courant->repertoryBloc->mesInodes[i]=courant->repertoryBloc->mesInodes[i+1];
			}
		}
	}
	
}
void supprimeFichier2 (Inode* courant,char* arg1,Disk* disk){	// besoin pour la récursivité
	
	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
		if(courant->repertoryBloc->mesInodes[i].type==TYPE_FICHIER && strcmp(arg1,courant->repertoryBloc->mesInodes[i].name)==0){
			supprimeFileDisk(arg1,disk,courant->repertoryBloc->mesInodes[i].type);
			
	
			
		}
	}
	
}
// pour le débug 
void afficherAllInodes(Disk* disk){

	printf(" liste des inodes: ");
	for(int i=0;i<(disk->nombreDinode);i++)
		printf(" %s  ",disk->listeDesInodes[i].name);
	printf("\n");
	

}

void supprimeRepertoire (Inode* courant,char* arg1,Disk* disk){
	printf("nom de tout mes inodes \n");
	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
		printf("%s ",courant->repertoryBloc->mesInodes[i].name);
	}
	printf("\n");
	int tamp = 0;

	printf(" je suis lancé et le courant est : %s \n",courant->name);
	printf("je demande de supprimer: %s \n",arg1);

	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
		if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && strcmp(arg1,courant->repertoryBloc->mesInodes[i].name)==0){
			tamp = i;

			if(courant->repertoryBloc->mesInodes[i].repertoryBloc->nbDeMesInode == 0){// pas de fils
				printf("je passe la \n");
				supprimeFileDisk(arg1,disk,courant->repertoryBloc->mesInodes[i].type);
				courant->repertoryBloc->nbDeMesInode = courant->repertoryBloc->nbDeMesInode-1;
			

			}else{	// le repertoir a des fils 
					//supprimeFileDisk(arg1,disk,courant->repertoryBloc->mesInodes[i].type); à voir 
				
					for(int j=0;j<(courant->repertoryBloc->mesInodes[i].repertoryBloc->nbDeMesInode);j++){ // suppression des fils
						printf(" nb inodes: %d\n",courant->repertoryBloc->mesInodes[i].repertoryBloc->nbDeMesInode);
						printf("j=%d \n",j);
						printf("i=%d \n",i);

						if(courant->repertoryBloc->mesInodes[i].repertoryBloc->mesInodes[j].type== TYPE_REPERTOIRE){
							printf("je lance moi meme\n");
							supprimeRepertoire(&(courant->repertoryBloc->mesInodes[i]),courant->repertoryBloc->mesInodes[i].repertoryBloc->mesInodes[j].name,disk);	// TODO PARTIE RECURSIF A TESTER!!
							
						}
						else{
							supprimeFichier2(&(courant->repertoryBloc->mesInodes[i]),courant->repertoryBloc->mesInodes[i].repertoryBloc->mesInodes[j].name,disk);
						}

					
					}// fin suppression des fils 
					supprimeFileDisk(arg1,disk,courant->repertoryBloc->mesInodes[i].type);

				

			}	
			

		}// apres la suppresion demande

		

	}
	courant->repertoryBloc->nbDeMesInode = courant->repertoryBloc->nbDeMesInode-1;
	for(int i=tamp;i<(courant->repertoryBloc->nbDeMesInode);i++){// faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
	 // si on arrive au bout du tableau
		if(courant->repertoryBloc->mesInodes[i+1].type == TYPE_FICHIER || courant->repertoryBloc->mesInodes[i+1].type == TYPE_REPERTOIRE )
			courant->repertoryBloc->mesInodes[i]=courant->repertoryBloc->mesInodes[i+1];
	
	}
}

void supprimeFileDisk(char* arg1,Disk* disk,int typeAEffacer){

	for(int i=0;i<(disk->nombreDinode);i++){
		if(strcmp(arg1,disk->listeDesInodes[i].name)==0 && typeAEffacer ==disk->listeDesInodes[i].type ){
	
			
			disk->nombreDinode = disk->nombreDinode-1;
			for(i;i<(disk->nombreDinode);i++){// faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
				 // si on arrive au bout du tableau
				if(disk->listeDesInodes[i+1].type == TYPE_FICHIER || disk->listeDesInodes[i+1].type == TYPE_REPERTOIRE )
					disk->listeDesInodes[i]= disk->listeDesInodes[i+1];
				
			
			}

		}

	}
	

}

void decoupeCibleChemin (char* arg){
	char* tab[200];// si tout les inodes sont mit bout à bout sachant qu'on ne peut qu'en avoir 200
	char* cs =NULL;
	int nombreDeSeparateur = 0;
	for(int i=0;i<strlen(arg);i++){
		if(arg[i] == 47)//  code ASCII du /
			nombreDeSeparateur++;
	}	
	for(int i=0;i<nombreDeSeparateur;i++){
		tab[i]=strtok(arg,"/");
	}
	printf("il y a %d \n",nombreDeSeparateur);
	// ce qui nous interesse c'est seulement la cible et son parent pour être certain de l'identifier


}
Inode chercheCibleChemin(char* name,char * nameOfParent,Disk* disk){
	
	for(int i=0;i<(disk->nombreDinode);i++){
		//if(strcmp(name,disk->listeDesInodes[i].name) )

	}

}

void changerRepertoire(char* arg1,Inode* courant,Inode * pere)	// 				cd 
{
	if(strcmp(arg1,"..")==0){
		if(strcmp(arg1,"..")==0){
			if(courant->previousInode != NULL){
				printf("mon papoulle est : %s \n",pere->name);
				
				if(courant->previousInode != NULL){
					*courant = *pere;
					if(pere->previousInode != NULL)
						*pere = *pere->previousInode;
					

				}
			}
			else
				printf("vous êtes a la racine \n");
		}
	}
	else{
		for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
				 
			if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && strcmp(arg1,courant->repertoryBloc->mesInodes[i].name)==0){
				
				
				Inode tampon = *courant;

				
				*courant= courant->repertoryBloc->mesInodes[i];
				
				courant->previousInode= pere;

				if(pere->previousInode != NULL){
					*pere = tampon;
				}

				
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
/* 
void copyFile(Inode* inodeFichier,Disk* disk,char* dest)
{
	Inode inode;

	int i =0;
	char* dest_fin,dest_pred;
	inode=*(inodeFichier);
	dest_fin=strtok(dest,"/");
    while (dest_fin!=NULL)
    {
			dest_pred=dest_fin;
			dest_fin = strtok (dest, "/");
    }	
    for(i=0;i<=disk->nombreDinode;i++)
    {
		if(disk->listeDesInodes[i].nom==dest_fin && disk->listeDesInodes[i].previousInode->nom==dest_pred && disk->listeDesInodes[i].type==TYPE_REPERTOIRE)
		{
			inode.previousInode=disk->listeDesInodes[i];
			ajoutInodeDisk(inode,disk);
			ajoutInode(inode,listeDesInodes[i]);
		}
		else if(disk->listeDesInodes[i].nom==dest_fin && disk->listeDesInodes[i].previousInode->nom==dest_pred && disk->listeDesInodes[i].type==TYPE_FICHIER)
		{
			inode.previousInode=disk->listeDesInodes[i].previousInode;
			supprimeFile(listeDesInodes[i].previousInode,dest_fin,disk);
			ajoutInodeDisk(inode,disk);
			ajoutInode(inode,listeDesInodes[i].previousInode);
		}
		else
			printf("Destination non trouvée\n");
	}
	
}
void deplacerFile(Inode* inodeFichier,char* dest, Disk* disk)
{
	copyFile(inodeFichier,disk,dest);
	supprimeFile(inodeFichier->name,disk);
}
*/
