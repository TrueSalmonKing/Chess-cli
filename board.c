#include <stdio.h>
#include <stdlib.h>

void next_move(char board[8][8][4], char* move, size_t buff_size);
void current_board(const char board[8][8][4], const char* next_move);
int main(int argc, char* argv[argc+1]) {

//4 bytes to include both the unicode character (3bytes) and the null pointer (1byte), otherwise it will keep on printing characters from the rest of the adjacent strings
	char board[8][8][4] = {
			{"\u265c","\u265e","\u265d","\u265b","\u265a","\u265d","\u265e","\u265c"}
			,{"\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f"}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{"\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659"}
			,{"\u2656","\u2658","\u2657","\u2655","\u2654","\u2658","\u2657","\u2656"}
			};


	size_t buff_size = 7;
	char * current_move = (char *)malloc(sizeof(char)*buff_size);

	while(1){
		current_board(board, current_move);
		printf("\nprevious move: %c%c%c%c%c%c%c \nnext move: ",*current_move,*(current_move+1),*(current_move+2),*(current_move+3),*(current_move+4),*(current_move+5),*(current_move+6));
		next_move(board,current_move, buff_size);
	}
	return 0;

}

void current_board(const char board[8][8][4], const char* next_move){
	printf(" _a_b_c_d_e_f_g_h\n");
	for(size_t i=0;i<8;i++){
		printf("%lu|",i+1);
		for(size_t j=0;j<8;j++){
			printf("%s|",board[i][j]);
		}
		printf("%lu\n",i+1);
	}
	printf(" _a_b_c_d_e_f_g_h\n");
			


//	printf(" _a_b_c_d_e_f_g_h\n8|\u265c|\u265e|\u265d|\u265b|\u265a|\u265d|\u265e|\u265c|8\n7|\u265f|\u265f|\u265f|\u265f|\u265f|\u265f|\u265f|\u265f|7\n6| | | | | | | | |6\n5| | | | | | | | |5\n4| | | | | | | | |4\n3| | | | | | | | |3\n2|\u2659|\u2659|\u2659|\u2659|\u2659|\u2659|\u2659|\u2659|2\n1|\u2656|\u2658|\u2657|\u2655|\u2654|\u2658|\u2657|\u2656|1\n -a-b-c-d-e-f-g-h-\n");

}

void next_move(char board[8][8][4], char* move, size_t buff_size){

	getline(&move,&buff_size,stdin);
	
//chess piece movement	
}
