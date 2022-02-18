//To do:
//Queen movement
//King movement
//Pawn movement
//Pawn to Queen conversion
//Co-op playstyle implementation
//Timer + Turns
//AI Implementation
//Handle Exceptions --> INVALID MOVE + TIMER RAN OUT + REGEX ERRORS
//
//
//Completed:
//Movement parsing
//Knight movement
//Movement parsing exception handling --> NO SPACE BETWEEN CHARACTERS
//Ally-Foe Recognition when collision occurs
//Rook movement --> Movement obstruction check
//Rook movement --> must return Invalid movement without any collision check in the case where collision occurs before the while loop in the rook movement reachs the desired board piece to move to
//Bishop movement
//Rook movement logic needs to be updated in lane_check (Utilize similar logic to Bishop movement)




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int lane_check(char board[8][8][4], int cpx, int cpy, int mX, int mY);
void next_move(char board[8][8][4], char* move, size_t buff_size);
void current_board(char board[8][8][4], const char* next_move);
int check_move(char board[8][8][4], char* curr_place, char* move);
int colli_handl(char p1[4], char p2[4]);

int main(int argc, char* argv[argc+1]){

//4 bytes to include both the unicode character (3bytes) and the null pointer (1byte), otherwise it will keep on printing characters from the rest of the adjacent strings
	char board[8][8][4]={
			{"\u265c","\u265e","\u265d","\u265b","\u265a","\u265d","\u265e","\u265c"}
			,{"\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f"}
			,{" "," "," "," "," "," "," "," "}
			,{" ","\u265d"," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{"\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659"}
			,{"\u2656","\u2658","\u2657","\u2655","\u2654","\u2657","\u2658","\u2656"}
			};

	size_t buff_size=7;
	char * current_move=(char *)malloc(sizeof(char)*buff_size);

	while(1){
		current_board(board, current_move);
		printf("\nprevious move: %c%c%c %c %c%c%c \nnext move: ",*current_move,*(current_move+1),*(current_move+2),*(current_move+3),*(current_move+4),*(current_move+5),*(current_move+6));
		next_move(board,current_move, buff_size);
	}
	return 0;

}

void current_board(char board[8][8][4], const char* next_move){
	printf(" _a_b_c_d_e_f_g_h\n");
	for(size_t i=0;i<8;i++){
		printf("%lu|",i+1);
		for(size_t j=0;j<8;j++){
			printf("%s|",board[i][j]);
		}
		printf("%lu\n",i+1);
	}
	printf(" _a_b_c_d_e_f_g_h\n");
			


}

void next_move(char board[8][8][4], char* move, size_t buff_size){

	char * move_1 = malloc(sizeof *move_1 * 3);
	char * move_2 = malloc(sizeof *move_2 * 3);
	char delim[]=" ";

	getline(&move,&buff_size,stdin);
	
	move_1=strtok(move,delim);
	move_2=strtok(NULL,delim);

	if(move_2 == NULL){
		printf("Invalid move !\n");
		return;
	}

	if(check_move(board, move_1, move_2))
		printf("Valid move !\n");
}

int check_move(char board[8][8][4], char* curr_place, char* move){
	int cpx=curr_place[1]-'a';
	int cpy=curr_place[2]-'1';
	int mx=move[1]-'a';
	int my=move[2]-'1';

	int a=mx-cpx;
	int b=my-cpy;
	int rc;
	regex_t regex;

	rc=regcomp(&regex, "[RNBKQP][a-h][1-8]",0);

// !!!!!!!!!!!!!!! MUST CHECK WHY REGEX DOESN'T ACCEPT "?"
//	rc=regcomp(&regex, "[RNBKQ]?[a-h][1-8]",0);
	rc=regexec(&regex,move,0,NULL,0);

	switch (move[0]){
		case 'N':
			if((!strcmp(board[cpy][cpx],"\u265e") || !strcmp(board[cpy][cpx],"\u2658")) && (!((mx)>>3)&&!((my)>>3)) && (((a&2)&&(b&1))^((a&1)&&(b&2)))){
				strcpy(board[my][mx],board[cpy][cpx]);
				strcpy(board[cpy][cpx]," ");
				return 1;
			};
			return 0;
		case 'R':
			if((!strcmp(board[cpy][cpx],"\u265c") || !strcmp(board[cpy][cpx],"\u2656")) && (!((mx)>>3)&&!((my)>>3)) && (!a && lane_check(board,cpx,cpy,a,b))^(!b && lane_check(board,cpx,cpy,a,b))){
				strcpy(board[my][mx],board[cpy][cpx]);
				strcpy(board[cpy][cpx]," ");
				return 1;
			};
			return 0;
		case 'B':
			if((!strcmp(board[cpy][cpx],"\u265d") || !strcmp(board[cpy][cpx],"\u2657")) && (!((mx)>>3)&&!((my)>>3)) && a<<29&b<<29 && lane_check(board,cpx,cpy,a,b)){
				strcpy(board[my][mx],board[cpy][cpx]);
				strcpy(board[cpy][cpx]," ");
				return 1;
			}
			return 0;
		default:
			printf("Invalid !\n");
			return rc;
	}
}

int lane_check(char board[8][8][4], int cpx, int cpy, int mX, int mY){

	int iter = ((!!mX) | (mX >> 31)) ? 1 : -1;
	int i=0, j=0, si=0, sj=0;
	printf("mX= %d, iter= %d, X=%d\n", mX, iter, X);
	printf("CASE 2\n\n\n");
	si = !mX ? 0 : (mX>>31) ? -1 : 1;
	sj = !mY ? 0 : (mY>>31) ? -1 : 1;
	i = 0;
	j = 0;

	do{
		i+=si;
		j+=sj;
		printf("mX=%d, mY=%d\n", mX, mY);
		printf("cpy=%d, cpx=%d, %s\n", cpy+j, cpx+i, board[cpy+j][cpx+i]);
		if(!strcmp(board[cpy+j][cpx+i]," "))
			printf("empty");
		else {
			printf("Collision !\n");
			return mX-i ? 0 : colli_handl(board[cpy][cpx], board[cpy+j][cpx+i]);
		}
	} while(mX-i);

	return 1;
}

int colli_handl(char p1[4], char p2[4]){

//colli_handl only gets called if the board piece ISN'T a space
//first we compare if its third hex value is larger than 0x93 (smallest chess piece is E2 99 94) and we divide by 6, as the smallest black chess piece has value E2 99 9A (9A - 94 = 6), to check whether it is a black of white piece, we proceed to get the bit value of its range (0 if white, 1 if black) and we XNOR it to the value get from the same operation done on the second piece
//if differing pieces' collision occurs --> 1 is returned
	return ((p1[2]-0x94)&0xFF)/6 == !(((p2[2]-0x94)&0xFF)/6);

}
