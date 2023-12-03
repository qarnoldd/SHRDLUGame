/*
BY ARNOLD QUIOCHO STUDENT20732073
*/

#ifndef SOLVER_H
#define SOLVER_H

#include "state.h"

class Solver 
{
  private:
  int numMoves = 0;
  public:
  void getSolverMove(State, int&, int&);
};

void Solver::getSolverMove(State s, int &loc, int &des)
{
  int tempLoc, tempDes;
  tempLoc = loc;
  tempDes = des;
  
  do {
    loc = rand() % s.getSize();
  } while (tempLoc == loc || s.getStateArray()[loc].size() == 0);
  do {
    des = rand() % s.getSize();
  } while (tempDes == des || s.getStateArray()[des].size() == s.getSize() || des == loc);
  numMoves++;
  cout << "\nMove " << numMoves << ": " << loc << " to " << des << endl;
}

#endif /*SOLVER_H*/