const int size = 40; // Size of the board (not including border)

// Struct to make it easier to pass coordinates
struct Cell {
  int x;
  int y;
};

class LifeBoard {
  friend ostream& operator<<(ostream&, LifeBoard&);
public:
  LifeBoard();
  ~LifeBoard();

  // Get and set methods for the board itself
  vector<vector<bool>> getBoard();
  void setBoard(vector<vector<bool>>);

  // Set cell status
  void setAlive(Cell);
  void setDead(Cell);

  // Utility methods
  int countLiveNeighbors(Cell);
  LifeBoard update(vector<vector<int>>);

private:
  vector<vector<bool>> board;
};
