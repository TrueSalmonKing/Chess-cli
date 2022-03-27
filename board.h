#ifndef BOARD
#define BOARD

typedef struct Node {
	char move[7];
	struct Node * next;
} Node; 

typedef struct LinkedList {
	int size;
	Node * head;
} LinkedList;

int lane_check(char board[8][8][4], int cpx, int cpy, int mX, int mY);
void next_move(char board[8][8][4], char* move, size_t buff_size);
void current_board(char board[8][8][4], const char* next_move);
int check_move(char board[8][8][4], char* curr_place, char* move);
int colli_handl(char p1[4], char p2[4]);
void add(LinkedList * l, Node * n);
void randomNode(LinkedList * l, Node * n);
void updateLegalMoves(char board[8][8][4], LinkedList * whiteMoves, LinkedList * blackMoves);
void getMoveSyntax(char board[8][8][4], int i, int j, char * move);

#endif
