
#include  <stdlib.h>
#include <stdio.h>
#include <string.h>


void myputchar(char* c){

	write(1,c,1);

}


int main (){
	printf("hello world\n");

	char* s;
	s = malloc(sizeof(s)*(255 +1));

	while(1){

		printf("user@user ");
		scanf(" %s",s);

		
		
		int i = 0; 
		/*
		for(i=0;i < strlen(s);i++){
			myputchar(s+i);
		}*/
		printf("%s",s);
		printf("\n");
	}
	free(s);
	return 0; 
}