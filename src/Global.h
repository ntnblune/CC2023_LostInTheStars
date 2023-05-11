#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include<bits/stdc++.h>
using namespace std;
struct Player
{
    int currentX, currentY;
    char color;
};
class Global
{
public:
    const int inf = 1e6;
    int M, N, K, T,P;
    Player me;
    const short directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<vector<char>> board;
    vector<Player> otherPlayers[3], playerHistory, nextMoves;  // luot, xy_coord
};

bool is_empty_file(std::ifstream& pFile);

#endif // GLOBAL_H_INCLUDED
