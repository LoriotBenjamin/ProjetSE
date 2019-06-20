 #ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdio.h>
#include "structure.h"

// touch : crée un fichier
void creerFichier(Inode* inodeParent, Disque* disque, char* nom);

// mkdir : crée un répertoire
void creerRepertoire(Inode* inodeParent, Disque* disque, char* nom);

// rm : supprime un fihcier
void supprimerFichier(Inode* courant, char* arg1, Disque* disque);

void supprimerFichier2(Inode* courant, char* arg1, Disque* disque);

void supprimerFichierDisque(char* arg1, Disque* disque, int typeAEffacer);

// rmdir : supprime un répertoire
void supprimerRepertoire(Inode* courant, char* arg1, Disque* disque);

// ls : affiche le contenu du répertoire
void afficherRepertoire(char* arg1, Inode* courant, Disque* disque);

// cat : affiche le contenu du fichier
void afficherDataFichier(Inode* courant, char* nomDufichier, Disque* disque);

// echo : affiche les arguments
void afficherArg(char* arg1, char* arg2);

// pwd : affiche le nom du répertoire courant
void afficherRepertoireCourant(Inode courant);

// wc : compte le nombre de mots contenu dans le fichier
void compterMots(Inode* courant, char* arg1);

// permet d'écrire dans un fichier
void ecrireDansFichier(char* nomDufichier, char* aEcrire, Disque* disque);

// cd : change le répertoire courant
void changerRepertoire(char* arg1, Inode* courant, Inode* pere);

// cp : copie le fichier voulu et le place à la destination souhaitée
void copierFichier(Inode fichier,char* dest, Disque* disque);

// mv : déplace un fichier
void deplacerFichier(Inode inodeFichier, char* dest, Disque* disque);

#endif // PRIMITIVES_H
