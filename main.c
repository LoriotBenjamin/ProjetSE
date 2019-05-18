
#include  <stdlib.h>
#include <stdio.h>
#include <string.h>


struct infoinode
{
	char permissions[8]; // rwxr--r--
	int typefichier; // 1 = texte, 2 = binaire , ...
	int blocutilise[30]; // quels sont les blocs utilisés (max 30 ici)
	// peut être mettre la longueur du fichier
};

struct unbloc {
	char donnees[1024]; // par exemple 1024 octets 
};
struct disk {
	struct infoinode inode[15]; // 15 inodes
	struct unbloc bloc[30]; // 30 blocs de 1024 octets 
};


int main (){


	while(1){

		printf("%d",sizeof(unbloc));

		printf("user@user ");

		char nomCommande[40]="\0";

		char seperator;

		char arg1[40]="\0";

		char arg2[40]="\0";

		char buffer[100];

		fgets(buffer, 100, stdin);

		sscanf(buffer, "%s%c%s%c%s", nomCommande,&seperator,arg1,&seperator,arg2);

		printf("nomCommande : %s\n", nomCommande);
		printf("arg1: %s\n",arg1 );
		printf("arg2: %s\n",arg2 );

		// traitement de la commande 
		



	}
	return 0; 
}