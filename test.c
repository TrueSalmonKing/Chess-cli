#include <stdio.h>

void binary_print(int a);
int check_Knight_Move();

int main(int argc, char* argv[argc+1]) {

}

int check_Knight_Move(){

	char test[3] = "Nh8";
	char test2[3] = "Na7";
	int a = test[1]-test2[1];
	int b = test[2]-test2[2];

	printf("b = %d\n",b);
	binary_print(b);
	printf("\na = %d\n",a);
	binary_print(a);

//boundary check with !(((test2[1]-'a')>>3)&&((test2[2]-'1')>>3)) where the value is shifted by 3 bits after substracting one to ensure that it is between 1 (0b0001) and 8 (0b0100) (bit shift works conveniently since we have an upper bound power of 2)
//check possible knight move with one move on one axis opposed to 2 moves on the other axis with( ((b&2)&&(a&1))^((b&1)&&(a&2)) ) 

	if( !(((test2[1]-'a')>>3)&&((test2[2]-'1')>>3)) && (((b&2)&&(a&1))^((b&1)&&(a&2))) ) {	
//	if(test2[1]>= 'a' && test2[1]<='h' && test2[2]>='1' && test2[2]<='8' && ( ((b&2)&&(a&1)) || ((b&1)&&(a&2)) )) {
		printf("\nValid move ! \n");
	}

	printf("\nb = %d\n",b);
	binary_print(b);

	return 0;
}

void binary_print(int a) {

        int i = 0;
        for (i=0; i<32; i++)
                printf("%d", !!((a<<i)&0x80000000));
        printf("\n");
        return;
 
}
