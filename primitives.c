#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

// touch : crée un fichier
void creerFichier(Inode* inodeParent, Disque* disque, char* nom) {
	Inode inode;
	int i;
	
	strcpy(inode.nom, nom);
	inode.type = TYPE_FICHIER;
	init_permissions(&inode);
	
	if(inodeParent->type == TYPE_REPERTOIRE) {
		BlocDonnees* blocDonnees = malloc(NB_BLOCS_UTILISES * sizeof(BlocDonnees));
		inode.blocDonnees = blocDonnees; 
		inode.inodePre = inodeParent;
	}

	ajoutInodeDisque(inode, disque);
	ajoutInode(inode, inodeParent);
}

// mkdir : crée un répertoire
void creerRepertoire(Inode* inodeParent, Disque* disque, char* nom) {
	Inode inode ;
	int i = 0;
	
	strcpy(inode.nom, nom);
	inode.type = TYPE_REPERTOIRE;
	init_permissions(&inode);

	if(inodeParent->type == TYPE_REPERTOIRE) {
		inode.inodePre = inodeParent;
		inode.blocRepertoire = malloc(sizeof(BlocRepertoire));
  		inode.blocRepertoire->nbInodes = 0;
	}

	ajoutInodeDisque(inode, disque);
	ajoutInode(inode, inodeParent);
}

// rm : supprime un fihcier
void supprimerFichier(Inode* courant,char* arg1,Disque* disque) {	
	for(int i=0; i<(courant->blocRepertoire->nbInodes); i++){
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_FICHIER && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0) {
			supprimerFichierDisque(arg1, disque, courant->blocRepertoire->listeInodes[i].type);
			courant->blocRepertoire->nbInodes = courant->blocRepertoire->nbInodes - 1;
			for(i; i<(courant->blocRepertoire->nbInodes); i++) { // faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
				// si on arrive au bout du tableau
				if(courant->blocRepertoire->listeInodes[i+1].type == TYPE_FICHIER || courant->blocRepertoire->listeInodes[i+1].type == TYPE_REPERTOIRE ) { 
					courant->blocRepertoire->listeInodes[i] = courant->blocRepertoire->listeInodes[i+1];
				}	
			}
		}
	}
}

void supprimerFichier2(Inode* courant, char* arg1, Disque* disque) { // besoin pour la récursivité
	for(int i=0; i<(courant->blocRepertoire->nbInodes); i++){
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_FICHIER && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0){
			supprimerFichierDisque(arg1,disque,courant->blocRepertoire->listeInodes[i].type);
		}
	}
}

void supprimerFichierDisque(char* arg1, Disque* disque, int typeAEffacer) {	
	for(int i=0; i<(disque->nbInodes); i++) {
		if(strcmp(arg1, disque->listeInodes[i].nom) == 0 && typeAEffacer == disque->listeInodes[i].type ) {	
			disque->nbInodes = disque->nbInodes - 1;
			for(i; i<(disque->nbInodes); i++) { // faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
				// si on arrive au bout du tableau
				if(disque->listeInodes[i+1].type == TYPE_FICHIER || disque->listeInodes[i+1].type == TYPE_REPERTOIRE) { 
					disque->listeInodes[i]= disque->listeInodes[i+1];
				}	
			}
		}
	}
}

// rmdir : supprime un répertoire
void supprimerRepertoire(Inode* courant, char* arg1, Disque* disque){	
	int tamp = 0, supp = 0;

	for(int i=0; i<(courant->blocRepertoire->nbInodes); i++) {
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_REPERTOIRE && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0) {
			tamp = i;

			if(courant->blocRepertoire->listeInodes[i].blocRepertoire->nbInodes == 0) { // pas de fils
				supprimerFichierDisque(arg1, disque,courant->blocRepertoire->listeInodes[i].type);
				courant->blocRepertoire->nbInodes = courant->blocRepertoire->nbInodes-1;
			} else {	// le repertoire a des fils 
				for(int j=0; j<(courant->blocRepertoire->listeInodes[i].blocRepertoire->nbInodes); j++) { // suppression des fils
					if(courant->blocRepertoire->listeInodes[i].blocRepertoire->listeInodes[j].type == TYPE_REPERTOIRE) {
						supprimerRepertoire(&(courant->blocRepertoire->listeInodes[i]), courant->blocRepertoire->listeInodes[i].blocRepertoire->listeInodes[j].nom, disque);	// TODO PARTIE RECURSIF A TESTER!!
					} else {
						supprimerFichier2(&(courant->blocRepertoire->listeInodes[i]), courant->blocRepertoire->listeInodes[i].blocRepertoire->listeInodes[j].nom, disque);
					}
				} 
				supprimerFichierDisque(arg1,disque,courant->blocRepertoire->listeInodes[i].type);
			}
			supp++;	
		}	
	}

	if(supp > 0) { 
		for(int i=tamp; i<(courant->blocRepertoire->nbInodes); i++) { // faut réorganiser le tableau on repart d'ou on etait et on prend les n+1 pour les decaler
			// si on arrive au bout du tableau
			if(courant->blocRepertoire->listeInodes[i+1].type == TYPE_FICHIER || courant->blocRepertoire->listeInodes[i+1].type == TYPE_REPERTOIRE) {
				courant->blocRepertoire->listeInodes[i] = courant->blocRepertoire->listeInodes[i+1];
			}	
		}
	}	
}

// ls : affiche le contenu du répertoire
void afficherRepertoire(char* arg1, Inode* courant, Disque* disque) {	
	if(courant->blocRepertoire->nbInodes > 0) {  
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
				} else if(courant->blocRepertoire->listeInodes[i].nom[0] != '.') { 
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
		} else {
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
}

// cat : affiche le contenu du fichier
void afficherDataFichier(Inode* courant, char* nomDufichier, Disque* disque) { 
	int i, j;

	if(getInodeParNom(nomDufichier, disque)!= NULL) {
		Inode* inodeAEcrire = getInodeParNom(nomDufichier, disque);

		if(inodeAEcrire->type == TYPE_FICHIER) { 
			for(j=0; j<NB_BLOCS_UTILISES; j++){
				for(i=0; i< sizeof(inodeAEcrire->blocDonnees[j].donnees); i++) {
					printf("%c", inodeAEcrire->blocDonnees[j].donnees[i]);
				}
				printf("bloc %d \n", j);
			}
		}	
	}
	else{
		printf("le fichier n'existe pas dans ce repertoire \n");
	}
}

// echo : affiche les arguments
void afficherArg(char* arg1, char* arg2) {	
	if(strcmp(arg1, "\0") && strcmp(arg2, "\0")) { 
		printf("%s %s \n", arg1, arg2);
	} else {  
		printf("%s \n", arg1);
	}	
}

// pwd : affiche le nom du répertoire courant
void afficherRepertoireCourant(Inode courant) {	
	printf("%s \n", courant.nom);
}

// wc : compte le nombre de mots contenu dans le fichier
void compterMots(Inode* courant, char* arg1) {
	int i, j, k, compteur = 0;

	for(i=0; i<(courant->blocRepertoire->nbInodes); i++) {
		if(courant->blocRepertoire->listeInodes[i].type == TYPE_FICHIER && strcmp(arg1, courant->blocRepertoire->listeInodes[i].nom) == 0) {
			for(j=0; j<NB_BLOCS_UTILISES; j++){
				for(k=0; k<BLOC_DONNEES_TAILLE; k++) {
					if(courant->blocRepertoire->listeInodes[i].blocDonnees[j].donnees[k] != 0) {
						compteur++;
					}
				}
			}
		}
	}
	printf("%d caracteres\n", compteur);
}

// permet d'écrire dans un fichier
void ecrireDansFichier(char* nomDufichier, char* aEcrire, Disque* disque) {
	int i;
	Inode* inodeAEcrire = getInodeParNom(nomDufichier, disque);
	
	if(inodeAEcrire->type == TYPE_FICHIER) { 
		if(strlen(aEcrire) < BLOC_DONNEES_TAILLE){ 
			strcpy(inodeAEcrire->blocDonnees[0].donnees, aEcrire);
		}	

		for(i=0; i< sizeof(inodeAEcrire->blocDonnees[1].donnees); i++) {
			printf(" %c", inodeAEcrire->blocDonnees[1].donnees[i]);
		}
		printf("\nvaleur de i à la fin de la boucle: %d\n", i);
	}	
}

// cd : change le répertoire courant
void changerRepertoire(char* arg1, Inode* courant, Inode * pere) {
	if(strcmp(arg1, "..") == 0) {
		if(strcmp(arg1, "..") == 0){
			if(courant->inodePre != NULL) {
				if(strcmp(courant->nom,"/") != 0) {
					*courant = *pere ;
					courant->inodePre = pere;
				
					if(strcmp(courant->nom, "/") != 0) {
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
				*courant = courant->blocRepertoire->listeInodes[i];
				break;
			}
		}	
	}		
}

// cp : copie le fichier voulu et le place à la destination souhaitée
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

// mv : déplace un fichier
void deplacerFichier(Inode inodeFichier, char* dest, Disque* disque) {
	copierFichier(inodeFichier, dest, disque);
	supprimerFichier(inodeFichier.inodePre, inodeFichier.nom, disque);
}
