//Final Project
// December 15th, 2016
//Matthew Fabian

// Preprocessor Directives
#include <iostream>
#include "gfxnew.h"
#include <cmath>
#include <unistd.h>
#include <array>
#include <math.h> 
using namespace std;
#include "finalclass.h"

// Global Variables 
int xOffset = 50;
int yOffset = 50;
float side = 75;
Chessboard board;

// Function Prototypes
void drawBoard();
void newBoard();
void updateBoard();
bool checkRules(int x1, int y1, int x2, int y2, char c1, char c2, char &turn);
void updatePosition(int x, int y);
void clearPosition(int x, int y);
void movePiece(int x1, int y1, int x2, int y2, char &turn);
void drawPawn(int x, int y, char color);
void drawRook(int x, int y, char color);
void drawBishop(int x, int y, char color);
void drawQueen(int x, int y, char color);
void drawKing(int x, int y, char color);
void drawKnight(int x, int y, char color);
void highlightCell(int x, int y);
char switchTurns(char turn);
bool checkTurn(char c, char turn);
bool checkRook(int x1, int y1, int x2, int y2);
bool checkBishop(int x1, int y1, int x2, int y2);
bool checkKnight(int x1, int y1, int x2, int y2);
bool checkKing(int x1, int y1, int x2, int y2);
bool checkQueen(int x1, int y1, int x2, int y2);
bool checkPawn(int x1, int y1, int x2, int y2, char c1, char c2);
bool checkCollision(int x1, int y1, int x2, int y2);

// Main Function
int main(){

	bool quit = false;
	bool done = false;
	bool clickedOnce = false;
	char turn = 'W';
	char c;
	char c2;
	float x1;
	float y1;
	float y2;
	float x2;
	int event;

	gfx_open(700, 700, "Chess");
	gfx_fill_rectangle(0,0,700,700);
	drawBoard();
	newBoard();
	gfx_flush();
	while (!quit){
		if((event = gfx_event_waiting()) != 0){
			c = gfx_wait();
			if (c == 1){
				if (event == 3){
					if (!clickedOnce){
						x1 = floor(((gfx_xpos() - xOffset)/side));
						y1 = floor(((gfx_ypos() - yOffset)/side));
						c2 = board.getSquareValue(y1, x1);
						bool yourTurn = checkTurn(c2, turn);
						if (yourTurn){
							highlightCell(x1, y1);
							clickedOnce = true;
						}

					}
					else{
						x2 = floor((gfx_xpos() - xOffset)/side);
						y2 = floor((gfx_ypos() - yOffset)/side);
						movePiece(x1, y1, x2, y2, turn);
						turn = switchTurns(turn);
						updateBoard();
						gfx_flush();
						clickedOnce = false;
					}
				}
			}
			if (c == 'q'){
				quit = true;
			}
		}
	}

	return 0;
}

void drawBoard(){
	int x = xOffset;
	int y = yOffset;
	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if ((i + j)%2){
				// sum is odd
				gfx_color(130, 82, 1);
			} 
			else {
				// sum is even
				gfx_color(182, 155, 76);
			}
			gfx_fill_rectangle(x, y, side, side);
			x = x + side;
		}
		x = x - 8*side;
		y = y + side;
	}
}

void newBoard(){
	board.setNewGame();
	drawBoard();
	updateBoard();


	// Pre Class Implementation
	// Now Obselete

	/*char color = 'W';
	
	for (int i = 0; i < 8; i++){
		drawPawn(xOffset + i*side, yOffset + 6*side, color);
	}
	drawKing(xOffset + 4*side, yOffset + 7*side, color);
	drawRook(xOffset + 0*side, yOffset + 7*side, color);
	drawBishop(xOffset + 2*side, yOffset + 7*side, color);
	drawKnight(xOffset + 1*side, yOffset + 7*side, color);
	drawRook(xOffset + 7*side, yOffset + 7*side, color);
	drawBishop(xOffset + 5*side, yOffset + 7*side, color);
	drawKnight(xOffset + 6*side, yOffset + 7*side, color);
	drawQueen(xOffset + 3*side, yOffset + 7*side, color);
	
	color = 'B';
	for (int i = 0; i < 8; i++){
		drawPawn(xOffset + i*side, yOffset + side, color);
	}
	drawKing(xOffset + 4*side, yOffset, color);
	drawRook(xOffset + 0*side, yOffset, color);
	drawBishop(xOffset + 2*side, yOffset, color);
	drawKnight(xOffset + 1*side, yOffset, color);
	drawRook(xOffset + 7*side, yOffset, color);
	drawBishop(xOffset + 5*side, yOffset, color);
	drawKnight(xOffset + 6*side, yOffset, color);
	drawQueen(xOffset + 3*side, yOffset, color);
	*/
}

void updateBoard(){

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			updatePosition(i, j);
		}
	}

}

void movePiece(int x1, int y1, int x2, int y2, char &turn){
	char c1 = board.getSquareValue(y1, x1);
	char c2 = board.getSquareValue(y2, x2);
	bool rules = checkRules(x1, y1, x2, y2, c1, c2, turn);
	if (rules){
		if (c2 != '#'){
			clearPosition(x2, y2);
		}
		board.setSquareValue(y1, x1, '#');
		clearPosition(x1, y1);
		if((c1 == 'P') && (y1 == 6)){
			// Black Pawn promoting
			board.setSquareValue(y2, x2, 'Q');
		}else if((c1 == 'p') && (y1 == 1)){
			// White Pawn promoting
			board.setSquareValue(y2, x2, 'q');
		}else{
			// Normal movement
			board.setSquareValue(y2, x2, c1);
		}
	}
}

void drawPawn(int x, int y, char color){
	if (color == 'W'){
		gfx_color(255,255,255);
	}
	else{
		gfx_color(0,0,0);
	}
	gfx_fill_circle(x + .5*side, y + .5*side, side/6);
	gfx_fill_circle(x + .5*side, y + .3*side, side/9);
	gfx_fill_arc(x+ .2*side, y + .55*side, .6*side, .5*side, 0, 180);

}

void drawRook(int x, int y, char color){
	if (color == 'W'){
		gfx_color(255,255,255);
	}
	else{
		gfx_color(0,0,0);
	}
	XPoint trapezoid[] = { {x + .2*side,y + .3 * side},{x + .8*side,y + .3*side},
		{x + .7*side,y + .4*side},{x + .3*side,y+.4*side},{x + .2*side,y + .3*side} };
	int num = sizeof(trapezoid)/sizeof(XPoint);
	gfx_fill_polygon(trapezoid, num);
	gfx_fill_rectangle(x + .3*side, y + .4*side, .4*side, .25*side);

	gfx_fill_rectangle(x + .2*side, y + .2*side, .6*side, .1*side);
	gfx_fill_rectangle(x + .2*side, y + .1*side, .1*side, .2*side);
	gfx_fill_rectangle(x + .4*side, y + .1*side, .2*side, .2*side);
	gfx_fill_rectangle(x + .7*side, y + .1*side, .11*side, .2*side);

	XPoint trapezoid2[] = { {x + .3*side,y + .65 * side},{x + .7*side,y + .65*side},
		{x + .8*side,y + .75*side},{x + .2*side,y+.75*side},{x + .3*side,y + .65 * side} };
	int num2 = sizeof(trapezoid2)/sizeof(XPoint);
	gfx_fill_polygon(trapezoid2, num2);

	gfx_fill_rectangle(x + .15*side, y + .75*side, .7*side, .1*side);
	gfx_fill_rectangle(x + .1*side, y + .85*side, .8*side, .1*side);
}

void drawBishop(int x, int y, char color){
	if (color == 'W'){
		gfx_color(255,255,255);
	}
	else{
		gfx_color(0,0,0);
	}

	gfx_fill_circle(x + .5*side, y + .15*side, .06*side);
	gfx_fill_arc(x+ .35*side, y + .19*side, .3*side, .45*side, 90, 180);
	gfx_fill_arc(x+ .35*side, y + .19*side, .3*side, .45*side, 270, 180);

	XPoint trapezoid[] = { {x + .35*side,y + .6 * side},{x + .65*side,y + .6*side},
	{x + .7*side,y + .7*side},{x + .3*side,y+.7*side},{x + .35*side,y + .6*side} };
	int num = sizeof(trapezoid)/sizeof(XPoint);
	gfx_fill_polygon(trapezoid, num);

	gfx_fill_arc(x+ .3*side, y + .58*side, .4*side, .2*side, 180, 180);
	gfx_fill_rectangle(x + .3*side, y + .78*side, .4*side, .07*side);
	gfx_fill_rectangle(x + .1*side, y + .83*side, .3*side, .05*side);
	gfx_fill_rectangle(x + .6*side, y + .83*side, .3*side, .05*side);

	if (color == 'W'){
		gfx_color(0,0,0);
	}
	else{
		gfx_color(255,255,255);
	}

	gfx_fill_rectangle(x+.48*side, y + .3*side, .04*side, .2*side);
	gfx_fill_rectangle(x+.4*side, y + .38*side, .2*side, .04*side);

}

void drawQueen(int x, int y, char color){
	if (color == 'W'){
		gfx_color(255,255,255);
	}
	else{
		gfx_color(0,0,0);
	}
	gfx_fill_circle(x + .5*side, y + .15*side, .06*side);
	gfx_fill_circle(x + .3*side, y + .17*side, .06*side);
	gfx_fill_circle(x + .1*side, y + .19*side, .06*side);
	gfx_fill_circle(x + .7*side, y + .17*side, .06*side);
	gfx_fill_circle(x + .9*side, y + .19*side, .06*side);

	XPoint triangle1[] = { {x + .5*side,y + .2* side},{x + .45*side,y + .6*side},
	{x + .55*side,y + .6*side},{x + .5*side,y+.2*side} };
	int num1 = sizeof(triangle1)/sizeof(XPoint);
	gfx_fill_polygon(triangle1, num1);

	XPoint triangle2[] = { {x + .3*side,y + .22* side},{x + .35*side,y + .6*side},
	{x + .45*side,y + .6*side},{x + .3*side,y+.22*side} };
	int num2 = sizeof(triangle2)/sizeof(XPoint);
	gfx_fill_polygon(triangle2, num2);

	XPoint triangle3[] = { {x + .1*side,y + .24* side},{x + .25*side,y + .6*side},
	{x + .35*side,y + .6*side},{x + .1*side,y+.24*side} };
	int num3 = sizeof(triangle3)/sizeof(XPoint);
	gfx_fill_polygon(triangle3, num3);

	XPoint triangle4[] = { {x + .7*side,y + .22* side},{x + .55*side,y + .6*side},
	{x + .65*side,y + .6*side},{x + .7*side,y+.22*side} };
	int num4 = sizeof(triangle4)/sizeof(XPoint);
	gfx_fill_polygon(triangle4, num4);

	XPoint triangle5[] = { {x + .9*side,y + .24* side},{x + .65*side,y + .6*side},
	{x + .75*side,y + .6*side},{x + .9*side,y+.24*side} };
	int num5 = sizeof(triangle5)/sizeof(XPoint);
	gfx_fill_polygon(triangle5, num5);

	gfx_fill_arc(x + .25*side, y + .55*side, .5*side, .15*side, 0, 180);

	XPoint trapezoid1[] = { {x + .25*side,y + .6* side},{x + .75*side,y + .6*side},
		{x + .65*side,y + .75*side}, {x + .35*side,y+.75*side}, {x + .25*side,y + .6* side } };
	int num6 = sizeof(trapezoid1)/sizeof(XPoint);
	gfx_fill_polygon(trapezoid1, num6);

	XPoint trapezoid2[] = { {x + .35*side,y + .75* side},{x + .65*side,y + .75*side},
		{x + .8*side,y + .9*side}, {x + .2*side,y+.9*side}, {x + .35*side,y + .75* side } };
	int num7 = sizeof(trapezoid2)/sizeof(XPoint);
	gfx_fill_polygon(trapezoid2, num7);

	//gfx_fill_rectangle(x + .1*side, y + .85*side, .8*side, .1*side); // Not sure if this looks good or bad.
}

void drawKing(int x, int y, char color){
	gfx_color(0,0,0);
	gfx_fill_rectangle(x+.48*side, y + .1*side, .04*side, .2*side);
	gfx_fill_rectangle(x+.4*side, y + .18*side, .2*side, .04*side);

	if (color == 'W'){
		gfx_color(255,255,255);
	}

	gfx_fill_circle(x + .5*side, y + .4*side, .1*side);
	gfx_fill_circle(x + .35*side, y + .57 * side, .17*side);
	gfx_fill_circle(x + .65*side, y + .57 * side, .17*side);

	gfx_fill_rectangle(x + .30*side, y + .5*side, .4*side, .35*side);

	gfx_fill_arc(x + .3*side, y + .73*side, .4*side, .2*side, 180, 180);

}

void drawKnight(int x, int y, char color){
	if (color == 'W'){
		gfx_color(255,255,255);
	}
	else{
		gfx_color(0,0,0);
	}

	gfx_fill_circle(x + .35*side, y + .35*side, .2*side);

	XPoint quad[] = { {x + .35 * side, y + .15 * side},{x + .8*side,y + .05*side},
	{x + .8*side,y + .35*side},{x + .35*side,y+.55*side}, {x + .35 * side, y + .15 * side} };
	int num2 = sizeof(quad)/sizeof(XPoint);
	gfx_fill_polygon(quad, num2);

	XPoint triangle[] = { {x + .25 * side,y + .9 * side},{x + .9*side,y + .9*side},
	{x + .8*side,y + .1*side},{x + .25*side,y+.9*side} };
	int num = sizeof(triangle)/sizeof(XPoint);
	gfx_fill_polygon(triangle, num);


}

void highlightCell(int x, int y){
	gfx_color(85,107,47);
	gfx_fill_rectangle(xOffset + side*x, yOffset + side*y, side, side);
	updatePosition(y, x);
}

void updatePosition(int i, int j){
	char c = board.getSquareValue(i,j);
		switch (c){
			case 'R': drawRook(xOffset + j*side, yOffset + i*side, 'B');
				break;
			case 'N': drawKnight(xOffset + j*side, yOffset + i*side, 'B');
				break;
			case 'B': drawBishop(xOffset + j*side, yOffset + i*side, 'B');
				break;
			case 'Q': drawQueen(xOffset + j*side, yOffset + i*side, 'B');
				break;
			case 'K': drawKing(xOffset + j*side, yOffset + i*side, 'B');
				break;
			case 'P': drawPawn(xOffset + j*side, yOffset + i*side, 'B');
				break;
			case 'r': drawRook(xOffset + j*side, yOffset + i*side, 'W');
				break;
			case 'n': drawKnight(xOffset + j*side, yOffset + i*side, 'W');
				break;
			case 'b': drawBishop(xOffset + j*side, yOffset + i*side, 'W');
				break;
			case 'k': drawKing(xOffset + j*side, yOffset + i*side, 'W');
				break;
			case 'q': drawQueen(xOffset + j*side, yOffset + i*side, 'W');
				break;
			case 'p': drawPawn(xOffset + j*side, yOffset + i*side, 'W');
				break;
			}
}

bool checkRules(int x1, int y1, int x2, int y2, char c1, char c2, char &turn){
	if ((x1 == x2)&&(y1 == y2)){
		// attacking the same position
		turn = switchTurns(turn);
		clearPosition(x1, y1);
		updatePosition(x1, y1);
		return false;
	}
	if ((isupper(c2)&&isupper(c1))||(islower(c2)&&islower(c1))){
		// attacking your own piece
		turn = switchTurns(turn);
		clearPosition(x1, y1);
		updatePosition(x1, y1);
		return false;
	}
	// Check if valid move for piece type
	bool valid = false;
	switch (c1){
		case 'R': valid = checkRook(x1, y1, x2, y2);
			break;
		case 'N': valid = checkKnight(x1, y1, x2, y2);
			break;
		case 'B': valid = checkBishop(x1, y1, x2, y2);
			break;
		case 'Q': valid = checkQueen(x1, y1, x2, y2);
			break;
		case 'K': valid = checkKing(x1, y1, x2, y2);
			break;
		case 'P': valid = checkPawn(x1, y1, x2, y2, c1, c2);
			break;
		case 'r': valid = checkRook(x1, y1, x2, y2);
			break;
		case 'n': valid = checkKnight(x1, y1, x2, y2);
			break;
		case 'b': valid = checkBishop(x1, y1, x2, y2);
			break;
		case 'k': valid = checkKing(x1, y1, x2, y2);
			break;
		case 'q': valid = checkQueen(x1, y1, x2, y2);
			break;
		case 'p': valid = checkPawn(x1, y1, x2, y2, c1, c2);
			break;
		}
	if (!valid){
		// moving to a square that isn't allowed.
		turn = switchTurns(turn);
		clearPosition(x1, y1);
		updatePosition(x1, y1);
		return false;
	}

	return true;
}

char switchTurns(char turn){
	if (turn == 'W'){
		turn = 'B';
	}else{
		turn = 'W';
	}
	return turn;
}

bool checkTurn(char c, char turn){
	if (isupper(c)&&(turn=='B')){
		return true;
	}else if (islower(c)&&(turn=='W')){
		return true;
	}

	return false;
}

void clearPosition(int x, int y){
	if ((x+y)%2){
		gfx_color(130, 82, 1);
	}else{
		gfx_color(182, 155, 76);
	}
	gfx_fill_rectangle(xOffset + x*side,yOffset + y*side, side, side);
}

bool checkRook(int x1, int y1, int x2, int y2){
	if((x1 != x2)&&(y1 != y2)){
		return false;
	}
	bool a = checkCollision(x1,y1,x2,y2);
	return a;
}

bool checkBishop(int x1, int y1, int x2, int y2){
	int test = abs(x2 - x1);
	if (abs(y2 - y1) != test){
		return false;
	}
	bool a = checkCollision(x1,y1,x2,y2);
	return a;
}

bool checkKnight(int x1, int y1, int x2, int y2){
	if ((abs(x2-x1) + abs(y2-y1) == 3)&&(x2!=x1)&&(y2!=y1)){
		return true;
	}
	return false;
}

bool checkKing(int x1, int y1, int x2, int y2){
	if((abs(x2-x1) > 1)||(abs(y2-y1) > 1)){
		return false;
	}
	return true;
}

bool checkQueen(int x1, int y1, int x2, int y2){
	return ((checkBishop(x1,y1,x2,y2)) || (checkRook(x1,y1,x2,y2)));
}

bool checkPawn(int x1, int y1, int x2, int y2, char c1, char c2){
	if( (abs(x2-x1) == 1) && ( (y1-y2) == 1) && (c2 != '#') && (c1 == 'p') ){
		// White Pawn attacking
		return true;
	}else if( (abs(x2-x1) == 1) && ( (y2-y1) == 1) && (c2 != '#') && (c1 == 'P')){
		// Black Pawn attacking
		return true;
	}else if( (x2 == x1) && (y1-y2) == 1 && (c2 == '#') && (c1 == 'p') ){
		// White Pawn moving forward
		return true;
	}else if( (x2 == x1) && (y2-y1) == 1 && (c2 == '#') && (c1 == 'P') ){
		// Black Pawn moving forward
		return true;
	}else if( (x2 == x1) && (y1-y2) == 2 && (c2 == '#') && (c1 == 'p') && (y1 == 6)){
		// White Pawn moving forward for the first time
		return true;
	}else if( (x2 == x1) && (y2-y1) == 2 && (c2 == '#') && (c1 == 'P') && (y1 == 1)){
		// Black Pawn moving forward for the first time
		return true;
	}
	
	return false;
}

bool checkCollision(int x1, int y1, int x2, int y2){

	// check on straight paths
	if ((x1 == x2)||(y1 == y2)){
		if(x1 > x2){ // Left
			for (int i = 1; i < (x1-x2); i++){
				if (board.getSquareValue(y1, x1 - i) != '#'){
					return false;
				}
			}
		}else if(x1 < x2){ //Right
			for (int i = 1; i < (x2-x1); i++){
				if (board.getSquareValue(y1, x1 + i) != '#'){
					return false;
				}
			}
		}else if(y1 > y2){ // Up
			for (int i = 1; i < (y1-y2); i++){
				if (board.getSquareValue(y1 - i, x1) != '#'){
					return false;
				}
			}
		}else if(y1 < y2){ // Down
			for (int i = 1; i < (y2-y1); i++){
				if (board.getSquareValue(y1 + i, x1) != '#'){
					return false;
				}
			}
		}
	}

	// check on diagonals
	if (abs(x2-x1) == abs(y2-y1)){
		if(((x2 - x1) > 0)&&((y2-y1) > 0)){ // Down - right
			for (int i = 1; i < (x2-x1); i++){
				if (board.getSquareValue(y1 + i, x1 + i) != '#'){
					return false;
				}
			}
		}else if(((x2 - x1) > 0)&&((y2-y1) < 0)){ // Up - right
			for (int i = 1; i < (x2-x1); i++){
				if (board.getSquareValue(y1 - i, x1 + i) != '#'){
					return false;
				}
			}
		}else if(((x2 - x1) < 0)&&((y2-y1) > 0)){ // Down - left
			for (int i = 1; i < (x1-x2); i++){
				if (board.getSquareValue(y1 + i, x1 - i) != '#'){
					return false;
				}
			}
		}else if(((x2 - x1) < 0)&&((y2-y1) < 0)){ // Up - left
			for (int i = 1; i < (x1-x2); i++){
				if (board.getSquareValue(y1 - i, x1 - i) != '#'){
					return false;
				}
			}
		}
	}

	// return
	return true;
}

