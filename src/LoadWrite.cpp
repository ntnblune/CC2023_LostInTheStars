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
            if (s == "HistoryPath")
            {
                for (int j = 0; j < global->T; j++)
                {
                    Player k;
                    fin >> k.currentX >> k.currentY;
                    global->playerHistory.push_back(k);
                }
                global->playerHistory.push_back(global->me);
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
                int num;
                fin >> num;
                for (int j = 0; j < num; j++)
                {
                    char c;
                    fin >> c;
                    for (int i = 0; i < global->T; i++)
                    {
                        Player k;
                        fin >> k.currentX >> k.currentY;
                        k.color = c;
                        global->otherPlayers[c - 'A'].push_back(k);
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
            if (global->T == 0) {
                fout << -1 << " " << -1 << endl;
                continue;
            }
            else {
                for (int j = 0; j < global->T + 1; j++)
                {
                    fout << global->playerHistory[j].currentX << ' ' << global->playerHistory[j].currentY << endl;
                }
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
            fout << global->P << endl;
            for (int j = 0; j < global->P; j++)
            {
                fout << global->color[j] << endl;
                for (int h = 0; h < global->T + 1; h++)
                {
                    fout << global->otherPlayers[global->color[j] - 'A'][h].currentX << ' ' << global->otherPlayers[global->color[j] - 'A'][h].currentY << endl;
                }
            }
        }
    }
    fout.close();
}