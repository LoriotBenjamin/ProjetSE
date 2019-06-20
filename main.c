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

	// boucle tant qu'on ne saisi pas "exit"	
	while(1) {
		char nomCommande[40] = "\0";
		char arg1[40] = "\0";
		char arg2[40] = "\0";		
		char buffer[100];
		char separateur;

		printf("user@%s ", courant.nom);
		fgets(buffer, 100, stdin);
		sscanf(buffer, "%s%c%s%c%s", nomCommande, &separateur, arg1, &separateur, arg2);
	
		//Inode test = decouperCibleChemin (arg1,&disque);
		//printf("nom du fichier cible: %s \n",test.nom);

		if(strcmp(nomCommande, "touch") == 0) {
			if(strcmp(arg1, "\0")) {
				creerFichier(&courant, &disque, arg1);
				printf("DEBUG : Nombre d'inodes : %d\n", disque.nbInodes);
			}
		} else if(strcmp(nomCommande, "cd") == 0) {
			if(strcmp(arg1, "\0")) {
					printf("pére avant sortie de la fonction %s \n", pere.nom);
					printf("parent avant entrée de la fonction %s \n", courant.inodePre->nom);
				
					changerRepertoire(arg1, &courant, &pere);
					printf("parent de courant aprés sortie de la fonction %s \n", courant.inodePre->nom);
					printf("pére aprés sortie de la fonction %s \n", pere.nom);

					//printf("DEBUG : mon papa nom : %s\n",courant.inodePre->nom);
					//printf("DEBUG : mon premier frere de mes freres : %s\n",courant.inodePre->blocRepertoire->listeInodes[0].nom);
					//printf("DEBUG : je suis : %s\n",courant.nom);
					//printf("DEBUG : mon papa nom : %s\n",courant.inodePre->nom);	
			}
		} else if(strcmp(nomCommande, "rm") == 0) {
			if(strcmp(arg1, "\0")){
				supprimerFichier(&courant, arg1, &disque);
			}
			
		} else if(strcmp(nomCommande, "rmdir") == 0) {
			if(strcmp(arg1, "\0")) {
				supprimerRepertoire(&courant, arg1, &disque);
			}
			
		} else if(strcmp(nomCommande, "ecrit") == 0) {
			ecrireDansFichier(arg1, arg2, &disque);
			
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
			donnerRepertoireCourant(courant);
			
		} else if(strcmp(nomCommande, "wc") == 0) {
			if(strcmp(arg1, "\0")) {
				compterMots(&courant, arg1);
			}
			
		} else if(strcmp(nomCommande, "mkdir") == 0) {
			if(strcmp(arg1, "\0")) {
				creerRepertoire(&courant, &disque, arg1);
				printf("DEBUG : Nombre d'inodes : %d\n", disque.nbInodes);
			}
			
		} else if(strcmp(nomCommande, "exit") == 0) {
            //sauver_disque(&disque);  // ne fonctionne pas
            return 0;
            
		} else if(strcmp(nomCommande, "cp") == 0) {
			copierFichier(chercherCibleChemin(arg1, courant.nom, &disque), arg2, &disque);	

		} else if(strcmp(nomCommande, "mv") == 0) {
			deplacerFichier(chercherCibleChemin(arg1, courant.nom, &disque), arg2, &disque);
			
		} else {
			printf("%s : command not found\n", nomCommande);
		}

		afficherInodes(&disque);

	} // fin du shell

	free(courant.blocRepertoire);
	free(pere.blocRepertoire);

	return 0; 
}
