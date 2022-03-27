//To do:
//updateLegalMoves function's logic must be corrected and updated
//board display function must be updated --> unused argument next_move
//Pawn piece conversion
//Pawn En Passant movement
//Regex check must be added to parsed movements
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
//Knight piece collision check must be added (IFF)
//Queen movement
//Initial Pawn movement
//King movement


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include "board.h"

//Program entry point
int main(int argc, char* argv[argc+1]) {

//4 bytes to include both the unicode character (3bytes) and the null pointer (1byte), otherwise it will keep on printing characters from the rest of the adjacent strings

//	Node n1,n2,n3,n4,n5,n6;
//	LinkedList * l = malloc(sizeof(*l));
	LinkedList * whiteMoves = malloc(sizeof(*whiteMoves));
	LinkedList * blackMoves = malloc(sizeof(*blackMoves));
	char * CPU_move = malloc(sizeof(CPU_move)*3);

//	memcpy(n1.move,"BAD BAD",7);
//	memcpy(n2.move,"TOD TOD",7);
//	memcpy(n3.move,"SOS SOS",7);
//	memcpy(n4.move,"POP POP",7);
//	memcpy(n5.move,"ZAP PAP",7);

//	add(l,&n1);
//	add(l,&n2);
//	add(l,&n3);
//	add(l,&n4);
//	add(l,&n5);

//	randomNode(l,&n6);
//	printf("random node = \"%s\"\n",n6.move);

	char board[8][8][4]={
			{"\u265c","\u265e","\u265d","\u265b","\u265a","\u265d","\u265e","\u265c"}
			,{"\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f"}
			,{" "," "," "," "," "," "," "," "}
			,{" ","\u265a"," "," "," "," "," "," "}
			,{" ","\u2659","\u2659"," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{"\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659"}
			,{"\u2656","\u2658","\u2657","\u2655","\u2654","\u2657","\u2658","\u2656"}
			};

//Buffer size set to 7 (movements are in the following syntax [Axi Byj]
	size_t buff_size=7;
	char * current_move=(char *)malloc(sizeof(char)*buff_size);

//Main program loop
	while(1) {
		updateLegalMoves(board,whiteMoves,blackMoves);
		printf("Possible moves for black = %d, Possible moves for white = %d", blackMoves->size, whiteMoves->size);
		current_board(board, current_move);
		printf("\nprevious move: %c%c%c %c %c%c%c \nnext move: ",*current_move,*(current_move+1),*(current_move+2),*(current_move+3),*(current_move+4),*(current_move+5),*(current_move+6));
		next_move(board,current_move, buff_size);
	}
	return 0;

}

//Board printing function
void current_board(char board[8][8][4], const char* next_move) {
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



//Movement validity check function
void next_move(char board[8][8][4], char* move, size_t buff_size) {

	char * move_1 = malloc(sizeof *move_1 * 3);
	char * move_2 = malloc(sizeof *move_2 * 3);
	char delim[]=" ";

//User's input is parsed to get the piece's current position and the desired location to move into
	getline(&move,&buff_size,stdin);
	
	move_1=strtok(move,delim);
	move_2=strtok(NULL,delim);

//Input invalid in the case where no second move can be parsed from the input (e.g no space between the two movements)
	if(move_2 == NULL){
		printf("Invalid move !\n");
		return;
	}
//If the user's input is indeed valid we invoke the function check_move
	if(check_move(board, move_1, move_2))
		printf("Valid move !\n");
}

//next_move merely checks if the user input has two tokens delimeted by a space, check_move then subsequently has to first check the syntax of each
int check_move(char board[8][8][4], char* curr_place, char* move) {
//each chess piece's position on the horizontal axis (x) and vertical axis (y) are assigned two variables cpx and cpy respectivaly, which are mapped accordingly with [a-h] -> [0-7]. We do the same for the positions of the location the player wants to move the piece to with variables mx and my
	int cpx=curr_place[1]-'a';
	int cpy=curr_place[2]-'1';
	int mx=move[1]-'a';
	int my=move[2]-'1';
	char * piece = board[cpy][cpx];
	char * placement = board[my][mx];

//a is the horizontal movement vector magnitude, and b is the vertical movement vector magnitude
	int a=mx-cpx;
	int b=my-cpy;
	int rc = -1;

// Usage of regex is still reaquired !
//	regex_t regex;

//	rc=regcomp(&regex, "[RNBKQP][a-h][1-8]",0);

// !!!!!!!!!!!!!!! MUST CHECK WHY REGEX DOESN'T ACCEPT "?"
//	rc=regcomp(&regex, "[RNBKQ]?[a-h][1-8]",0);
//	rc=regexec(&regex,move,0,NULL,0);

//Depending on the chosen piece, we invoke a specific if statement
//For each piece, mx and my must not exceed 7, which would result in the piece going out of the board, as such we check for this in the following bitwise operation:
//	!((my)>>3) && !((mx)>>3)
//Each current position cpx, cpy must have the unicode representation of the piece required to move, which is indicated by the first letter --> checked with strcmp
//In the case of a collision the funciton colli_handl is called, supplied with both the current position of the piece and the position of the collision
	switch (move[0]) {
//Knight chess piece
//Knight movement corresponds to one move in one axis, with two moves in the other axis, as such we check for this in the following bitwise operation:
//	( (a&2)&&(b&1) ^ (a&1)&&(b&2) )
//Knight ches piece has no collision checks, except if the moved to board position isn't empty
		case 'N':
			printf("%s %s\n",piece, placement);
			if((!strcmp(piece,"\u265e") || !strcmp(piece,"\u2658")) && (!((mx)>>3)&&!((my)>>3)) && (((a&2)&&(b&1))^((a&1)&&(b&2))) && colli_handl(piece,placement)) {
				strcpy(placement,piece);
				strcpy(piece," ");
				return 1;
			};
			return 0;
//Rook chess piece
//Knight movement corresponds to movement in only one axis, as such we check for that with !a or !b, we also have to ensure that the traversed lane with the rook piece must be checked in the case where a collision occurs with a piece, we perform this check with the function lane_check
		case 'R':
			if((!strcmp(piece,"\u265c") || !strcmp(piece,"\u2656")) && (!((mx)>>3)&&!((my)>>3)) && (!a && lane_check(board,cpx,cpy,a,b))^(!b && lane_check(board,cpx,cpy,a,b))) {
				strcpy(placement,piece);
				strcpy(piece," ");
				return 1;
			};
			return 0;
//Bishop chess piece
//Bishop movement corresponds to same movement magnitude in both axises, as such we check for that with the following:
//	a<<29 && b<<29
//Similar to the rook piece, lane_check must be called
		case 'B':
			if((!strcmp(piece,"\u265d") || !strcmp(piece,"\u2657")) && (!((mx)>>3)&&!((my)>>3)) && a<<29&b<<29 && lane_check(board,cpx,cpy,a,b)) {
				strcpy(placement,piece);
				strcpy(piece," ");
				return 1;
			}
			return 0;
//Queen chess piece
//Queen combines both the logic of Rook and Bishop
		case 'Q':
			if((!strcmp(piece,"\u265a") || !strcmp(piece,"\u2654")) && (!((mx)>>3)&&!((my)>>3)) && (a<<29&b<<29 || (!a^!b)) && lane_check(board,cpx,cpy,a,b)) {
				strcpy(placement,piece);
				strcpy(piece," ");
				return 1;
			}
			return 0;
//Pawn chess piece
//Pawn movement corresponds to movement in only one placement in the y-axis (checked using (!a) and !(b-1) if the piece is on the black side, and !(b+1) otherwise), with the possibility of two placements if it's the first movement of the pawn piece and if the placement is empty (checked using (!a), strcmp(board[my][mx]," ") and !(b-2) if the piece is on the black side or !(b+2) otherwise). If the Pawn piece is able to capture an opposing piece then the placement is checked for if it's empty, if not then we confirm that it's indeed an opposing piece (checked using !(a-1)^!(a+1) which works for both colors of pawn pieces, strcmp(board[my][mx]," ") and the same logic using in colli_handl minus the possibility to go to an empty placement)
		case 'P':
//Black Pawn case
			if(!strcmp(piece,"\u265f") && (!((mx)>>3)&&!((my)>>3)) 
&& ((!(b-2) && !a && !(cpy-1) && !strcmp(placement," ")) || 
(!(b-1) && (!strcmp(placement, " ") ? !a : !(a-1)^!(a+1) && ((piece[2]-0x94)&0xFF)/6 == !(((placement[2]-0x94)&0xFF)/6)))
)) {
				strcpy(placement,piece);
				strcpy(piece," ");
				return 1;
				
			};
			return 0;
//White Pawn case
			if(!strcmp(piece,"\u2659") && (!((mx)>>3)&&!((my)>>3)) 
&& ((!(b+2) && !a && !(cpy+1) && !strcmp(placement," ")) || 
((!(b+1) && (!strcmp(placement," ")) ? !a : !(a-1)^!(a+1) && ((piece[2]-0x94)&0xFF)/6 == !(((placement[2]-0x94)&0xFF)/6)))
)) {
				strcpy(board[my][mx],board[cpy][cpx]);
				strcpy(board[cpy][cpx]," ");
				return 1;
				
			};
			return 0;
//King chess piece
//Allows for movement in any placement with one displacement in each axis
		case 'K':
			if((!strcmp(piece,"\u265a") || !strcmp(piece,"\u2654")) && (!((mx)>>3)&&!((my)>>3)) && (!(((a+(a>>31))^(a>>31))>>1)&&!(((b+(b>>31))^(b>>31))>>1)) && colli_handl(piece,placement)) {
				strcpy(placement,piece);
				strcpy(piece," ");
				return 1;
				
			};
			return 0;
		default:
			printf("Invalid !\n");
			return rc;
	}
}

//The main function that checks whether a specific lane during movement is empty for the rook, bishop and queen pieces
int lane_check(char board[8][8][4], int cpx, int cpy, int mX, int mY) {

	int iter = ((!!mX) | (mX >> 31)) ? 1 : -1;
	int i=0, j=0, k=0, si, sj, x, y;
	int maskX = (mX>>31);
	int maskY = (mY>>31);
	printf("mX= %d, iter= %d, X=%d\n", mX, iter);
	printf("CASE 2\n\n\n");
	y = (((mX+maskX)^maskX) - ((mY+maskY)^maskY))>>31 ? mY : mX;
	si = !mX ? 0 : maskX ? -1 : 1;
	sj = !mY ? 0 : maskY ? -1 : 1;
	x = !y ? 0 : (y>>31) ? -1 : 1;
	printf("\n\n IWJEFLWEFLWE y=%d, si=%d, sj=%d, x=%d\n\n", y,si,sj,x);

	do{
		i+=si;
		j+=sj;
		k+=x;
		printf("mX=%d, mY=%d\n", mX, mY);
		printf("cpy=%d, cpx=%d, %s\n", cpy+j, cpx+i, board[cpy+j][cpx+i]);
		if(!strcmp(board[cpy+j][cpx+i]," "))
			printf("empty");
		else {
			printf("Collision !\n");
			return y-k ? 0 : colli_handl(board[cpy][cpx], board[cpy+j][cpx+i]);
		}
	} while(y-k);

	return 1;
}

int colli_handl(char p1[4], char p2[4]) {

//colli_handl only gets called if the board piece ISN'T a space
//UPDATED LOGIC TO ACCOUNT FOR EMPTY PLACEMENTS = the first check is to ensure that the knight movement is able have a collision check as well. A simple xor to ensure that the knight piece is able to move when no piece is on the targeted placement
//first we compare if its third hex value is larger than 0x93 (smallest chess piece is E2 99 94) and we divide by 6, as the smallest black chess piece has value E2 99 9A (9A - 94 = 6), to check whether it is a black of white piece, we proceed to get the bit value of its range (0 if white, 1 if black) and we XNOR it to the value get from the same operation done on the second piece
//if differing pieces' collision occurs --> 1 is returned
	return !strcmp(p1," ") ^ !strcmp(p2, " ") ? 1 : ((p1[2]-0x94)&0xFF)/6 == !(((p2[2]-0x94)&0xFF)/6);

}

void add(LinkedList * l, Node * n) {

	if(!l->head){
		n->next=NULL;
		l->head=n;
		l->size=1;
		return;
	}

	if(!l->head->next){
		n->next=NULL;
		l->head->next=n;
		l->size=2;
		return;
	}

	Node * iterator_n = l->head->next;

	while(iterator_n->next)
		iterator_n = iterator_n->next;

	++l->size;

	iterator_n->next = n;
	n->next=NULL;
}

void randomNode(LinkedList * l, Node * n) {

	if(!l) {
		printf("Empty list");
		return;
	}

	srand(time(NULL));
	int r = rand() % l->size;

	Node * iterator_n = malloc(sizeof(*iterator_n));

	iterator_n = l->head;
	int i = 0;

	while(r>i && iterator_n->next) {
		++i;
		iterator_n = iterator_n->next;
	}

	*n=*iterator_n;
}

void updateLegalMoves(char board[8][8][4], LinkedList * whiteMoves, LinkedList * blackMoves) {
	int i = 0;
	char * curr_place = malloc(sizeof(curr_place) * 3);
	char * mov_place = malloc(sizeof(mov_place) * 3);

	while(i<64) {
		if(strcmp(board[i%8][i/8], " ")) {
			if(strcmp(board[i%8][i/8], "\u2658")) {
				for(int j=1;j<3;j++) {
					for(int k=1;k<3;k++) {
						curr_place = board[i%8][i/8];
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(whiteMoves,n);
							break;
						}
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(whiteMoves,n);
							break;
						}
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(whiteMoves,n);
							break;
						}
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(whiteMoves,n);
							break;
						}
					}
				}
			}
			if(strcmp(board[i%8][i/8], "\u265e")) {
				for(int j=1;j<3;j++) {
					for(int k=1;k<3;k++) {
						curr_place = board[i%8][i/8];
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(blackMoves,n);
							break;
						}
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(blackMoves,n);
							break;
						}
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(blackMoves,n);
							break;
						}
						mov_place = board[(i%8+k)%8][(i/8+j)%8];
						if(check_move(board,curr_place,mov_place)){
							Node * n = malloc(sizeof(*n));
							add(blackMoves,n);
							break;
						}
					}
				}
			}
		}
		++i;
	}
}

//Function that converts a specific piece's placement into Chess's algebraic notation
void getMoveSyntax(char board[8][8][4], int i, int j, char * move) {

	if(board[j][i][0]&0xE2 && board[j][i][1]&0x99) {
		switch(board[j][i][2]) {
			case (signed char) 0x98:
				move[0] = 'N';
				break;
			case (signed char) 0x9E:
				move[0] = 'N';
				break;
			case (signed char) 0x96:
				move[0] = 'R';
				break;
			case (signed char) 0x9C:
				move[0] = 'R';
				break;
			case (signed char) 0x97:
				move[0] = 'B';
				break;
			case (signed char) 0x9D:
				move[0] = 'B';
				break;
			case (signed char) 0x95:
				move[0] = 'Q';
				break;
			case (signed char) 0x9B:
				move[0] = 'Q';
				break;
			case (signed char) 0x94:
				move[0] = 'K';
				break;
			case (signed char) 0x9A:
				move[0] = 'K';
				break;
			case (signed char) 0x99:
				move[0] = 'P';
				break;
			case (signed char) 0x9F:
				move[0] = 'P';
				break;
		}
		move[1] = i + 'a';
		move[2] = j + '1';
	}
}
