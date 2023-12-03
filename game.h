/*
BY ARNOLD QUIOCHO STUDENT20732073
*/

#ifndef GAME_H
#define GAME_H

#include "state.h"
#include "solver.h"
#include "monteCarlo.h"

class Game
{
  private:
  State s;
  Solver solver;
  MonteCarloSolver mcs;
  int loc, des;

  public:
  void Driver();
  void playerGame();
};

void Game::Driver()
{
  srand(time(NULL));
  s.chooseSize();
  s.generateState();
  s.printState();
  
  int chooseMode = -1;
  cout << "\n\nChoose method.\n1.Player input\n2.Tree Search (No Heuristics)\n3.Tree Search w/ Heuristics\n\n";
  cin >> chooseMode;
  
  s.setMultiGoal();
  
  if(chooseMode == 1)
  {
    playerGame();
    cout << "\nGOAL REACHED!";
    s.printState();
  }
  else if (chooseMode== 2)
  {
    for(int i = 0; (i < 1000) ^ (s.checkGameState()); i++)
      {
        solver.getSolverMove(s, loc, des);
        s.Action(loc, des);
        s.printState();
      }
    if(!s.checkGameState())
      cout << "\nMove limit reached. Failed to complete";
    else
      cout << "\nFinished!";
    s.printState();
  }
    
  else if (chooseMode == 3)
  {
    for(int i = 0; (i < 1000) ^ (s.checkGameState()); i++)
      {
        mcs.getMove(s,loc,des);
        s.Action(loc, des);
        cout << "\nTurn " << i << ": Move " << loc << " to " << des;
        s.printState();
      }
    if(!s.checkGameState())
      cout << "\nMove limit reached. Failed to complete";
    else
      cout << "\nFinished!";
    s.printState();
  }
}

void Game::playerGame()
{
  while(!s.checkGameState())
    {
      s.printState();
      s.getPlayerAction();
    } 
}


#endif /*!GAME_H*/