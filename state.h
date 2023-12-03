/*
BY ARNOLD QUIOCHO STUDENT20732073
*/

#ifndef STATE_H
#define STATE_H

#include "include.h"
#include "struct.h"
#include <ctime>
#include <queue>
#include <random>

class State {
private:
  int size = 3;
  int blockCount = 6;
  vector<list<int>> stateArray;
  vector<goalState> goalArray;

public:
  int getSize();
  vector<list<int>> getStateArray();

  int gameMode;
  void chooseSize();
  void generateState();
  void printState();
  void printState2();

  void Action(int, int);
  bool isLegal(int);
  void getPlayerAction();

  bool checkGameState();
  bool atomGoalState(int, int, int);
  void setMultiGoal();
  bool checkDisjunctiveGoal();
  bool checkConjunctiveGoal();
};

int State::getSize() { return size; }

vector<list<int>> State::getStateArray() { return stateArray; }

void State::chooseSize() {
  cout << "Size must be over 2 blocks.\nInput size: ";
  cin >> size;
  while (size < 3) {
    cout << "Size must be over 2 blocks.\nInput size: ";
    cin >> size;
  }
  cout << "Block count must be more than size, and less than size^2.\nInput "
          "block count: ";
  cin >> blockCount;
  while (blockCount < size || (size * size) < blockCount) {
    cout << "Block count must be more than size, and less than size^2.\nInput "
            "block count: ";
    cin >> blockCount;
  }
}

void State::generateState() {
  vector<int> validBlocks;

  for (int i = 1; i != blockCount + 1; i++) // create the list of valid blocks
  {
    validBlocks.push_back(i);
  }

  for (int i = 0; i < size; i++) // push back lists into the vector array
  {
    list<int> list;
    stateArray.push_back(list);
  }

  for (int i = 0; i < blockCount; i++) // randomise block locations
  {
    int randNum = rand() % validBlocks.size();
    int column;
    do {
      column = rand() % size;
      // cout << endl << "RAN ONCE";
    } while (stateArray[column].size() == size);

    stateArray[column].push_front(validBlocks[randNum]);
    // cout << endl << "PUSHED BACK VALUE " << validBlocks[randNum] << " INTO
    // COLUMN " << column;
    validBlocks.erase(validBlocks.begin() + randNum);
  }
}

void State::Action(int move, int to) {
  int tempMove = 0;
  if (isLegal(to)) {
    tempMove = stateArray[move].front();
    stateArray[move].pop_front();
    stateArray[to].push_front(tempMove);
  } else
    cout << "\nMove is illegal.";
}

bool State::isLegal(int pos) {
  if (stateArray[pos].size() < size)
    return true;
  else
    return false;
}

void State::getPlayerAction() {
  int move, to;
  cout << "\nInputs must be less than the size or more than 0.\nInput a blocks "
          "column, then the column to move into.";
  cin >> move >> to;
  Action(move, to);
}

bool State::atomGoalState(int target, int col, int row) {
  vector<list<int>> copyArray = stateArray;
  for (int i = size; i != row + 1; i--) {
    if (copyArray[col].size() == i) {
      copyArray[col].pop_front();
    }
  }
  if (copyArray[col].front() == target)
    return true;
  else
    return false;
}

void State::printState() {
  vector<list<int>> copyArray = stateArray;
  int currentColumn = size;
  for (int i = 0; i < size; i++) {
    cout << "\n|" << setw(3);
    for (int j = 0; j < size; j++) {
      if (copyArray[j].size() < currentColumn)
        cout << 0;
      else if (copyArray[j].size() == currentColumn) {
        cout << copyArray[j].front();
        copyArray[j].pop_front();
      }
      cout << "|" << setw(3);
    }
    currentColumn--;
  }
}

void State::printState2() {
  vector<list<int>> copyArray = stateArray;

  for (int i = 0; i < size; i++) {
    cout << endl;
    int arraySize = copyArray[i].size();
    for (int j = arraySize; j > 0; j--) {
      cout << copyArray[i].front();
      copyArray[i].pop_front();
      cout << "|";
    }
  }
}

bool State::checkGameState() {
  if (gameMode == 1) {
    return checkDisjunctiveGoal();
  }
  if (gameMode == 2) {
    return checkConjunctiveGoal();
  } else
    return false;
}

void State::setMultiGoal() {
  goalState goal;
  int finLoop = 1;
  while (finLoop == 1) {
    cout << "\nChoose the goal in the order of target block, column, "
            "row.\nTarget Block: ";
    cin >> goal.block;
    cout << "\nColumn: ";
    cin >> goal.column;
    cout << "\nRow: ";
    cin >> goal.row;
    goalArray.push_back(goal);
    cout << "\nWould you like to add another goal?\n1.Yes \n2.No\n\n";
    cin >> finLoop;
  }
  cout << "\nIs this goal an atom goal, disjunctive or "
          "conjunctive?\n1.Disjunctive Goal (or Atom Goal)\n2.Conjunctive "
          "Goal\n\n";
  cin >> gameMode;
}

bool State::checkDisjunctiveGoal() {
  for (int i = 0; i < goalArray.size(); i++) {
    if (atomGoalState(goalArray[i].block, goalArray[i].column,
                      goalArray[i].row))
      return true;
  }
  return false;
}

bool State::checkConjunctiveGoal() {
  int currentGoals = 0;
  for (int i = 0; i < goalArray.size(); i++) {
    if (atomGoalState(goalArray[i].block, goalArray[i].column,
                      goalArray[i].row))
      currentGoals++;
  }
  if (currentGoals == goalArray.size())
    return true;
  else
    return false;
}

#endif /*STATE_H*/