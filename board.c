//To do:
//Rook movement --> Movement obstruction check
//Bishop movement
//Queen movement
//King movement
//Pawn movement
//Pawn to Queen conversion
//Ally-Foe Recognition when collision occurs
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




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int rook_lane_check(char board[8][8][4], int A, int Ax, int Ay);
void next_move(char board[8][8][4], char* move, size_t buff_size);
void current_board(char board[8][8][4], const char* next_move);
int check_move(char board[8][8][4], char* curr_place, char* move);
int main(int argc, char* argv[argc+1]) {

//4 bytes to include both the unicode character (3bytes) and the null pointer (1byte), otherwise it will keep on printing characters from the rest of the adjacent strings
	char board[8][8][4]={
			{"\u265c","\u265e","\u265d","\u265b","\u265a","\u265d","\u265e","\u265c"}
			,{"\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f"}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{"\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659"}
			,{"\u2656","\u2658","\u2657","\u2655","\u2654","\u2658","\u2657","\u2656"}
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

	if(!check_move(board, move_1, move_2)){
		printf("Valid move !\n");
	}
}

int check_move(char board[8][8][4], char* curr_place, char* move){
	int cpx=curr_place[2]-'1';
	int cpy=curr_place[1]-'a';
	int mx=move[2]-'1';
	int my=move[1]-'a';

	int a=my-cpy;
	int b=mx-cpx;
	int rc;
	regex_t regex;

	rc=regcomp(&regex, "[RNBKQP][a-h][1-8]",0);

// !!!!!!!!!!!!!!! MUST CHECK WHY REGEX DOESN'T ACCEPT "?"
//	rc=regcomp(&regex, "[RNBKQ]?[a-h][1-8]",0);
	rc=regexec(&regex,move,0,NULL,0);

	switch (move[0]){
		case 'N':
			if(!strcmp(board[cpx][cpy],"\u265e") && !(((my)>>3)&&((mx)>>3)) && (((b&2)&&(a&1))^((b&1)&&(a&2)))){
//				printf("mx=%d my=%d cpx=%d cpy%d",mx,my,cpx,cpy);
				strcpy(board[mx][my],board[cpx][cpy]);
				strcpy(board[cpx][cpy]," ");
				return 0;
			};
		case 'R':
			if(!strcmp(board[cpx][cpy],"\u265c") && !(((my)>>3)&&((mx)>>3)) && (!b && rook_lane_check(board,a,cpy,my))^(!a && rook_lane_check(board,b,cpx,mx))){
//				printf("mx=%d my=%d cpx=%d cpy%d",mx,my,cpx,cpy);
				strcpy(board[mx][my],board[cpx][cpy]);
				strcpy(board[cpx][cpy]," ");
				return 0;
			};
		default:
			printf("Invalid move !\n");
			return rc;
	}
}

int rook_lane_check(char board[8][8][4], int A, int Ax, int Ay){

	if(A&0x0001)
		return 1;
//	if(A&0x8000000){
//		A=-(A+1);
//		while(!(A-1)){
//			Ay+A
//		}
//	}

	return 1;

}
