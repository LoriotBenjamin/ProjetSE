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
		DataBloc* dataBloc = malloc(30*sizeof(DataBloc));
		inode.dataBloc = dataBloc; 
	
		inode.previousInode = inodeParent;
	}
	ajoutInodeDisk(inode,disk);

	ajoutInode(inode,inodeParent);

}
// pour le débug 
void afficherAllInodes(Disk* disk){	// pour debug

	printf(" liste des inodes: ");
	for(int i=0;i<(disk->nombreDinode);i++)
		printf(" %s  ",disk->listeDesInodes[i].name);
	printf("\n");
	

}
void afficherDataFichier(Inode* courant, char* nomDufichier,Disk* disk){ // cat 
		
			int i=0;
			int j=0;
			if(getInodeByName(nomDufichier,disk)!= NULL){
				Inode* inodeAEcrire = getInodeByName(nomDufichier,disk);

				for(j=0;j<30;j++){
					for(i=0;i< sizeof(inodeAEcrire->dataBloc[j].data);i++){
						printf("%c",inodeAEcrire->dataBloc[j].data[i]);
					}
					printf("bloc %d \n",j);
				}

				printf("valeur de j à la fin de la boucle: %d",j);
				printf("\n");
			}
			else{
				printf("le fichier n'existe pas dans ce repertoire \n");
			}

}
// pour débug
void ecrireDansFichier(char* nomDufichier,char* aEcrire,Disk* disk){
			printf("inode mal recupere: \n");
			Inode* inodeAEcrire = getInodeByName(nomDufichier,disk);
			printf("inode bien recupere: %s \n",inodeAEcrire->name);

			if(strlen(aEcrire)<1024)
				strcpy(inodeAEcrire->dataBloc[0].data,aEcrire);

			int i=0;
			for(i=0;i< sizeof(inodeAEcrire->dataBloc[1].data);i++){
				printf(" %c",inodeAEcrire->dataBloc[1].data[i]);
			}
			printf("valeur de i à la fin de la boucle: %d",i);
			printf("\n");
}


Inode* getInodeByName(char* nomInode,Disk* disk){
	printf("je veu l'inode du nom de : %s \n",nomInode);
	for(int i=0;i<(disk->nombreDinode);i++){
		if(strcmp(nomInode,disk->listeDesInodes[i].name)==0 ){
			printf("inode trouve son nom est : %s \n",disk->listeDesInodes[i].name);
			return &(disk->listeDesInodes[i]);
		}
	}
	return NULL;	
}

void supprimeFichier (Inode* courant,char* arg1,Disk* disk){	// rm
	
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


void afficheArg(char* arg1,char* arg2){	// echo
	if(strcmp(arg1,"\0") && strcmp(arg2,"\0"))
		printf("%s %s \n",arg1,arg2);
	else 
		printf("%s \n",arg1);
	
}

void supprimeRepertoire (Inode* courant,char* arg1,Disk* disk){	// rmdir
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

void supprimeFileDisk(char* arg1,Disk* disk,int typeAEffacer){	// RMDIR

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

Inode decoupeCibleChemin (char* arg,Disk* disk){
	char* tab[200];
	char* cs =NULL;
	int i=0;
	int nombreDeSeparateur = 0;
	for(int i=0;i<strlen(arg);i++){
		if(arg[i] == 47)//  code ASCII du /
			nombreDeSeparateur++;
	}	

	char string[500] ;// commande de 500 caracteres max
	strcpy(string,arg);
  	char *p;
 	 printf ("String  \"%s\" is split into tokens:\n",string);
 	 p = strtok (string,"/");
	  while (p!= NULL)
	  {
	  	tab[i]= p;
	    i++;
	    printf ("%s\n",p);
	    p = strtok (NULL, "/");

	   
	  }
	return chercheCibleChemin(tab[nombreDeSeparateur-1],tab[nombreDeSeparateur-2],disk);


}

Inode chercheCibleChemin(char* name,char * nameOfParent,Disk* disk){	// Pour les futurs chemins 
	printf("je cherche un inode du nom de : %s \n",name);
	printf("avec comme pere : %s \n",nameOfParent);
	for(int i=0;i<(disk->nombreDinode);i++){
		printf(" 1 : %s  2: %s 3: %s 4:%s",name,disk->listeDesInodes[i].name,nameOfParent,disk->listeDesInodes[i].previousInode->name); // le "disk->listeDesInodes[i].previousInode->name" ( 4: ...) renvoie le mauvais nom 
		if(strcmp(name,disk->listeDesInodes[i].name)==0 && strcmp(nameOfParent,disk->listeDesInodes[i].previousInode->name) ==0)
		{
			printf(" loltes1 : %s",disk->listeDesInodes[i].name);
			return disk->listeDesInodes[i];

		}
	}

}
void changerRepertoire(char* arg1,Inode* courant,Inode * pere)	// 				cd 
{
	if(strcmp(arg1,"..")==0){
		if(strcmp(arg1,"..")==0){
			if(courant->previousInode != NULL){
				printf("mon papoulle est : %s \n",pere->name);
				printf("je suis  : %s \n",courant->name);
				
				if(strcmp(courant->name,"/")!=0){
					*courant = *pere ;
					courant->previousInode=pere;
					

					if(strcmp(courant->name,"/")!=0){
						printf("le pére du courant qu'on vient de changer est %s  \n",courant->previousInode->name);
						printf("nom du courant aprés assignation du pere %s \n",courant->name);
						pere = courant->previousInode;
					}

					

				}
			}
			else
				printf("vous êtes a la racine \n");
		}
	}
	else{
		for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++){
				 
			if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && strcmp(arg1,courant->repertoryBloc->mesInodes[i].name)==0){
				
				

				if(strcmp(courant->name,"/")!=0){
					*pere = *courant;
					//printf(" nom du courant juste apres son assgination %s ",courant->name);
				}

				
				*courant = courant->repertoryBloc->mesInodes[i];
				
				courant->previousInode= pere ;

				//printf("parent aprés assignation %s \n",courant->previousInode->name);
				printf("le grand pere de courant est  :%s",courant->previousInode->previousInode->name);
				

				
				break;

			}
			
			//printf("DEBUG : mon papa name : %s\n",courant->previousInode->name);

		}
		
	}


		
}

void showCurrentRepository(Inode courant){	// PWD
	printf("%s \n",courant.name);
}
void afficherRepertoire(char* arg1, Inode* courant,Disk* disk) // 				ls
{	
	printf(" je suis : %s \n",courant->name);
	printf(" j'ai  : %d inodes \n",courant->repertoryBloc->nbDeMesInode);
	if(strcmp(arg1,"-C")==0)
   	{
       		for(int i;i<(courant->repertoryBloc->nbDeMesInode);i++)
       		{
            		if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && courant->repertoryBloc->mesInodes[i].name[0] !='.')
                		printf ("\033[34;01m%s\033[00m  \n",courant->repertoryBloc->mesInodes[i].name);
            		else if (courant->repertoryBloc->mesInodes[i].name[0] !='.')
                		printf("%s  \n",courant->repertoryBloc->mesInodes[i].name);
        	}
    	}
   	else if (strcmp(arg1,"-F")==0)
   	{
        	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++)
        	{
            		if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && courant->repertoryBloc->mesInodes[i].name[0] !='.')
                		printf ("\033[34;01m%s\033[00m/  ",courant->repertoryBloc->mesInodes[i].name);
           		/*else if (courant->repertoryBloc->mesInodes[i].type==TYPE_EXECUTABLE)
                		printf("%s*  ",courant->repertoryBloc->mesInodes[i].name);*/
            		else if (courant->repertoryBloc->mesInodes[i].name[0] !='.')
                	printf("%s  ",courant->repertoryBloc->mesInodes[i].name);
        	}
    	}
    	else if (strcmp(arg1,"-R")==0)
    	{
        	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++)
        	{
        		if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && courant->repertoryBloc->mesInodes[i].name[0] !='.')
            		{
                		printf ("\033[34;01m%s\033[00m  ",courant->repertoryBloc->mesInodes[i].name);
                		for(int j=0;j<(courant->repertoryBloc->nbDeMesInode);j++)
                		{
                    			if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && courant->repertoryBloc->mesInodes[i].name[0] !='.')
                        			printf ("\033[34;01m%s\033[00m  ",courant->repertoryBloc->mesInodes[i].name);
                    			else if (courant->repertoryBloc->mesInodes[i].name[0] !='.')
                        			printf("%s  ",courant->repertoryBloc->mesInodes[i].name);
                		}
            		}
            		else
                		printf("%s  ",courant->repertoryBloc->mesInodes[i].name);
        	}
    	}
    	else if (strcmp(arg1,"-d")==0)
    	{
        	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++)
        	{
            		printf("%s  ",courant->repertoryBloc->mesInodes[i].name);
        	}
    	}
    	else if (strcmp(arg1,"-i")==0)
    	{
        	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++)
        	{
            		if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && courant->repertoryBloc->mesInodes[i].name[0] !='.')
			{
				printf ("%d",i);
                		printf ("%d\033[34;01m%s\033[00m  \n",i,courant->repertoryBloc->mesInodes[i].name);
			}
            		else if (courant->repertoryBloc->mesInodes[i].name[0] !='.')
			{
				printf ("%d",i);
                		printf("%d%s  \n",i,courant->repertoryBloc->mesInodes[i].name);
			}
        	}
    	}
	else if (strcmp(arg1,"-t")==0)
    	{
        	for(int i=(courant->repertoryBloc->nbDeMesInode)-1;i>0;i--)
        	{
            		if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && courant->repertoryBloc->mesInodes[i].name[0] !='.')
                		printf ("\033[34;01m%s\033[00m",courant->repertoryBloc->mesInodes[i].name);
            		else if (courant->repertoryBloc->mesInodes[i].name[0] !='.')
				printf ("%d",i);
                		printf("%s",courant->repertoryBloc->mesInodes[i].name);
        	}
    	}
	/*else if (strcmp(arg1,"-a")==0)
	{
        	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++)
        	{
        	  	if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE)
        		        printf ("\033[34;01m%s\033[00m  \n",i,courant->repertoryBloc->mesInodes[i].name);
            		else
                		printf("%s  \n",i,courant->repertoryBloc->mesInodes[i].name);
        	}
	}
    	*/else
    	{
        	for(int i=0;i<(courant->repertoryBloc->nbDeMesInode);i++)
        	{
        		if(courant->repertoryBloc->mesInodes[i].type==TYPE_REPERTOIRE && courant->repertoryBloc->mesInodes[i].name[0] !='.')
        	       		printf ("\033[34;01m%s\033[00m  \n",courant->repertoryBloc->mesInodes[i].name);
            		else if (courant->repertoryBloc->mesInodes[i].name[0] !='.')
                		printf("%s  \n",courant->repertoryBloc->mesInodes[i].name);
        	}
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
		//DataBloc* dataBloc = malloc(sizeof(DataBloc));
		//inode.dataBloc = dataBloc; 
		inode.previousInode = inodeParent;
<<<<<<< HEAD
		//printf("le nom de mon pére est33 : %s \n",inodeParent->name);
		//printf("j'ia enregistre: %s \n",inode.previousInode->name);
=======
		printf("le nom de mon pére est33 : %s \n",inodeParent->name);
		printf("j'ia enregistre: %s \n",inode.previousInode->name);
>>>>>>> 27820cf102f9f9e4fc50be525b61b506916a8271
		inode.repertoryBloc= malloc(sizeof(RepertoryBloc));
  		inode.repertoryBloc->nbDeMesInode=0;

	}
<<<<<<< HEAD
	//printf("le nom de mon pére est33 : %s \n",inodeParent->name);
		//printf("j'ia enregistre: %s \n",inode.previousInode->name);
=======
	printf("le nom de mon pére est33 : %s \n",inodeParent->name);
		printf("j'ia enregistre: %s \n",inode.previousInode->name);
>>>>>>> 27820cf102f9f9e4fc50be525b61b506916a8271
	ajoutInodeDisk(inode,disk);
	ajoutInode(inode,inodeParent);
}
void copyFile(Inode fichier,char* dest,Disk* disk)
{
	Inode inode,inodeParent;
	inode=fichier;
	inodeParent=decoupeCibleChemin(dest,disk);
	
	if(inodeParent.type==TYPE_REPERTOIRE)
	{
		inode.previousInode=&inodeParent;
		ajoutInodeDisk(inode,disk);
		ajoutInode(inode,&inodeParent);
	}
	else
	{
		inode.previousInode=inodeParent.previousInode;
		supprimeFichier(inodeParent.previousInode,inodeParent.name,disk);
		ajoutInodeDisk(inode,disk);
		ajoutInode(inode,inode.previousInode);
	}
}

void deplacerFile(Inode inodeFichier,char* dest,Disk* disk)
{
	copyFile(inodeFichier,dest,disk);
	supprimeFichier(inodeFichier.previousInode,inodeFichier.name,disk);
}
