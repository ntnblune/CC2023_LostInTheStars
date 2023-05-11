#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include"InputOutput.h"

pair<int, int> solve(Global *global);
bool areOnlySurvivor(Global *global);
bool genPath(Global *global, pair<int,int> next_move);
vector<vector<int>> findDistant(Global *global, int currentX, int currentY);
pair<int, int> buildNewPath(Global *global, vector<pair<int, int>> &path);
bool checkSurvive(Global *global, int x, int y, pair<int,int> &next_move);


#endif // ALGORITHM_H_INCLUDED
