#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "SGF.h"
#include "primitives.h"

int main() {
	Disque disque;
	Inode courant;
	Inode pere; 
	
	initialise_disque(&disque);
	recuperer_disque(&disque);
	
	courant = disque.listeInodes[0];
	pere = courant; 

	printf("\n");

	// boucle tant qu'on ne saisi pas "exit"	
	while(1) {
		char nomCommande[TAILLE_SAISIE] = "\0";
		char arg1[TAILLE_SAISIE] = "\0";
		char arg2[TAILLE_SAISIE] = "\0";		
		char buffer[100];
		char separateur;

		printf("\033[32;01muser@monShell\033[00m:\033[34;01m%s\033[00m ", courant.nom);
		fgets(buffer, 100, stdin);
		sscanf(buffer, "%s%c%s%c%s", nomCommande, &separateur, arg1, &separateur, arg2);

		if(strcmp(nomCommande, "touch") == 0) {
			if(strcmp(arg1, "\0")) {
				creerFichier(&courant, &disque, arg1);
			}
		} else if(strcmp(nomCommande, "mkdir") == 0) {
			if(strcmp(arg1, "\0")) {
				creerRepertoire(&courant, &disque, arg1);
			}
			
		} else if(strcmp(nomCommande, "rm") == 0) {
			if(strcmp(arg1, "\0")) {
				supprimerFichier(&courant, arg1, &disque);
			}
			
		} else if(strcmp(nomCommande, "rmdir") == 0) {
			if(strcmp(arg1, "\0")) {
				supprimerRepertoire(&courant, arg1, &disque);
			}
			
		} else if(strcmp(nomCommande, "ls") == 0) {
			afficherRepertoire(arg1, &courant, &disque);
			
		} else if(strcmp(nomCommande, "cat") == 0) {
			if(strcmp(arg1, "\0")) {
				afficherDataFichier(&courant, arg1, &disque);
			}
			
		} else if(strcmp(nomCommande, "echo") == 0) {
			if(strcmp(arg1, "\0")) {
				afficherArg(arg1, arg2);
			}
			
		} else if(strcmp(nomCommande, "pwd") == 0) {
			afficherRepertoireCourant(courant);
			
		} else if(strcmp(nomCommande, "wc") == 0) {
			if(strcmp(arg1, "\0")) {
				compterMots(&courant, arg1);
			}
			
		} else if(strcmp(nomCommande, "ecrit") == 0) {
			ecrireDansFichier(arg1, arg2, &disque);
			
		} else if(strcmp(nomCommande, "cd") == 0) {
			if(strcmp(arg1, "\0")) {
				changerRepertoire(arg1, &courant, &pere);
			}
		} else if(strcmp(nomCommande, "cp") == 0) {
			copierFichier(chercherCibleChemin(arg1, courant.nom, &disque), arg2, &disque);	

		} else if(strcmp(nomCommande, "mv") == 0) {
			deplacerFichier(chercherCibleChemin(arg1, courant.nom, &disque), arg2, &disque);
			
		} else if(strcmp(nomCommande, "exit") == 0) {
            //sauver_disque(&disque);  // ne fonctionne pas
			printf("\n");
            return 0;
            
		} else {
			printf("%s : command not found\n", nomCommande);
		}
	} // fin du shell

	free(courant.blocRepertoire);
	free(pere.blocRepertoire);

	return 0; 
}
