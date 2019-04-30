
#include  <stdlib.h>
#include <stdio.h>
#include <string.h>


void myputchar(char* c){

	write(1,c,1);

}


int main (){

	printf("hello world\n");

	char s[100]=" ";

	while(1){

		printf("user@user ");

		char nomCommande[40];

		char seperator;

		char arg1[40];

		char arg2[40];

		char buffer[100];

		fgets(buffer, 100, stdin);

		sscanf(buffer, "%s%c%s%c%s", nomCommande,&seperator,arg1,&seperator,arg2);

		printf("nomCommande : %s\n", nomCommande);
		printf("arg1: %s\n",arg1 );
		printf("arg2: %s\n",arg2 );



	}
	//free(s);
	return 0; 
}