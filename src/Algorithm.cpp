#include"Algorithm.h"
bool areOnlySurvivor(Global *global)
{
    if (global->me.currentX == -1 && global->me.currentY == -1)
        return false;
    for (Player e : global->otherPlayers)
    {
        if (e.currentX == -1 && e.currentY == -1)
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
pair<int, int> solve(Global *global)
{
    if (areOnlySurvivor(global) == true)
    {
        // an full map con lai
    }
    else if (global->otherPlayers.size() == 1)
    {
        // solo 1 vs 1
        return {0,0};
    }
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
