#include"Algorithm.h"
bool areOnlySurvivor(Global *global)
{
    if (global->me.currentX == -1 && global->me.currentY == -1)
        return false;
    for (int i = 0; i < 3; i++)
    {
        if (global->otherPlayers[i][global->otherPlayers[i].size()-1].currentX == -1 && global->otherPlayers[i][global->otherPlayers[i].size()-1].currentY == -1)
            continue;
        return false;
    }
    return true;
}
vector <vector<int>> findDistant(Global *global){
    int N = global->N;
    int M = global->M;
    vector<vector<char>> &board = global->board;
    vector <vector<int> > dist;
    dist.resize(M, vector<int> (N, global->inf));
    queue <pair<int, int>> q;

    for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++) dist[i][j] = global->inf;

    q.push(make_pair(global->me.currentX, global->me.currentY));
    dist[global->me.currentX][global->me.currentY] = 0;

    while (!q.empty()){
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();
        for (const auto &[dx, dy] : global->directions) {
            int nextX = curX + dx;
            int nextY = curY + dy;
            if (nextX < 0 || nextY < 0 || nextX >= M || nextY >= N || ('a' <= board[nextX][nextY] && board[nextX][nextY] <= 'd') || board[nextX][nextY] == '#')
                continue;
            if (dist[nextX][nextY] > dist[curX][curY] + 1){
                q.push(make_pair(nextX, nextY));
                dist[nextX][nextY] = dist[curX][curY] + 1;
            }
        }
    }
    return dist;

}

vector<int> checkFollowTail(Global *global){
    vector<int> v;
    v.clear();
    bool firstEqual = false, secondEqual = false;
    if (global->T >= 3){
        for (int i = 0; i < 4; i++)
        {
            firstEqual = secondEqual = false; 
            if (!global->otherPlayers[i].empty())
            {
                if (count(global->playerFollowTail.begin(), global->playerFollowTail.end(), i) > 0) 
                {
                    v.push_back(i);
                    continue;
                }
                int yourSize = global->otherPlayers[i].size();
                int mySize = global->playerHistory.size();
                cout << "Your size: " << yourSize << endl;
                cout << "My size: " << mySize << endl;
                cout << "Hello" << endl;
                if (global->playerHistory[mySize - 2].currentX == global->otherPlayers[i][yourSize - 1].currentX
                    && global->playerHistory[mySize - 2].currentY == global->otherPlayers[i][yourSize - 1].currentY)
                {
                    firstEqual = true;
                    cout << "first true" << endl;
                }
                if (global->playerHistory[mySize - 3].currentY == global->otherPlayers[i][yourSize - 2].currentY
                    && global->playerHistory[mySize - 3].currentY == global->otherPlayers[i][yourSize - 2].currentY)
                {
                    secondEqual = true;
                    cout << "second true" << endl;
                }
            }
            if (firstEqual && secondEqual) 
            {
                global->playerFollowTail.push_back(i);
                v.push_back(i);
            }
        }
    }
    return v;
}

pair<int, int> solve(Global *global)
{
    
    if (global->me.currentX == -1 && global->me.currentY == -1)
        return {2,0};

    vector<int>v = checkFollowTail(global);
    if (v.size() > 0)
    {
        int size = global->otherPlayers[v[0]].size();
        return {global->otherPlayers[v[0]][size - 1].currentX, global->otherPlayers[v[0]][size-1].currentY};
    }

    if (global->me.currentY <= global->N - 5) return {global->me.currentX, global->me.currentY+1};
    //else if (global->me.currentX <= global->N - 5) return {global->me.currentX+1, global->me.currentY};
    //else return  {global->me.currentX, global->me.currentY-1};

    if (areOnlySurvivor(global) == true)
    {
        // an full map con lai
    }
    // else if (global->otherPlayers.size() == 1)
    // {
    //     // solo 1 vs 1
    //     return {0,0};
    // }
    else
    {
        // 1 vs 3
        if (global->me.currentX == -1 && global->me.currentY == -1)
        {
          //   Game Start, bo goc thoi nao
            return {0,0};
        }
//        vector <pair<int, int>> path;
//        loadStateData(path);
//
//        if (path.empty() && !buildNewPath(path))
//            return make_pair(-1, -1);
//
//        int nextX = path.back().first, nextY = path.back().second;
//        path.pop_back();
//
//        generateNewPath(path);
//        return make_pair(nextX, nextY);
    }
}
