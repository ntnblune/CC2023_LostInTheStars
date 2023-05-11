#include "LoadWrite.h"

bool loadStateData(Global *global)
{
    ifstream fin("STATE.DAT");
    bool load = false;
    string s;
    if (!is_empty_file(fin))
    {
        while (fin >> s)
        {

        }
        int nextX = -1, nextY = -1;
        while (inputFile >> nextX >> nextY)
        {
            path.push_back(make_pair(nextX, nextY));
        }
        load = true;
    }
    inputFile.close();
    return load;
}

void saveStateData(Global *global)
{
    ofstream fout("STATE.DAT");
    const int type = 3;
    string s[type] = {"HistoryPath", "FolowingMoves", "OtherPlayers"};
    for (int i = 0; i < type; i++)
    {
        fout << s[i] << endl;
        if (s[i] == "HistoryPath")
        {
            for (int j = 0; j < global->T + 1; j++)
            {
                fout << global->playerHistory[j].currentX << ' ' << global->playerHistory[j].currentY << endl;
            }
        }
        else if (s[i] == "FolowingMoves")
        {
            fout << global->nextMoves.size() << endl;
            for (int j = 0; j < global->nextMoves.size(); j++)
            {
                fout << global->nextMoves[j].currentX << ' ' << global->nextMoves[j].currentY << endl;
            }
        }
        else if (s[i] == "OtherPlayers")
        {
            for (int j = 0; j < 3; j++)
            {
                fout << j << ' ' << global->otherPlayer[j].color << endl;
                for (int h = 0; h < global->T + 1; h++)
                {
                    fout << global->otherPlayer[j].currentX << ' ' << global->otherPlayer[j].currentY << endl;
                }
            }
        }
    }
}