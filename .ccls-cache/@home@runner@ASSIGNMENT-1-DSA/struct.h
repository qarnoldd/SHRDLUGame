/*
BY ARNOLD QUIOCHO STUDENT20732073
*/

#ifndef STRUCT_H_
#define STRUCT_H_

struct moveStruct {
  double priority;
  int block;
  int position;
  int destination;

  bool operator<(const moveStruct& p)const {
    return priority < p.priority;
  }
};

struct goalState {
  int block;
  int column;
  int row;
};

#endif /*STRUCT_H_*/