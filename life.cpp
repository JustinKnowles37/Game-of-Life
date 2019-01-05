#include <iostream>
using namespace std;

#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <string>

#include "lifeboard.h"

char getCommand(void);
void a(LifeBoard&);
void r(LifeBoard&);
LifeBoard n(LifeBoard);
void p(LifeBoard&);

int main(int argc, char *argv[]) {
  system("clear"); // Clears screen
  LifeBoard myBoard; // Create initial blank board

  // If statement to determine if interactive or batch mode
  if (argc == 1) { // interactive mode

    // Display initial blank board
    cout << myBoard;

    // Initialize user command variable
    char userCommand = 'a';

    // While loop to play until user quits
    while (userCommand != 'q') {

      // Get user command
      userCommand = getCommand();

      // If statement for each possible user command
      if (userCommand == 'a') {

        a(myBoard); // add a new live cell

      } else if (userCommand == 'r') {

        r(myBoard); // remove a cell

      } else if (userCommand == 'n') {

        myBoard = n(myBoard); // advance simulation to next stage
        system("clear"); // Clears screen
        cout << myBoard;

      } else if (userCommand == 'q') {
      
        // No separate function here because of simplicity
        cout << "Thank you for playing! Goodbye!" << endl;
        break;

      } else if (userCommand == 'p') {

        p(myBoard); // play game continuously

      } else {

        cout << "Error! Invalid command! Enter a, r, n, q, or p." << endl;

      }
    }

  } else if (argc == 2) { // batch mode

    // Input data from file
    string s;
    Cell c;
    string fileName = argv[1];
    ifstream ifs;
    ifs.open(fileName);

    // Ensure that file is valid
    if (!ifs) {
      cout << "Error! Invalid file!" << endl;
      return 2;
    }

    getline(ifs, s, ' ');

    // While loop unitl it reaches p, which symbolizes end of file
    while (!ifs.eof()) {
      getline(ifs, s, ' ');
      c.x = stoi(s);
      getline(ifs, s);
      c.y = stoi(s);
      myBoard.setAlive(c);
      getline(ifs, s, ' ');
    }

    cout << myBoard << endl;

    // Now, ready to play game continuously
    p(myBoard); // play game continuously

  } else { // user entered too many arguments

    cout << "Error. Too many arguments." << endl;

    return 1;
  }

  return 0;
}

char getCommand(void) {
  char command;
  cout << "Enter your desired command: ";
  cin >> command;
  return command;
}

void a(LifeBoard& myBoard) {
  Cell c; // Cell type defined in .h file
  cout << "Enter the x and y coordinates of the new cell to add: ";
  cin >> c.x >> c.y;

  // Ensure valid input
  while (c.x < 0 || c.x >= size || c.y < 0 || c.y >= size) {
    cout << "Error! Please enter valid cell coordinates" << endl;
    cout << "Enter the x and y coordinates of the new cell to add: ";
    cin >> c.x >> c.y;
  }

  myBoard.setAlive(c);
  system("clear"); // Clears screen
  cout << myBoard;
}

void r(LifeBoard& myBoard) {
  Cell c; // Cell type defined in .h file
  cout << "Enter the x and y coordinates of the cell to remove: ";
  cin >> c.x >> c.y;

  // Ensure valid input
  while (c.x < 0 || c.x >= size || c.y < 0 || c.y >= size) {
    cout << "Error! Please enter valid cell coordinates" << endl;
    cout << "Enter the x and y coordinates of the new cell to add: ";
    cin >> c.x >> c.y;
  }

  myBoard.setDead(c);
  system("clear"); // Clears screen
  cout << myBoard;
}

LifeBoard n(LifeBoard myBoard) {
  // Count number of neighbors that each cell has
  vector<vector<int>> numLiveNeighbors; // Stores number of live neighbors
  Cell c; // Cell to be used throughout function
  int currentNeighbors = 0; // Number of neighbors for current cell
  for (int i = 0; i < size; i++) {
    vector<int> liveNeighborsRow; // Vector for each row
    for (int j = 0; j < size; j++) {
      c.x = i;
      c.y = j;
      currentNeighbors = myBoard.countLiveNeighbors(c);
      liveNeighborsRow.push_back(currentNeighbors);
    }
    cout << endl;
    numLiveNeighbors.push_back(liveNeighborsRow);
  }

  // Now, we need to update the board
  myBoard = myBoard.update(numLiveNeighbors);

  return myBoard;
}

void p(LifeBoard& myBoard) {
  // To play game continuously, need infinite loop
  while(true) {
    myBoard = n(myBoard);
    system("clear"); // Clears screen
    cout << myBoard;
    usleep(400000); // Pauses for short time
  }
}
