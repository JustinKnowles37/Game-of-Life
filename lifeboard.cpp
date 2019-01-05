#include <iostream>
#include <vector>
using namespace std;

#include "lifeboard.h"

LifeBoard::LifeBoard() {
  for (int i = 0; i < size; i++) {
    vector<bool> row;
    for (int j = 0; j < size; j++) {
      row.push_back(false);
    }
  board.push_back(row);
  }
}

LifeBoard::~LifeBoard()
{}


// Get and set methods for the board itself

vector<vector<bool>> LifeBoard::getBoard() {
  return board;
}

void LifeBoard::setBoard(vector<vector<bool>> newBoard) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      board[i][j] = newBoard[i][j];
    }
  }
}

// Set cell status

void LifeBoard::setAlive(Cell c) {
  board[c.x][c.y] = true;
}

void LifeBoard::setDead(Cell c) {
  board[c.x][c.y] = false;
}

int LifeBoard::countLiveNeighbors(Cell c) {
  int numLiveNeighbors = 0;

  // We need to check if the neighbors around the desired cell are alive. To do
  // this, we will add the values of these surrounding cel
  // We also need to account for edge cells, which is done in the outer if
  // statements below.

  if (c.x != 0 && c.y != 0)
    if (board[c.x-1][c.y-1]) numLiveNeighbors++;

  if (c.x != 0)
    if(board[c.x-1][c.y]) numLiveNeighbors++;

  if (c.x != 0 && c.y != size - 1)
    if(board[c.x-1][c.y+1]) numLiveNeighbors++;

  if(c.y != size - 1)
    if(board[c.x][c.y+1]) numLiveNeighbors++;

  if (c.x != size - 1 && c.y != size - 1)
    if(board[c.x+1][c.y+1]) numLiveNeighbors++;

  if (c.x != size - 1)
    if(board[c.x+1][c.y]) numLiveNeighbors++;

  if (c.x != size - 1 && c.y != 0)
    if(board[c.x+1][c.y-1]) numLiveNeighbors++;

  if (c.y != 0)
    if(board[c.x][c.y-1]) numLiveNeighbors++;

  return numLiveNeighbors;
}

LifeBoard LifeBoard::update(vector<vector<int>> numLiveNeighbors) {
  // Create temporary board to store future board state
  LifeBoard tempBoard;
  tempBoard.board = board;

  Cell c; // Cell to be used throughout method

  // If statement to determine the changes on the board
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {

      c.x = i;
      c.y = j;

      // If statement to do different actions for alive and dead cells

      if (board[i][j]) {
        if (numLiveNeighbors[i][j] < 2 || numLiveNeighbors[i][j] > 3) {
          tempBoard.setDead(c);
        }
      } else {
	if (numLiveNeighbors[i][j] == 3) {
          tempBoard.setAlive(c);
        }
      }
    }
  }
  // Now that temporary board has been set, return temporary board
  return tempBoard;

}

ostream& operator<<(ostream& os, LifeBoard& LB) {
  // Display top part of border
  os << '+';
  for (int k = 0; k < size; k++) cout << '-';
  os << '+';
  os << endl;

  // Display side borders and board
  for (int i = 0; i < size; i++) {
    os << '|'; // Create left side of border
    for (int j = 0; j < size; j++) {
      if (LB.board[i][j]) {
        os << 'X';
      } else {
	      os << ' ';
      }
    }
    os << '|' << endl; // Create right side of border
  }

  // Display bottom part of border
  os << '+';
  for (int l = 0; l < size; l++) os << '-';
  os << '+';
  os << endl;

  return os;
}
