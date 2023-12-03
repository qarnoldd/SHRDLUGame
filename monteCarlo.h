/*
BY ARNOLD QUIOCHO STUDENT20732073
*/

#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H
#include "state.h"

class MonteCarloSolver {
  int simulationTimes = 100;

public:
  void getMove(State, int &, int &);
  double simulation(State, int, int);
  double expansion(State, int, int, int);
  void possibleMoves(State);
};

void MonteCarloSolver::getMove(State s, int &loc, int &des) {
  priority_queue<moveStruct> moves;

  int temploc = loc, tempdes = des;

  int size = s.getSize();
  vector<list<int>> stateArray = s.getStateArray();

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (stateArray[j].size() == size || j == i)
        continue;

      State tempState = s;
      tempState.Action(i, j);
      if (tempState.checkGameState()) {
        loc = i;
        des = j;
        return;
      }

      moveStruct move;
      move.block = stateArray[i].front();
      move.position = i;
      move.destination = j;
      move.priority = simulation(tempState, i, j);
      moves.push(move);
      // cout << "\nPush move: BLOCK " << move.block << " AT POSITION " <<
      // move.position << " TO DESTINATION " << move.destination;

      if (!moves.empty()) {
        loc = moves.top().position;
        des = moves.top().destination;
      }
    }
  }
}

double MonteCarloSolver::simulation(State s, int pos, int des) {
  double success = 0.0;
  for (int i = 0; i < simulationTimes; i++) {
    State tempState = s;
    success += expansion(tempState, pos, des, 100);
  }
  cout << "\nSUCCESS: " << success << " SIM: " << simulationTimes;
  return success;
}

double MonteCarloSolver::expansion(State s, int loc, int des, int expand) {
  if (s.checkGameState())
    return 1.0;
  else if (expand == 0)
    return 0.0;
  else {
    int tempLoc, tempDes;
    tempLoc = loc;
    tempDes = des;
    do {
      loc = rand() % s.getSize();
    } while (tempLoc == loc || s.getStateArray()[loc].size() == 0);
    do {
      des = rand() % s.getSize();
    } while (tempDes == des || s.getStateArray()[des].size() == s.getSize() ||
             des == loc);
    s.Action(loc, des);
    expand--;
    return expansion(s, loc, des, expand);
  }
}

/*
void MonteCarloSolver::possibleMoves(State s)
{
  for(int i = 0; i < moveQueue.size(); i++)
    moveQueue.pop();

  int size = s.getSize();
  vector<list<int>> stateArray = s.getStateArray();

  for(int i = 0; i < size; i++)
    {
      for(int j = 0; j < size; j++)
        {
          if(stateArray[j].size() < size && j != i)
          {
            moveStruct move;
            move.block = stateArray[i].front();
            move.position = i;
            move.destination = j;
            moveQueue.push(move);
          }
        }
    }
}
*/
#endif /*!MONTE_CARLO_H*/