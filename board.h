#ifndef BOARD
#define BOARD

typedef struct Node {
	char * move;
	struct Node * next;
} Node; 

typedef struct LinkedList {
	int size;
	Node * head;
} LinkedList;

int lane_check(char board[8][8][4], int cpx, int cpy, int mX, int mY);
int next_move(char board[8][8][4], char* move, size_t buff_size, short curr_player);
void current_board(char board[8][8][4]);
int check_move(char board[8][8][4], char* curr_place, char* move, char** piece, char** placement);
int colli_handl(char p1[4], char p2[4]);
void pawn_promotion(char board[8][8][4], int pos);
void add(LinkedList * l, char ** s);
void randomNode(LinkedList * l, Node ** n);
void clear(Node ** head);
void updateLegalMoves(char board[8][8][4], LinkedList * whiteMoves, LinkedList * blackMoves);
void getMoveSyntax(char board[8][8][4], int i, int j, char move[4]);

#endif
