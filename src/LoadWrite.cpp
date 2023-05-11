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
            global->me.currentX = global->me.currentY = -1;
            if (s == "HistoryPath")
            {
                for (int j = 0; j < global->T; j++)
                {
                    Player k;
                    fin >> k.currentX >> k.currentY;
                }
            }
            else if (s == "FolowingMoves")
            {
                int t;
                fin >> t;
                for (int j = 0; j < t; j++)
                {
                    Player k;
                    fin >> k.currentX >> k.currentY;
                    global->nextMoves.push_back(k);
                }
            }
            else if (s == "OtherPlayers")
            {
                for (int j = 0; j < 3; j++)
                {
                    int index;
                    char c;
                    fin >> index >> c;
                    for (int i = 0; i < global->T; i++)
                    {
                        Player k;
                        fin >> k.currentX >> k.currentY;
                        k.color = c;
                        global->otherPlayers[j].push_back(k);
                    }
                }
            }
        }
        load = true;
    }
    fin.close();
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
            global->playerHistory.push_back(global->me);
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
                fout << j << ' ' << global->otherPlayers[j][0].color << endl;
                for (int h = 0; h < global->T + 1; h++)
                {
                    fout << global->otherPlayers[j][h].currentX << ' ' << global->otherPlayers[j][h].currentY << endl;
                }
            }
        }
    }
}