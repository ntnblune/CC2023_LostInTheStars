#include "LoadWrite.h"

bool loadStateData(Global *global)
{
    ifstream fin("STATE.DAT");
    bool load = false;
    string s;
    for (int i = 0; i < 4; i++)
    {
        global->otherPlayers[i].clear();
    }
    global->playerHistory.clear();
    if (!is_empty_file(fin))
    {
        while (fin >> s)
        {
            if (s == "FollowTail") {
                int t;
                fin >> t;
                for (int i = 0; i < t; i++){
                    int x;
                    fin >> x;
                    global->playerFollowTail.push_back(x);
                }
            }
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
                for (int j = 0; j < global->P; j++)
                {
                    if (global->T >= 1)
                    {
                        char c;
                        fin >> c;
                        global->color.push_back(c);
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
    if (global->playerFollowTail.size() > 0) {
        fout << "FollowTail" << endl;
        for (auto k : global->playerFollowTail){
            fout << k << endl;
        }
    }
    for (int i = 0; i < type; i++)
    {
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
            for (int j = 0; j < (int)global->nextMoves.size(); j++)
            {
                fout << global->nextMoves[j].currentX << ' ' << global->nextMoves[j].currentY << endl;
            }
        }
        else
        {
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