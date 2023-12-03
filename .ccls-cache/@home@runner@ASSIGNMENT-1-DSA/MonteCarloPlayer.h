#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_
#include "include.h"
#include "state.h"
#include "struct.h"
#include <queue>
class MonteCarloPlayer {
  queue<possibleMove> moveQueue;
  int simulationTimes = 1000;

public:
  void possibleMoves(vector<list<int>>, State, int&, int&);
  double simulation(State);
  double expansion(State);
};

void MonteCarloPlayer::possibleMoves(vector<list<int>> stateArray, State mainState, int &location, int &destination) {
  State s = mainState;
  int size = s.getSize();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (stateArray[j].size() < size && j != i) {
        possibleMove move;
        move.block = stateArray[i].front();
        move.position = i;
        move.destination = j;
        move.priority = simulation(s);
        moveQueue.push(move);
      }
    }
    if(!moveQueue.empty())
      location = moveQueue.front().position;
      destination = moveQueue.front().destination;
  }
}

double MonteCarloPlayer::simulation(State s) {
  double success = 0.0;
  for (int i = 0; i < simulationTimes; i++) {
    State tempState = s;
    success += expansion(s);
  }
  return success / simulationTimes;
}

double MonteCarloPlayer::expansion(State s) {
  if (s.checkGameState())
    return 1.0;
  else
    return 0.0;

  int move, to;
  while(s.getStateArray()[move].size() == s.getSize())
    move = rand() % 2;
  while(move == to)
    move = rand() % 2;
  s.Action(move,to);
  return expansion(s);
}

#endif /*MONTECARLOPLAYER_H_*/