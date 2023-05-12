#include"InputOutput.h"
#include"LoadWrite.h"

using namespace std;

void input(Global *global) {
    ifstream inputFile("MAP.INP");
    inputFile >> global->M >> global->N >> global->K >> global->T >> global->me.currentX >> global->me.currentY >> global->me.color >> global->P;
    loadStateData(global);
    for (int i = 0; i < global->P; ++i)
        {
            int X,Y;
            char C;
            inputFile >> X >> Y >> C;
            bool check = true;
            for (int j = 0; j < global->color.size(); j++)
            {
                if (global->color[j] == C)
                {
                    check = false;
                    break;
                }
            }
            if (check)
            {
                global->color.push_back(C);
            }
            Player k;
            k.currentX = X;
            k.currentY = Y;
            k.color = C;
            global->otherPlayers[C - 'A'].push_back(k);
        }

    global->board.resize(global->M, vector<char>(global->N, '.'));

    for (int x = 0, y; x < global->M; ++x)
        for (y = 0; y < global->N; ++y){
            inputFile >> global->board[x][y];
        }
    inputFile.close();
}
void output(const pair<int, int> &nextPositions) {
    ofstream outputFile("MOVE.OUT");
    outputFile << nextPositions.first << ' ' << nextPositions.second << '\n';
    outputFile.close();
}
