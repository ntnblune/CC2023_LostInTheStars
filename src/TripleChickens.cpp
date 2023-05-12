#include"InputOutput.h"
#include"Algorithm.h"
#include"LoadWrite.h"
int main() {


    Global *global = new Global;
    srand(time(NULL));
    cin.tie(0) -> sync_with_stdio(0);
    cout.tie(0);
    input(global);
    pair<int,int> ans = solve(global);
    output(ans);
    global->me.currentX = ans.first;
    global->me.currentY = ans.second;
    cout << global->me.currentX << " " << global->me.currentY << endl;
    saveStateData(global);
    return 0;
}
