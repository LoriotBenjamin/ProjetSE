#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

// touch
void creerFichier(Inode* inodeParent, Disque* disque, char* nom) {
	Inode inode;
	int i;

	for(i=0; i<inodeParent->blocRepertoire->nbInodes; i++) {

	}
	
	strcpy(inode.nom, nom);
	
	inode.type = TYPE_FICHIER;
	inode.test = 12;

	//init_permissions(&inode);
	
	if(inodeParent->type == TYPE_REPERTOIRE) {
		BlocDonnees* blocDonnees = malloc(NB_BLOCS_UTILISES * sizeof(BlocDonnees));
		inode.blocDonnees = blocDonnees; 
		inode.inodePre = inodeParent;
	}

	ajoutInodeDisque(inode, disque);
	ajoutInode(inode, inodeParent);
}

// pour le débug 
void afficherInodes(Disque* disque) {	
	printf(" liste des inodes: ");
	for(int i=0; i<(disque->nbInodes); i++) { 
		printf(" %s  ", disque->listeInodes[i].nom);
	}	
	printf("\n");
}

// cat 
void afficherDataFichier(Inode* courant, char* nomDufichier, Disque* disque) { 
	int i, j;

	if(getInodeParNom(nomDufichier, disque)!= NULL) {
		Inode* inodeAEcrire = getInodeParNom(nomDufichier, disque);

		for(j=0; j<NB_BLOCS_UTILISES; j++){
			for(i=0; i< sizeof(inodeAEcrire->blocDonnees[j].donnees); i++) {
				printf("%c", inodeAEcrire->blocDonnees[j].donnees[i]);
			}
			printf("bloc %d \n", j);
		}

		printf("valeur de j à la fin de la boucle: %d", j);
		printf("\n");
	}
	else{
		printf("le fichier n'existe pas dans ce repertoire \n");
	}
}

// pour débug
void ecrireDansFichier(char* nomDufichier, char* aEcrire, Disque* disque) {
	int i;

	printf("inode mal recupere: \n");
	Inode* inodeAEcrire = getInodeParNom(nomDufichier, disque);
	printf("inode bien recupere: %s \n", inodeAEcrire->nom);

	if(strlen(aEcrire) < BLOC_DONNEES_TAILLE){ 
		strcpy(inodeAEcrire->blocDonnees[0].donnees, aEcrire);
	}	

	for(i=0; i< sizeof(inodeAEcrire->blocDonnees[1].donnees); i++) {
		printf(" %c", inodeAEcrire->blocDonnees[1].donnees[i]);
	}
	printf("valeur de i à la fin de la boucle: %d", i);
	printf("\n");
}

void compterMots(Inode* courant, char* arg1) {
	int i, j, k, compteur = 0;

	for(i=0; i<(courant->blocRepertoire->nbInodes); i++) {
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_FICHIER && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0) {
			printf("ça bug ici? %d \n", i);
			for(j=0; j<NB_BLOCS_UTILISES; j++){
				//printf("ou  ici? %d \n", i);
				//printf("ou  la? %d \n", i);
				for(k=0; k<BLOC_DONNEES_TAILLE; k++) {
					if(courant->blocRepertoire->listeInodes[i].blocDonnees[j].donnees[k] != 0) {
						compteur++;
						printf(" %c  ", courant->blocRepertoire->listeInodes[i].blocDonnees[j].donnees[k]);
					}
				}
				printf("bloc %d \n", j);
			}
		}
	}
	printf("il y a : %d caracteres", compteur);
}

Inode* getInodeParNom(char* nomInode, Disque* disque){
	printf("je veu l'inode du nom de : %s \n", nomInode);
	for(int i=0; i<(disque->nbInodes); i++) {
		if(strcmp(nomInode, disque->listeInodes[i].nom) == 0 ){
			printf("inode trouve son nom est : %s \n", disque->listeInodes[i].nom);
			return &(disque->listeInodes[i]);
		}
	}
	return NULL;	
}

// echo
void afficherArg(char* arg1, char* arg2) {	
	if(strcmp(arg1,"\0") && strcmp(arg2,"\0")) { 
		printf("%s %s \n",arg1,arg2);
	} else {  
		printf("%s \n",arg1);
	}	
}

// rmdir
void supprimerRepertoire(Inode* courant, char* arg1, Disque* disque){	
	printf("nom de tout mes inodes \n");
	for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
		printf("%s ", courant->blocRepertoire->listeInodes[i].nom);
	}
	printf("\n");
	int tamp = 0;

	printf(" je suis lancé et le courant est : %s \n", courant->nom);
	printf("je demande de supprimer: %s \n", arg1);

	for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0) {
			tamp = i;

			if(courant->blocRepertoire->listeInodes[i].blocRepertoire->nbInodes == 0) {// pas de fils
				printf("je passe la \n");
				supprimerFichierDisque(arg1, disque,courant->blocRepertoire->listeInodes[i].type);
				courant->blocRepertoire->nbInodes = courant->blocRepertoire->nbInodes-1;
			} else {	// le repertoir a des fils 
				//supprimerFichierDisque(arg1, disque,courant->blocRepertoire->listeInodes[i].type); à voir 
				for(int j=0; j<(courant->blocRepertoire->listeInodes[i].blocRepertoire->nbInodes); j++) { // suppression des fils
					printf(" nb inodes: %d\n", courant->blocRepertoire->listeInodes[i].blocRepertoire->nbInodes);
					printf("j=%d \n", j);
					printf("i=%d \n", i);

					if(courant->blocRepertoire->listeInodes[i].blocRepertoire->listeInodes[j].type == TYPE_REPERTOIRE) {
						printf("je lance moi meme\n");
						supprimerRepertoire(&(courant->blocRepertoire->listeInodes[i]), courant->blocRepertoire->listeInodes[i].blocRepertoire->listeInodes[j].nom, disque);	// TODO PARTIE RECURSIF A TESTER!!
					} else {
						supprimerFichier2(&(courant->blocRepertoire->listeInodes[i]), courant->blocRepertoire->listeInodes[i].blocRepertoire->listeInodes[j].nom, disque);
					}
				} // fin suppression des fils 
				supprimerFichierDisque(arg1,disque,courant->blocRepertoire->listeInodes[i].type);
			}	
		} // apres la suppresion demande	
	}

	courant->blocRepertoire->nbInodes = courant->blocRepertoire->nbInodes-1;
	for(int i=tamp; i<(courant->blocRepertoire->nbInodes); i++) { // faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
	 	// si on arrive au bout du tableau
		if(courant->blocRepertoire->listeInodes[i+1].type == TYPE_FICHIER || courant->blocRepertoire->listeInodes[i+1].type == TYPE_REPERTOIRE) {
			courant->blocRepertoire->listeInodes[i] = courant->blocRepertoire->listeInodes[i+1];
		}	
	}
}

// rmdir
void supprimerFichierDisque(char* arg1, Disque* disque, int typeAEffacer) {	
	for(int i=0; i<(disque->nbInodes); i++) {
		if(strcmp(arg1, disque->listeInodes[i].nom) == 0 && typeAEffacer == disque->listeInodes[i].type ) {	
			disque->nbInodes = disque->nbInodes - 1;
			for(i; i<(disque->nbInodes); i++) {// faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
				 // si on arrive au bout du tableau
				if(disque->listeInodes[i+1].type == TYPE_FICHIER || disque->listeInodes[i+1].type == TYPE_REPERTOIRE) { 
					disque->listeInodes[i]= disque->listeInodes[i+1];
				}	
			}
		}
	}
}

// rm
void supprimerFichier(Inode* courant,char* arg1,Disque* disque) {	
	for(int i=0; i<(courant->blocRepertoire->nbInodes); i++){
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_FICHIER && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0) {
			supprimerFichierDisque(arg1, disque, courant->blocRepertoire->listeInodes[i].type);
			
			courant->blocRepertoire->nbInodes = courant->blocRepertoire->nbInodes - 1;
			for(i; i<(courant->blocRepertoire->nbInodes); i++) {// faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
				 // si on arrive au bout du tableau
				if(courant->blocRepertoire->listeInodes[i+1].type == TYPE_FICHIER || courant->blocRepertoire->listeInodes[i+1].type == TYPE_REPERTOIRE ) { 
					courant->blocRepertoire->listeInodes[i] = courant->blocRepertoire->listeInodes[i+1];
				}	
			}
		}
	}
}

void supprimerFichier2(Inode* courant, char* arg1, Disque* disque) {	// besoin pour la récursivité
	for(int i=0; i<(courant->blocRepertoire->nbInodes); i++){
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_FICHIER && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0){
			supprimerFichierDisque(arg1,disque,courant->blocRepertoire->listeInodes[i].type);
		}
	}
}

Inode decouperCibleChemin (char* arg, Disque* disque) {  
	char* tab[MAX_INODES_DISQUE];
	char* cs = NULL;
	int i = 0;
	int nombreDeSeparateur = 0;

	for(int i=0; i<strlen(arg); i++){
		if(arg[i] == 47) { //  code ASCII du /
			nombreDeSeparateur++;
		}	
	}	

	char string[500]; // commande de 500 caracteres max
	strcpy(string, arg);
  	char *p;
 	printf("String  \"%s\" is split into tokens:\n", string);
 	p = strtok(string, "/");
	while (p != NULL) {
		tab[i] = p;
		i++;
		printf("%s\n",p);
		p = strtok(NULL, "/");
	}
	return chercherCibleChemin(tab[nombreDeSeparateur-1], tab[nombreDeSeparateur-2], disque);
}

Inode chercherCibleChemin(char* nom, char * nomParent, Disque* disque) {	// Pour les futurs chemins 
	printf("je cherche un inode du nom de : %s \n", nom);
	printf("avec comme pere : %s \n", nomParent);
	for(int i=0; i<(disque->nbInodes); i++) {
		printf(" 1 : %s  2: %s 3: %s 4:%s", nom, disque->listeInodes[i].nom, nomParent, disque->listeInodes[i].inodePre->nom); // le "disque->listeInodes[i].inodePre->nom" ( 4: ...) renvoie le mauvais nom 
		if(strcmp(nom,disque->listeInodes[i].nom) == 0 && strcmp(nomParent,disque->listeInodes[i].inodePre->nom) == 0) {
			printf(" loltes1 : %s", disque->listeInodes[i].nom);
			return disque->listeInodes[i];
		}
	}
}

//  cd 
void changerRepertoire(char* arg1, Inode* courant, Inode * pere) {
	if(strcmp(arg1, "..") == 0) {
		if(strcmp(arg1, "..") == 0){
			if(courant->inodePre != NULL) {
				printf("mon papoulle est : %s \n", pere->nom);
				printf("je suis  : %s \n", courant->nom);
				if(strcmp(courant->nom,"/") != 0) {
					*courant = *pere ;
					courant->inodePre = pere;
				
					if(strcmp(courant->nom, "/") != 0) {
						printf("le pére du courant qu'on vient de changer est %s  \n", courant->inodePre->nom);
						printf("nom du courant aprés assignation du pere %s \n", courant->nom);
						pere = courant->inodePre;
					}
				}
			} else { 
				printf("vous êtes a la racine \n");
			}	
		}
	} else {
		for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
			if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0) {
				if(strcmp(courant->nom,"/") != 0) {
					//*pere = *courant;
					//printf(" nom du courant juste apres son assgination %s ",courant->nom);
				}
				*courant = courant->blocRepertoire->listeInodes[i];
				//courant->inodePre= pere ;
				//printf("parent aprés assignation %s \n", courant->inodePre->nom);
				printf("le grand pere de courant est par le courant  :%s", courant->inodePre->inodePre->nom);
				printf("le grand pere de courant est par le pere  :%s", pere->inodePre->nom);
				break;
			}
			//printf("DEBUG : mon papa nom : %s\n",courant->inodePre->nom);
		}	
	}		
}

// pwd
void donnerRepertoireCourant(Inode courant) {	
	printf("%s \n", courant.nom);
}

// ls
void afficherRepertoire(char* arg1, Inode* courant, Disque* disque) {	
	printf(" je suis : %s \n", courant->nom);
	printf(" j'ai  : %d inodes \n", courant->blocRepertoire->nbInodes);
	if(strcmp(arg1,"-C") == 0) {
		for(int i; i<(courant->blocRepertoire->nbInodes); i++) {
			if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
				printf("\033[34;01m%s\033[00m  ", courant->blocRepertoire->listeInodes[i].nom);
			} else if(courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
				printf("%s  ", courant->blocRepertoire->listeInodes[i].nom);
			}	
		}
	} else if (strcmp(arg1, "-F") == 0) {
		for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
			if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
				printf("\033[34;01m%s\033[00m/  ",courant->blocRepertoire->listeInodes[i].nom);
			} /*else if(courant->blocRepertoire->listeInodes[i].type == TYPE_EXECUTABLE) { 
				printf("%s*  ", courant->blocRepertoire->listeInodes[i].nom);
			}*/ else if(courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
				printf("%s  ", courant->blocRepertoire->listeInodes[i].nom);
			}
		}	
	} else if (strcmp(arg1, "-R") == 0) {
		for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
			if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && courant->blocRepertoire->listeInodes[i].nom[0] !=  '.') {
				printf("\033[34;01m%s\033[00m  ", courant->blocRepertoire->listeInodes[i].nom);
				for(int j=0; j<(courant->blocRepertoire->nbInodes); j++) {
					if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
						printf("\033[34;01m%s\033[00m  ", courant->blocRepertoire->listeInodes[i].nom);
					} else if(courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
						printf("%s  ", courant->blocRepertoire->listeInodes[i].nom);
					}	
				}
			} else { 
				printf("%s  ", courant->blocRepertoire->listeInodes[i].nom);
			}	
		}
	} else if(strcmp(arg1, "-d") == 0) {
		for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
				printf("%s  ", courant->blocRepertoire->listeInodes[i].nom);
		}
	} else if(strcmp(arg1, "-i") == 0) {
		for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
			if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && courant->blocRepertoire->listeInodes[i].nom[0] != '.') {
				printf("%d ", i);
				printf("%d\033[34;01m%s\033[00m  ", i, courant->blocRepertoire->listeInodes[i].nom);
			}
			else if(courant->blocRepertoire->listeInodes[i].nom[0] != '.') {
				printf("%d ", i);
				printf("%d%s  ", i, courant->blocRepertoire->listeInodes[i].nom);
			}
		}
	} else if(strcmp(arg1,"-t") == 0) {
        	for(int i=(courant->blocRepertoire->nbInodes)-1; i>0; i--) {
				if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
					printf ("\033[34;01m%s\033[00m",courant->blocRepertoire->listeInodes[i].nom);
				} else if(courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
					printf ("%d",i);
					printf("%s",courant->blocRepertoire->listeInodes[i].nom);
			}	
        }
    } /*else if(strcmp(arg1,"-a") == 0) {
        for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
        	if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE) {  
              	printf ("\033[34;01m%s\033[00m  \n", i, courant->blocRepertoire->listeInodes[i].nom);
        	} else { 
         		printf("%s  \n", i, courant->blocRepertoire->listeInodes[i].nom);
			}	
        }
	}*/ else {
        for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
        	if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
        		printf ("\033[34;01m%s\033[00m  ", courant->blocRepertoire->listeInodes[i].nom);
        	} else if(courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
         		printf("%s  ", courant->blocRepertoire->listeInodes[i].nom);
			}	
        }
    }
	printf("\n");
}

// mkdir
void creerRepertoire(Inode* inodeParent, Disque* disque, char* nom) {
	Inode inode ;
	int i = 0;
	
	strcpy(inode.nom, nom);
	inode.type = TYPE_REPERTOIRE;
	//init_permissions(&inode);

	if(inodeParent->type == TYPE_REPERTOIRE) {
		//Pas trop compris la suite, j'sais pas si c'est bon :o
		//BlocDonnees* blocDonnees = malloc(sizeof(BlocDonnees));
		//inode.blocDonnees = blocDonnees; 
		inode.inodePre = inodeParent;

		//printf("le nom de mon pére est33 : %s \n",inodeParent->nom);
		//printf("j'ia enregistre: %s \n",inode.inodePre->nom);

		inode.blocRepertoire = malloc(sizeof(BlocRepertoire));
  		inode.blocRepertoire->nbInodes = 0;
	}

	//printf("le nom de mon pére est33 : %s \n",inodeParent->nom);
	//printf("j'ia enregistre: %s \n",inode.inodePre->nom);

	ajoutInodeDisque(inode, disque);
	ajoutInode(inode, inodeParent);
}

void copierFichier(Inode fichier, char* dest, Disque* disque) {
	Inode inode, inodeParent;

	inode = fichier;
	inodeParent = decouperCibleChemin(dest ,disque);
	
	if(inodeParent.type == TYPE_REPERTOIRE) {
		inode.inodePre = &inodeParent;
		ajoutInodeDisque(inode, disque);
		ajoutInode(inode, &inodeParent);
	} else {
		inode.inodePre = inodeParent.inodePre;
		supprimerFichier(inodeParent.inodePre, inodeParent.nom, disque);
		ajoutInodeDisque(inode, disque);
		ajoutInode(inode, inode.inodePre);
	}
}

void deplacerFichier(Inode inodeFichier, char* dest, Disque* disque) {
	copierFichier(inodeFichier, dest, disque);
	supprimerFichier(inodeFichier.inodePre, inodeFichier.nom, disque);
}
