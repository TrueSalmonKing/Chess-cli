#include <stdio.h>

void binary_print(int a);
int main(int argc, char* argv[argc+1]) {

	char test[3] = "Nf6";
	char test2[3] = "Ng5";
	int a = test[1]-test2[1];
	int b = test[2]-test2[2];

	printf("b = %d\n",b);
	binary_print(b);
	printf("\na = %d\n",a);
	binary_print(a);

//boundary check + check if every move either moves once on the x axis and twice on the y axis or the opposite using ( ((b&2)&&(a&1)) || ((b&1)&&(a&2)) )

	if(test2[1]>= 'a' && test2[1]<='h' && test2[2]>='1' && test2[2]<='8' && ( ((b&2)&&(a&1)) || ((b&1)&&(a&2)) )) {
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
