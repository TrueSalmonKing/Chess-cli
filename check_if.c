#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	size_t buff_size=7;
	char * move = malloc(sizeof * move * 7);
	char * move_1 = malloc(sizeof *move_1 * 3);
	char * move_2 = malloc(sizeof *move_2 * 3);
	char delim[]=" ";

	getline(&move,&buff_size,stdin);

	move_1=strtok(move,delim);
	move_2=strtok(NULL,delim);

	if(move_1 == NULL && move_2 == NULL){
		printf("invalid move 1 !");
		return 1;
	} 	
	if(move_2 == NULL){
		printf("invalid move 2 !");
		return 1;
	} 	

	return 0;

}
