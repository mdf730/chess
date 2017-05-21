Matthew Fabian
Final Project Report

From a user perspective:

The program runs by typing 'make' into the command line, followed by 'go.' This 
launches a new window labeled "Chess." On the screen appears an 8x8 grid of 
alternating colored cells, and a moment later 32 of the squares are covered by a 
chess piece.  The pieces are in the expected positions for a game of chess, with 
white on the bottom and black on the top. The user can then play a basic game of 
chess with another user at the same computer. 

White moves first. To move a piece, the user clicks first on the piece that they want 
to move. If it is their turn and they click on their own piece, the cell it is on 
will be highlighted with an olive green color. From there, the user can click on any 
cell on the board. If the user clicks on a cell that is valid to move to, the piece 
will disappear from where it was and reappear at the new cell. If it is taking the 
place of an opponent's piece, that piece will disappear from the board. If the user 
clicks on a cell that isn't valid (such as the same cell again, one of their own 
pieces, or a cell that the particular piece cannot move to), it will deselect the 
piece. The color of the cell will return to normal, and the same user will be able to 
attempt to move any of their pieces again. They will not relinquish their turn until 
they succesfully move a piece.

The game of chess ends with checkmate, draw, stalemate, or resignation. When one of 
these conditions is met, either use can exit the program by pressing 'q.' This can be 
done at any time.

The standard rules of chess are followed, with the following exceptions:
1. En Passant capture does not exist.
2. Castling does not exist.
3. Pawns that reach the opposite side of the board are 
	promoted exclusively to queens. 

Touch move rule is in effect; there is no such thing as undo. The player is 
responsible for declaring check and checkmate. There is no built in clock, but users 
could play with an external clock if desired.

From a programmer perspective:

The program has a main function that includes the game while loop and 23 supporting 
functions. A quick note - I chose to use a few global variables because we were told 
via piazza that global variables would be ok for the final, and it saved me from 
having to pass an extra few variables to every function. With so many functions, this 
saved both programming time and perserved better readability within the program.

In the main function, several variables are initialized and declared. A graphics 
window is opened using gfx_open(), and 2 functions are called to initialize the 
board: drawboard() and newboard(). The output is then flushed to the screen using 
gfx_flush(). Next, a while loop is entered that loops until the user chooses to quit 
and the 'quit' boolean is triggered. The while loop encapsulates a single if 
statement that is true when gfx_event_waiting() detects any input. If that is the 
case, gfx_wait() is called and if statements are used to determine if the left mouse 
button was clicked, or if some other event occured. If the mouse button occured and 
the clickedOnce flag has not been triggered, the cell value that was clicked on is 
recorded using gfx_xpos() and gfx_ypos(). The program determines what piece is in 
the cell that was selected, and if the piece you selected is your own piece, it 
colors the cell an olive green. The clickedOnce boolean is set to true. When another 
click is registered, it will lead the program to the else statement (line 82) and 
determine the cell coordinates in a similar manner as was previously described. Now, 
the program determines if it is valid to move the piece from the original cell to 
the new cell and moves it if legal. The turn then passes to the other player, and 
all updates are flushed to the screen. clickedOnce is set back to false to reset the 
cycle.

What is described above is accomplished through the help of several functions. 

The first function is drawBoard(). It is a void function that uses the gfx library to 
draw the 8x8 checkerboard in the graphics window. This is accomplished by a nested 
for loop encapsulating an if/else statement that alternates colors based on if the 
sum of the rows and columns are even or odd.

Next is newBoard(). This function calls the .setNewGame() method of the Chessboard 
Class. This updates a private array that uses ASCII characters to keep track of where 
each piece is on the board. the .setNewGame() method initializes the pieces to the 
default setup. The commented out code in this section shows the process that would 
have been necesarry without the class implementation. It clearly saves both 
programming time and delay while running the program.

Within newBoard(), updateBoard() is called. This is a simple helper function that 
uses a nested for loop to call the function updatePosition() for every cell on the 
board.

updatePosition is another void function. It takes as its arguments two integers that 
represent the x and y indeces of the Chessboard. The function uses the 
.getSquareValue() method to determine what piece is on that particular cell, then 
uses a switch statement to call the relevant draw...() function. This places the 
proper piece of the proper color on the graphical chessboard.

There are six draw...() functions. Each of these functions uses various members of 
the gfx library to draw the described piece. Every function is a void function with 
no return, but takes as its arguments integers x and y (located at the top left 
corner of the cell in which to draw the piece) and the char color (what color to use 
to draw the piece). An if/else statement is used in each case to select the color, 
and then various gfx functions are called to make a recognizable image. Featured 
functions include gfx_fill_circle(), gfx_fill_polygon(), gfx_fill_rectangle(), and 
gfx_fill_arc(). These functions required several iterations of trial and error in 
order to make the pieces look presentable.

Next is one of the key functions: movePiece(). This is a void function that takes as 
input the x/y coordinates of the piece currently, the x/y coordinates of the cell to 
move to, and the turn value, passed by reference. Within the function, the piece at 
each relevant cell is determined using the .getSquareValue() method described 
earlier. Next the rules function is called, which will be explained later. If the 
rules function returns true, the old square is cleared, the new square is cleared, 
and the original piece is placed in the new square. Exceptions exist if the original 
piece was a pawn and it is advancing to the back rank, in which case it becomes a 
queen instead of a pawn.

A function mentioned brielfy earlier is the highlightCell() function. This void 
function takes as input the x/y coordinates of a specific cell. It colors that cell 
an olive green, then calls updatePosition() for that cell only in order to redraw the 
piece in the cell.

The checkRules() function accomplishes a few connected points. The function returns a 
boolean value from the arguments of original x/y coordinates, new x/y coordinates, 
the piece in each of the aforementioned cells, and the turn value passed by reference.
The first two if statements if the function state that if the new cell is either the 
same as the old cell, or the cell of one of the user's own pieces, that move is not 
allowed. Turns is switched in order to ensure the player does not lose their turn, 
the highlighted cell is cleared, and we exit back to the main while loop. If both of 
the initial conditions pass, we enter a switch statement that selects from among 
several relevant check...() functions. If the relevant check...() statement returns 
true, the rules function returns true and the move is made as the user indicated.

Each of the six check...() functions determines if a piece is allowed to move where 
it is attempting to move according to the rules of chess. The boolean functions are 
passed the x/y coordinates of both the old and new cell. (Note the pawn is also 
passed the actual values of the cell including color in order to ensure it moves in 
the proper direction.) The functions establish basic movement rules, such as that 
rooks can only move horizontally or vertically, and then a helper function is called: 
checkCollision. The pieces that need to check for collisions are bishops, rooks, and 
queens. Knight jump pieces so collisions aren't a concern, while pawns and kings only 
move one cell at a time so collisions are impossible. The checkPawn function has a 
special else/if string because of its unique forward movement coupled with diagonal 
attacking. 

The checkCollision() function returns a boolean and takes as its arguments the x/y 
coordiantes of the old cell and the new cell. It uses a several if statements to 
determine which cardinal direction the piece is attempting to move in, and then 
determine if there are any obstacles along the path that it will travel. If there are 
obstacles along the path (traveled in the program using a for loop), the function 
returns false. If there are no obstacles, the function returns true.

A few more miscellaneous functions... checkTurn() is a boolean function that returns 
true if the color entere matches the color of the player who currently has the turn, 
while clearPosition() is a void function that essentially erases a piece from a specific 
cell by coloring it back to its original rectangle. switchTurns returns a char that is 
the opposite of the current player's turn, allowing the turn to switch back and forth 
between 'W' and 'B.'

Evaluating program correctness:

As far as I described and as best I am aware, the program works properly. I built 
small portions of the program at a time and tested each possible edge case and 
several points of possible failure. For example, the original movePiece function 
could be used to move any piece to any cell. This resulted in overlap of pieces, 
illegal moves, and several more issues. The most pressing issue and first to address 
was that clicking on a piece and then a different cell occasionally resulted in 
different pieces being moved, or moved correct pieces to incorrect squares. This 
problem was solved (an issue with the offset). Then a function was written to prevent 
pieces from overlapping. Next several functions were created under the 'rules' 
function that checked whether a piece was making a valid move for its type. And so on 
and so forth, until each piece was moving exactly as it should. 

A similar process was used for the less innovative and more tedious task of drawing 
each of the pieces. Each piece has a separate function that the gfx_library to build 
a 2D image of the piece using circles, arcs, rectangles, and polygons. These 
functions were built on trial and error, with more trial and less error as the 
process went on. 

Currently there are no cases where the program gives innacurate results, but there 
are several areas for improvement as I continue to work with it in the future.  Most 
importantly, I want to get the program working with all rules of chess. In order of 
priority, this includes rules for castling, non-queen pawn promotion, and en passant 
capture. I would also like to implement an checkForCheck() function similar to the 
earlier extra credit which forces the user to take a legal action if they are in 
check. Included in this would be adding a small red circle around a king when it is 
check, and possibly a larger red square when the king is checkmated.

Once these goals are met, future plans include:
 - displaying small olive circles on cells that are valid to move to when a user 
 	clicks a piece once.
 - displaying on the side of the board all pieces that have been captured so far.
 - options to restart and to undo
 - a chess clock
 - improving the graphics for the pieces (especially the knight)
 - implementing click and drag functionality
 - create a txt file with the history of the game in chess notation.
 - be able to read in a txt file with chess notation and initialize a board based on
  	where the game currently is.

  	
