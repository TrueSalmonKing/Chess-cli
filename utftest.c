#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[argc+1]){

	char *a = malloc(sizeof *a * 4);
	*a = 0xE2;
	*(a+1) = 0x99;
	*(a+2) = 0x9F;
	printf("%s", a);
	return 0;

}

