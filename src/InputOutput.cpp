#include"InputOutput.h"

using namespace std;
bool is_empty_file(std::ifstream& pFile)
{
    if (!pFile) return true;
    return pFile.peek() == std::ifstream::traits_type::eof();
}
void input(Global *global) {
    ifstream inputFile("MAP.INP");

    inputFile >> global->M >> global->N >> global->K >> global->T >> global->me.currentX >> global->me.currentY >> global->me.color >> global->P;
    for (int i = 0; i < global->P; ++i)
        {
            int X,Y;
            char C;
            inputFile >> X >> Y >>C;
            global->otherPlayers.push_back({X,Y,C});
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
