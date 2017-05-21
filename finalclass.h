// Matthew Fabian
// final project
// finalclass.h

class Chessboard {
  public:
    Chessboard();
    ~Chessboard();
    char getSquareValue(int, int);
    void setSquareValue(int, int, char);
    void setNewGame();
  private:
    char board[8][8];
};