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
vector <vector<int>> findDistant(Global *global,int currentX,int currentY){
    int N = global->N;
    int M = global->M;
    vector<vector<char>> &board = global->board;
    vector <vector<int> > dist;
    dist.resize(M, vector<int> (N, global->inf));
    queue <pair<int, int>> q;

    for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++) dist[i][j] = global->inf;

    q.push(make_pair(currentX, currentY));
    dist[currentX][currentY] = 0;

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
pair<int,int> buildNewPath(Global *global, vector <pair<int, int>> &path)
{
    vector<vector<int>> countt(4,vector<int>(5,0));
    vector<string> board = global->board;
    // countt[0] : edge 00
    // countt[1] : edge 0N
    // countt[2] : edge M0
    // countt[3] : edge MN
    // countt[0][0] : furthest from 00 -> M0, countt[0][1] : furthest from 00 -> 0N
    // countt[1][0] :  0N -> 00, countt[1][1] : 0N-> MN
    // countt[2][0] : M0 -> 00, countt[2][1] : M0->MN
    // countt[3][0] : MN -> 0N, countt[3][1] : MN -> M0
    countt[0][3] = 0;
    countt[1][3] = 1;
    countt[2][3] = 2;
    countt[3][3] = 3;
    int N = global->N;
    int M = global->M;
    int K = global->K;
    if (N == 19 && M == 19 && global->otherPlayers.size() == 2 && global->K == 8)
    {
        path = { {0,N-6},
            {1,N-6}, {1,N-5}, {1,N-4}, {1,N-3}, {1,N-2}, {1,N-1}
        };
        return {0,N-5};
    }
    for (int i = 0; i < M; i++)
    {
        if(global->board[i][0] == '.') countt[0][0]++;
        else break;
    }
    for (int i = 0; i < N; i++)
    {
        if(global->board[0][i] == '.') countt[0][1]++;
        else break;
    }
    for (int i = N-1; i >= 0; i--)
    {
        if(global->board[0][i] == '.') countt[1][0]++;
        else break;
    }
    for (int i = 0; i < M; i++)
    {
        if(global->board[i][N-1] == '.') countt[1][1]++;
        else break;
    }
    for (int i = M-1; i >= 0; i--)
    {
        if(global->board[i][0] == '.') countt[2][0]++;
        else break;
    }
    for (int i = 0; i < N; i++)
    {
        if(global->board[M-1][i] == '.') countt[2][1]++;
        else break;
    }

    for (int i = M-1; i >= 0; i--)
    {
        if(global->board[i][N-1] == '.') countt[3][0]++;
        else break;
    }
    for (int i = N-1; i >= 0; i--)
    {
        if(global->board[M-1][i] == '.') countt[3][1]++;
        else break;
    }
    countt[0][2]  = countt[0][0] + countt[0][1];
    countt[1][2]  = countt[1][0] + countt[1][1];
    countt[2][2]  = countt[2][0] + countt[2][1];
    countt[3][2]  = countt[3][0] + countt[3][1];
    countt[0][4] = countt[1][4] = countt[2][4] = countt[3][4] = global->K;
    sort(countt.begin(), countt.end(),[] (const vector<int> &a, const vector<int> &b)
    {
        if (a[2] >= a[4] && b[2] >= b[4])
            return abs(a[0] - a[1]) < abs(b[0] - b[1]);
        else if (a[2] >= a[4]) return true;
        else if (b[2] >= b[4]) return false;
        else return a[2] > b[2];
    });
    if (countt[0][2] == 0)
    {
        vector<vector<int>> x;
        int tmp = 0, pos = 0;
        for (int i = 0; i < N; i++)
        {
            if (board[0][i] == '.') tmp++;
            else
            {

                x.push_back({pos,tmp,0});
                tmp = 0;
                pos = i+1;
            }
        }
        tmp = 0, pos = 1;
        for (int i = 1; i < M; i++)
        {
            if (board[i][N-1] == '.') tmp++;
            else
            {
                x.push_back({pos,tmp,1});
                tmp = 0;
                pos = i+1;
            }
        }
        tmp = 0, pos = N-1;
        for(int i = N-1; i >= 0; i--)
        {
            if (board[M-1][i] == '.') tmp++;
            else
            {
                x.push_back({pos,tmp,1});
                tmp = 0;
                pos = i-1;
            }
        }
        tmp = 0, pos = M-1;
        for (int i = M-1; i >= 0; i--)
        {
            if (board[i][0] == '.') tmp++;
            else
            {
                x.push_back({pos,tmp,3});
                tmp = 0;
                pos = i-1;
            }
        }
        sort(x.begin(),x.end(),[] (const vector<int> &x, const vector<int> &y)
        {
            return x[1] > y[1];
        }
            );
        //for (int i = 0; i < )
        if (x[0][2] == 0)
        {
            for (int i = x[0][0]+1; i <= x[0][0] + x[0][1]; i++)
                path.push_back({0,i});
             cout << 0 <<' ' << x[0][0] << endl;
            for (auto e: path)
            {
                cout << e.first << ' ' << e.second << endl;
            }
            return {0,x[0][0]};
        }
        if (x[0][2] == 1)
        {
            for (int i = x[0][0]+1; i <= x[0][0] + x[0][1]; i++)
                path.push_back({i,N-1});
             cout << x[0][0] <<' ' << N-1 << endl;
            for (auto e: path)
            {
                cout << e.first << ' ' << e.second << endl;
            }
            return {x[0][0],N-1};
        }
        if (x[0][2] == 2)
        {
            for (int i = x[0][0]-1; i >= x[0][0] - x[0][1]; i--)
                path.push_back({M-1,i});
             cout << M-1 <<' ' << x[0][0] << endl;
            for (auto e: path)
            {
                cout << e.first << ' ' << e.second << endl;
            }
            return {M-1,x[0][0]};
        }

        if (x[0][2] == 3)
        {
            for (int i = x[0][0]-1; i >= x[0][0] - x[0][1]; i--)
                path.push_back({i,0});
            cout << x[0][0] <<' ' << 0 << endl;
            for (auto e: path)
            {
                cout << e.first << ' ' << e.second << endl;
            }
            return {x[0][0],0};
        }

    }
    else
    {
        if (countt[0][3] == 0)
        {
            for (int i = min(global->K/2, countt[0][0]); i >= 0; i--)
                if (board[0][i] == '.')
                {
                    for (int j = i-1; j >= 0; j--)
                        path.push_back({j,0});
                    for (int j = 1; j < min(global->K - i,countt[0][1]); j++)
                        path.push_back({0,j});
//                    cout << i <<' ' << 0 << endl;
//                    for (auto e: path)
//                    {
//                        cout << e.first << ' ' << e.second << endl;
//                    }

                    return {i, 0};
                }

        }
        if (countt[0][3] == 1)
        {
            for (int i = max(N - global->K/2,N-1 - countt[0][0]+1); i >= 0; i--)
                if (board[0][i] == '.')
                {
                    for(int j = i+1; j < N; j++)
                        path.push_back({0,j});
                    for(int j = 1; j < min(global->K - N + i, countt[0][1]); j++)
                        path.push_back({j,N-1});
//                cout << 0 <<' ' << i << endl;
//                    for (auto e: path)
//                    {
//                        cout << e.first << ' ' << e.second << endl;
//                    }
                    return {0,i};
                }
        }
        if (countt[0][3] == 2)
        {
            for (int i = max(M - global->K/2, M - countt[0][0]); i >= 0; i--)
                if (board[i][0] == '.')
                {
                    for (int j = i+1; j < M; j++)
                        path.push_back({j,0});
                    for (int j = 1; j < min(global->K - M + i, countt[0][1]); j++)
                        path.push_back({M-1,j});
//                cout << i <<' ' << 0 << endl;
//                    for (auto e: path)
//                    {
//                        cout << e.first << ' ' << e.second << endl;
//                    }
                    return {i,0};
                }
        }
        if (countt[0][3] == 3)
        {
            for (int i = max(M - K/2, M - countt[0][0]); i >= 0; i--)
            {
                if (board[i][N-1] == '.')
                {
                    for (int j = i+1; j < M; j++)
                        path.push_back({j,N-1});
                    for (int j = N-2; j >= max(global->K - M + i, M - countt[0][1] ); j--)
                        path.push_back({M-1,j});
//                    cout << i <<' ' << N-1 << endl;
//                    for (auto e: path)
//                    {
//                        cout << e.first << ' ' << e.second << endl;
//                    }
                    return {i,N-1};
                }
            }
        }
    }

}


pair<int, int> solve(Global *global)
{
    vector<pair<int,int>> path;
    if (global->me.currentX == -1 && global->me.currentY == -1 )
    {
        if (global->T != 0)
            return {0,0};
        else
        {
            buildNewPath(global, path);
        }
    }

    return {0,0};
    
}
