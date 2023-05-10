#ifndef INPUTOUTPUT_H_INCLUDED
#define INPUTOUTPUT_H_INCLUDED

#include"Global.h"

void input(Global *global);
void output(const pair<int, int> &nextPositions);
bool is_empty_file(std::ifstream& pFile);

#endif // INPUTOUTPUT_H_INCLUDED
