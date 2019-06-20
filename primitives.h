#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdio.h>
#include "structure.h"

void creerFichier(Inode* inodeParent, Disque* disque, char* nom);

//void afficherRepertoire(BlocRepertoire* repertory);

void ecrireDansFichier(char* nomDufichier, char* aEcrire, Disque* disque);

void afficherDataFichier(Inode* courant, char* nomDufichier, Disque* disque);

Inode* getInodeParNom(char* nomInode, Disque* disque);

void afficherRepertoire(char* arg1, Inode* courant, Disque* disque);

void creerRepertoire(Inode* inodeParent, Disque* disque, char* nom);

void changerRepertoire(char* arg1, Inode* courant, Inode* pere);

void donnerRepertoireCourant(Inode courant);

void supprimerFichier(Inode* courant, char* arg1, Disque* disque);

void supprimerFichier2(Inode* courant, char* arg1, Disque* disque);

void supprimerRepertoire(Inode* courant, char* arg1, Disque* disque);

void supprimerFichierDisque(char* arg1, Disque* disque, int typeAEffacer);

void afficherInodes(Disque* disque);

Inode decouperCibleChemin(char* arg, Disque* disque);

Inode chercherCibleChemin(char* nom, char * nomParent, Disque* disque);

void copierFichier(Inode fichier,char* dest, Disque* disque);

void deplacerFichier(Inode inodeFichier, char* dest, Disque* disque);

void afficherArg(char* arg1, char* arg2);

void compterMots(Inode* courant, char* arg1);

#endif // PRIMITIVES_H
