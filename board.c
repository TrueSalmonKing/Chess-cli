//To do:
//King capturing king move should be illegal !
//Pawn En Passant movement
//Regex check must be added to parsed movements
//Co-op playstyle implementation (Timer + Checkmate + Stalemate + Win/Lose/Draw + Replay)
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
//Segmentaion fault on egal moves LinkedList clear...
//Set linkedlist head node to null after clearing the list inside the function
//board display function must be updated --> unused argument next_move
//Pawn piece conversion
//updateLegalMoves function's logic must be corrected and updated
//getMoveSyntax redundancy must be checked! (Switch case redudancy unable to be reduced further)
//Co-op playstyle barebones implementation (turns)
//Error must be fixed in last two lines in next_move(), relating to freeing the allocated memory for the two strings (Can't free space !! --> ERROR : free(): invalid pointer)
//Checkmate check during each move's attempt
//Checkmate + Stalemate implemented


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
	Node * n = malloc(sizeof(*n));

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

	char board_t[8][8][4]={
			{"\u265c","\u265e","\u265d","\u265b","\u265a","\u265d","\u265e","\u265c"}
			,{"\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f","\u265f"}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{"\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659"}
			,{"\u2656","\u2658","\u2657","\u2655","\u2654","\u2657","\u2658","\u2656"}
			};

	char board_t_two[8][8][4]={
			{" "," "," "," "," "," "," ","\u2654"}
			,{"\u265c"," ","\u265b"," "," "," "," "," "}
			,{" "," "," "," "," "," ","\u265f"," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			};

	char board[8][8][4]={
			{"\u2654"," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{"\u265f","\u265a"," ","\u265d"," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			};

//Buffer size set to 7 (movements are in the following syntax [Axi Byj]
	size_t buff_size=7;
	char * current_move=(char *)malloc(sizeof(char)*buff_size);
	char * previous_move=(char *)malloc(sizeof(char)*buff_size);
	char color[2][6] = {"white", "black"};
//i regulates players' turns:
//0 signifies white's turn, while 1 signifies black's
	short i = 0;
	int moved_status = 0;

//Main program loop
	while(1) {
		current_board(board);
		printf("\nnext move: ");
		moved_status = next_move(board,current_move, buff_size, i);
		if(moved_status){
			previous_move[0] = current_move[0];
			previous_move[1] = current_move[1];
			previous_move[2] = current_move[2];
			previous_move[3] = current_move[3];
			previous_move[4] = current_move[4];
			previous_move[5] = current_move[5];
			previous_move[6] = current_move[6];
		}
		i = moved_status ? (i+1)%2 : i;
//Error must be fixed in last two lines in next_move(), relating to freeing the allocated memory for the two strings (Can't free space !! --> ERROR : free(): invalid pointer)
		//randomNode(blackMoves,&n);
		//printf("RANDOM BLACK NODE: '%s'", n->move);
		//printf("clearing white list\n");
		clear(&whiteMoves->head);
		//printf("clearing black list\n");
		clear(&blackMoves->head);
		updateLegalMoves(board,whiteMoves,blackMoves);
		//printf("Possible moves for black = %d, Possible moves for white = %d", blackMoves->size, whiteMoves->size);

		if(moved_status) {
			if(!i)
				if(checkMate(board, whiteMoves, i)) {
					if(!(inCheck(board)+1))
						printf("Stalemate !\n");
					else
						printf("Game Over ! Black Won with last move %c%c%c %c %c%c%c\n",*previous_move,*(previous_move+1),*(previous_move+2),*(previous_move+3),*(previous_move+4),*(previous_move+5),*(previous_move+6));
					current_board(board);
					break;
				}
			else{
				if(checkMate(board, blackMoves, i)) {
					if(!(inCheck(board)+1))
						printf("Stalemate !\n");
					else
						printf("Game Over ! White Won with last move %c%c%c %c %c%c%c\n",*previous_move,*(previous_move+1),*(previous_move+2),*(previous_move+3),*(previous_move+4),*(previous_move+5),*(previous_move+6));
					current_board(board);
					break;
				}
			}
		}
		printf("\n%s's turn !\nprevious move: %c%c%c %c %c%c%c\n",color[i],*previous_move,*(previous_move+1),*(previous_move+2),*(previous_move+3),*(previous_move+4),*(previous_move+5),*(previous_move+6));
	}
	return 0;

}

//Board printing function
void current_board(char board[8][8][4]) {
	printf("\n _a_b_c_d_e_f_g_h\n");
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
//Return 1 if a piece has been moved
int next_move(char board[8][8][4], char* move, size_t buff_size, short curr_player) {

	char * move_1 = malloc(sizeof(*move_1) * 4);
	char * move_2 = malloc(sizeof(*move_2) * 4);
	char delim[]=" ";
	char * piece;
	char * placement;

//User's input is parsed to get the piece's current position and the desired location to move into
	getline(&move,&buff_size,stdin);
	
	move_1=strtok(move,delim);
	move_2=strtok(NULL,delim);
//Input invalid in the case where no second move can be parsed from the input (e.g no space between the two movements)
	if(move_2 == NULL){
		printf("Invalid move !\n");
		return 0;
	}
//If the user's input is indeed valid we invoke the function check_move
//We also verify that the current moving piece indeed has the turn to move by a simple xor with the inverse of the last byte of the chess piece's unicode representation (it ranges from 0x94 to 0x99 for white pieces, and 0x9A to 0x9F for black pieces)
	//printf("curr player = %x while %x\n", curr_player, (((board[move_1[2]-'1'][move_1[1]-'a'][2]-0x94)&0xFF)/6));
	if(check_move(board, move_1, move_2, &piece, &placement) && ((((board[move_1[2]-'1'][move_1[1]-'a'][2]-0x94)&0xFF)/6)^!curr_player) ) {
		printf("Valid move !\n");
		strcpy(placement,piece);
		strcpy(piece," ");
		int inc = inCheck(board);
		printf("IN CHECK VALUE = %d\n",inc);
		if(inc != -1 && inc == curr_player) {
			strcpy(piece,placement);
			strcpy(placement," ");
			printf("Illegal move !\n");
			return 0;
		}

		switch(inc) {
			case 0:
				printf("White in check !\n");
				goto default_case;
			case 1:
				printf("Black in check !\n");
				goto default_case;
			default_case:
			default:
				pawn_promotion(board, (move_2[2]-'1') + (move_2[1]-'a')*8);
				return 1;
		}
		
	} else
		printf("Invalid move!!\n");
		return 0;

	free(move_1);
	free(move_2);
}

//next_move merely checks if the user input has two tokens delimeted by a space, check_move then subsequently has to first check the syntax of each
int check_move(char board[8][8][4], char* curr_place, char* move, char ** piece, char ** placement) {
//each chess piece's position on the horizontal axis (x) and vertical axis (y) are assigned two variables cpx and cpy respectivaly, which are mapped accordingly with [a-h] -> [0-7]. We do the same for the positions of the location the player wants to move the piece to with variables mx and my
	int cpx=curr_place[1]-'a';
	int cpy=curr_place[2]-'1';
	int mx=move[1]-'a';
	int my=move[2]-'1';
	if(piece)
		*piece = board[cpy][cpx];
	if(placement)
		*placement = board[my][mx];

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
//	( !(a^2)&&!(b^1) ^ !(a^1)&&!(b^2) )
//After we return the absolute value of both movement values a and b
//Knight ches piece has no collision checks, except if the moved to board position isn't empty
		case 'N':
			a = ((a+(a>>31))^(a>>31));
			b = ((b+(b>>31))^(b>>31));
			//printf("%s %s\n",board[cpy][cpx], board[my][mx]);
			if((!strcmp(board[cpy][cpx],"\u265e") || !strcmp(board[cpy][cpx],"\u2658")) && (!((mx)>>3)&&!((my)>>3)) && ((!(a^2)&&!(b^1))^(!(a^1)&&!(b^2))) && colli_handl(board[cpy][cpx],board[my][mx])) {
				return 1;
			};
			return 0;
//Rook chess piece
//Knight movement corresponds to movement in only one axis, as such we check for that with !a or !b, we also have to ensure that the traversed lane with the rook piece must be checked in the case where a collision occurs with a board[cpy][cpx], we perform this check with the function lane_check
		case 'R':
			if((!strcmp(board[cpy][cpx],"\u265c") || !strcmp(board[cpy][cpx],"\u2656")) && (!((mx)>>3)&&!((my)>>3)) && (!a && lane_check(board,cpx,cpy,a,b))^(!b && lane_check(board,cpx,cpy,a,b))) {
				return 1;
			};
			return 0;
//Bishop chess piece
//Bishop movement corresponds to same movement magnitude in both axises, as such we check for that with the following:
//	(!(a-b) || !(a+b))
//Similar to the rook board[cpy][cpx], lane_check must be called
		case 'B':
			//printf("a=%d, b=%d\n",a,b);
			if((!strcmp(board[cpy][cpx],"\u265d") || !strcmp(board[cpy][cpx],"\u2657")) && (!((mx)>>3)&&!((my)>>3)) && (!(a-b) || !(a+b)) && lane_check(board,cpx,cpy,a,b)) {
				return 1;
			}
			return 0;
//Queen chess piece
//Queen combines both the logic of Rook and Bishop
		case 'Q':
			if((!strcmp(board[cpy][cpx],"\u265b") || !strcmp(board[cpy][cpx],"\u2655")) && (!((mx)>>3)&&!((my)>>3)) && ((!(a-b) || !(a+b)) && lane_check(board,cpx,cpy,a,b) || (!a && lane_check(board,cpx,cpy,a,b))^(!b && lane_check(board,cpx,cpy,a,b)))) {
				return 1;
			}
			return 0;
//Pawn chess piece
//Pawn movement corresponds to movement in only one placement in the y-axis (checked using (!a) and !(b-1) if the piece is on the black side, and !(b+1) otherwise), with the possibility of two placements if it's the first movement of the pawn piece (chcked using (cpy-1) for black pieces and (cpy-6) for the white pawn pieces) and if the placement is empty (checked using (!a), strcmp(board[my][mx]," ") and !(b-2) if the piece is on the black side or !(b+2) otherwise). If the Pawn piece is able to capture an opposing piece then the placement is checked for if it's empty, if not then we confirm that it's indeed an opposing piece (checked using !(a-1)^!(a+1) which works for both colors of pawn pieces, strcmp(board[my][mx]," ") and the same logic using in colli_handl minus the possibility to go to an empty placement
//For the pawn's last logical expression, it the same one used below in colli_handl
//In this case it is used to account for the case where a pawn is attempting to capture an opposing piece ---|
//											  		     |
//											  		     |
//											  		     V
//First we compare if its third hex value is larger than 0x93 (smallest chess piece is E2 99 94) and we divide by 6, as the smallest black chess piece has value E2 99 9A (9A - 94 = 6), to check whether it is a black or white piece, we proceed to get the bit value of its range (0 if white, 1 if black) and we XOR it to the value get from the same operation done on the second piece
//if differing pieces' collide --> 1 is returned, signaling that the movement is valid, and this allows the pawn to capture an opposing piece
		case 'P':
//Black Pawn case
			if(!strcmp(board[cpy][cpx],"\u265f") && (!((mx)>>3)&&!((my)>>3)) 
&& ((!(b-2) && !a && !(cpy-1) && !strcmp(board[my][mx]," ")) || 
(!(b-1) && (!strcmp(board[my][mx]," ") ? !a : !(a-1)^!(a+1) && ((board[cpy][cpx][2]-0x94)&0xFF)/6 ^ (((board[my][mx][2]-0x94)&0xFF)/6)))
)) {
				return 1;
				
			};
//White Pawn case
			if(!strcmp(board[cpy][cpx],"\u2659") && (!((mx)>>3)&&!((my)>>3)) 
&& ((!(b+2) && !a && !(cpy-6) && !strcmp(board[my][mx]," ")) || 
(!(b+1) && (!strcmp(board[my][mx]," ") ? !a : !(a-1)^!(a+1) && ((board[cpy][cpx][2]-0x94)&0xFF)/6 ^ (((board[my][mx][2]-0x94)&0xFF)/6)))
)) {
				return 1;
				
			};
			return 0;
//King chess piece
//Allows for movement in any placement with one displacement in each axis
		case 'K':
			if((!strcmp(board[cpy][cpx],"\u265a") || !strcmp(board[cpy][cpx],"\u2654")) && (!((mx)>>3)&&!((my)>>3)) && (!(((a+(a>>31))^(a>>31))>>1)&&!(((b+(b>>31))^(b>>31))>>1)) && colli_handl(board[cpy][cpx],board[my][mx])) {
				return 1;
				
			};
			return 0;
		default:
			return 0;
	}
}

//The main function that checks whether a specific lane during movement is empty for the rook, bishop and queen pieces
int lane_check(char board[8][8][4], int cpx, int cpy, int mX, int mY) {

	int iter = ((!!mX) | (mX >> 31)) ? 1 : -1;
	int i=0, j=0, k=0, si, sj, x, y;
	int maskX = (mX>>31);
	int maskY = (mY>>31);
	//printf("mX= %d, iter= %d, X=%d\n", mX, iter);
	//printf("CASE 2\n\n\n");
	y = (((mX+maskX)^maskX) - ((mY+maskY)^maskY))>>31 ? mY : mX;
	si = !mX ? 0 : maskX ? -1 : 1;
	sj = !mY ? 0 : maskY ? -1 : 1;
	x = !y ? 0 : (y>>31) ? -1 : 1;
	//printf("\n\n IWJEFLWEFLWE y=%d, si=%d, sj=%d, x=%d\n\n", y,si,sj,x);

	do{
		i+=si;
		j+=sj;
		k+=x;
		//printf("mX=%d, mY=%d\n", mX, mY);
		//printf("cpy=%d, cpx=%d, %s\n", cpy+j, cpx+i, board[cpy+j][cpx+i]);
		if(strcmp(board[cpy+j][cpx+i]," "))
			//printf("empty");
		//else {
			//printf("Collision !\n");
			return y-k ? 0 : colli_handl(board[cpy][cpx], board[cpy+j][cpx+i]);
	//	}
	} while(y-k);

	return 1;
}

int colli_handl(char p1[4], char p2[4]) {

//colli_handl only gets called if the board piece ISN'T a space
//UPDATED LOGIC TO ACCOUNT FOR EMPTY PLACEMENTS = the first check is to ensure that the knight movement is able have a collision check as well. A simple xor to ensure that the knight piece is able to move when no piece is on the targeted placement
//first we compare if its third hex value is larger than 0x93 (smallest chess piece is E2 99 94) and we divide by 6, as the smallest black chess piece has value E2 99 9A (9A - 94 = 6), to check whether it is a black or white piece, we proceed to get the bit value of its range (0 if white, 1 if black) and we XOR it to the value get from the same operation done on the second piece
//if differing pieces' collision occurs --> 1 is returned
	return !strcmp(p1," ") ^ !strcmp(p2, " ") ? 1 : ((p1[2]-0x94)&0xFF)/6 ^ (((p2[2]-0x94)&0xFF)/6);

}

void pawn_promotion(char board[8][8][4], int pos) {

	if(!(pos%8) && !strcmp(board[pos%8][pos/8], "\u2659") || !((pos+1)%8) && !strcmp(board[pos%8][pos/8] ,"\u265f")){
		char * promotion_target = malloc(2);
		char delim[]=" ";
		size_t buff_size = 1;

		printf("To which piece should the pawn in %c%c be promoted?\nQ : queen\nR : rook\nB : bishop\nK : knight\n",(pos/8 + 'a'), (pos%8+'1'));

		//User's input is parsed to get the piece's current position and the desired location to move into
		getline(&promotion_target,&buff_size,stdin);
		//Both black and white chess pieces have the same order of pieces with respect to their unicode byte representation (E2999F, E2999E, E2999D, E2999C, E2999B and E2999A for black pawn, knight, bishop, rook and queen respectively. E29999...E29994 for white pawn, knight, bishop, rook and queen respectively), as such we can promote to other pieces simply by decrementing the last byte value
		switch(*promotion_target) {
			case 'Q':
				board[pos%8][pos/8][2] = board[pos%8][pos/8][2] - 4;
				break;
			case 'R':
				board[pos%8][pos/8][2] = board[pos%8][pos/8][2] - 3;
				break;
			case 'B':
				board[pos%8][pos/8][2] = board[pos%8][pos/8][2] - 2;
				break;
			case 'K':
				board[pos%8][pos/8][2] = board[pos%8][pos/8][2] - 1;
				break;
		}
		

		free(promotion_target);
	}
}

void add(LinkedList * l, char ** s) {

	//printf("adding %s\n\n", *s);
	if(!s)
		return;

	if(!l->head){
		Node * n = malloc(sizeof(*n));
		n->next=NULL;
		n->move = *s;
		l->head=n;
		l->size=1;
		return;
	}

	if(!l->head->next){
		Node * n = malloc(sizeof(*n));
		n->next=NULL;
		n->move = *s;
		l->head->next=n;
		l->size=2;
		return;
	}

	Node * n = malloc(sizeof(*n));
	Node * iterator_n = l->head->next;

	while(iterator_n->next)
		iterator_n = iterator_n->next;

	++l->size;

	iterator_n->next = n;
	n->next=NULL;
	n->move = *s;
}

void randomNode(LinkedList * l, Node ** n) {

	if(!l) {
		//printf("Empty list");
		return;
	}

	srand(time(NULL));
	int r = rand() % l->size;
	//printf("RANDOM VALUE %d !\n",r);

	Node * iterator_n = malloc(sizeof(*iterator_n));

	iterator_n = l->head;
	int i = 0;

	while(r>i && iterator_n->next) {
		//printf("LOOKING FOR VALUE R=%d AND MOVE=%s !\n",r,iterator_n->move);
		++i;
		iterator_n = iterator_n->next;
	}

	*n=iterator_n;
}

void clear(Node ** head) {

	Node * temp = *head;	

	while(*head){
		temp = *head;
		*head = (*head)->next;
		temp->next=NULL;
		temp->move=NULL;
		free(temp->move);
		free(temp);
	}

	*head = NULL;
}

void updateLegalMoves(char board[8][8][4], LinkedList * whiteMoves, LinkedList * blackMoves) {
	int i = 0, j = 0, k = 0;
	char curr_place[4] = "";
	char mov_place[4] = "";

	while(i<64) {
		if(strcmp(board[i%8][i/8], " ")) {
			getMoveSyntax(board,i/8,i%8,curr_place);
			mov_place[0] = curr_place[0];
			//printf("\n\nPIECE IS %s AND WE GOT CURR PLACE = %s with j=%d\n\n\n",board[i%8][i/8], curr_place,j);

			while(j<64) {
				getMoveSyntax(board,j/8,j%8,mov_place);
//ISSUE MUST BE LOOKED INTO --> CALLING getMoveSyntax resets the mov_place[0] to the previous piece's value (from K to P)
				mov_place[0] = curr_place[0];
				//printf("i=%d and j=%d and CURR_PLACE='%s' and MOV_PLACE='%s' and check_move value is %d\n",i, j, curr_place, mov_place, check_move(board,curr_place,mov_place, NULL, NULL));
				if((i-j) && check_move(board,curr_place,mov_place, NULL, NULL)) {
					//printf("i=%d and j=%d and CURR_PLACE='%s' and MOV_PLACE='%s'\n",i, j, curr_place, mov_place);
					//printf("TESTING\n");

					char * move = malloc(sizeof(char*)*8);
					move[0] = curr_place[0];
					move[1] = curr_place[1];
					move[2] = curr_place[2];
					move[3] = ' ';
					move[4] = mov_place[0];
					move[5] = mov_place[1];
					move[6] = mov_place[2];
					move[7] = '\0';
			

					//printf("MOVE = %s\n",move);
					((board[i%8][i/8][2]-0x94)&0xFF)/6 ? add(blackMoves,&move) : add(whiteMoves,&move);
					//printf("ADDED %s", move);
				//	printf("ooooooooo");
				}
				++j;
			}
		}

		j=0;
		++i;
	}
}

//Function that converts a specific piece's placement into Chess's algebraic notation
void getMoveSyntax(char board[8][8][4], int i, int j, char move[4]) {

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

//Movement place case
	else {
		move[1] = i + 'a';
		move[2] = j + '1';
	}
}

//Function that looks for checks for both black and white side:
//0 is returned back in the case where black king is in check
//1 is returned back in the case where white king is in check
int inCheck(char board[8][8][4]) {
	
	unsigned i = 0;
	unsigned whiteKingIndx = -1;
	unsigned blackKingIndx = -1;
	int ret = -1;

//We loop over the entire board to find both kings
	while(i<64) {
		if(!(whiteKingIndx+1) && !strcmp(board[i%8][i/8], "\u2654")) {
			//printf("found white king ! %d\n", i);
			whiteKingIndx = i;
		}

		if(!(blackKingIndx+1) && !strcmp(board[i%8][i/8], "\u265a")) {
			//printf("found black king ! %d\n", i);
			blackKingIndx = i;
		}

		++i;
	}

	LinkedList * whiteMoves = malloc(sizeof(*whiteMoves));
	LinkedList * blackMoves = malloc(sizeof(*blackMoves));

//We get all possible moves for both players
	updateLegalMoves(board, whiteMoves, blackMoves);
		
	Node * wHead = whiteMoves->head;
	Node * bHead = blackMoves->head;


	while(bHead){
//If a move from a black piece results in it landing in the white king's position, effectively capturing it, we return 0 (-1 + 1) to signify that white is in check
		if(whiteKingIndx != -1 && ((bHead->move[5]-'a')==(whiteKingIndx/8)) && ((bHead->move[6]-'1')==(whiteKingIndx%8))){
			ret += 1;
			break;
		}

		if(bHead)
			bHead = bHead->next;
	}

	while(wHead){
//If a move from a white piece results in it landing in the black king's position, effectively capturing it, we return 1 (-1 + 2) to signify that black is in check
		if(blackKingIndx != -1 && ((wHead->move[5]-'a')==(blackKingIndx/8)) && ((wHead->move[6]-'1')==(blackKingIndx%8))){
			ret += 2;
			break;
		}

		if(wHead)
			wHead = wHead->next;
	}

	clear(&whiteMoves->head);
	clear(&blackMoves->head);
	free(whiteMoves);
	free(blackMoves);

//Even though it is impossible for both sides to be in check at the same time, we account for this by returning 2 in the case where this occurs as (-1 + 1 +2)
	return ret;
}

//Function that checks whether the current side is in checkmate for both black and white side:
//Is in the case where the current player is white, and black just played before it a move that placed white's king in checkmate, 1 is returned, if it simple check or the king is not in check at all, then 0 is returned. The same values are returned in the case of the current player being black
int checkMate(char board[8][8][4], LinkedList * Moves, int curr_player) {


//We initialize an empty chess board
	char board_temp[8][8][4]={
			{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			,{" "," "," "," "," "," "," "," "}
			};
	char * move_1 = malloc(sizeof(*move_1) * 4);
	char * move_2 = malloc(sizeof(*move_2) * 4);
	char delim[]=" ";
	char * piece;
	char * placement;
	int inc = -1;

//We iterate through all possible moves in current player's possible moves' list
	while(Moves->head->next){

		move_1=strtok(Moves->head->move,delim);
		move_2=strtok(NULL,delim);

//We store the previous version of the board in order to avoid accidently removing pieces during checkmate check by the double string copy operation below
		memcpy(board_temp,board,sizeof(char)*(8*8*4));
		current_board(board_temp);
		strcpy(placement,piece);
		strcpy(piece," ");
//We store the value of inCheck to confirm whether white or black are in check
		inc = inCheck(board);

//We restore the previous board state
		memcpy(board,board_temp,sizeof(char)*(8*8*4));
		current_board(board);

//In the case where a possible move for the current player results in either the player that is in check isn't the same as the current player, if the player isn't in check or if somehow both players are in check (impossible under normal circumstances) we exit the function
		if(inc != curr_player && inc < 2) {
			return 0;
		}

		if(Moves->head->next)
			Moves->head = Moves->head->next;
	}

//If all possible moves from the current player result in a check, then we return 1 signifying that the current player is indeed in check
	return 1;

}
