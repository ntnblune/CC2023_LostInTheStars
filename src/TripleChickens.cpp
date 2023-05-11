#include"InputOutput.h"
#include"Algorithm.h"
#include"LoadWrite.h"
int main() {


    Global *global = new Global;
    srand(time(NULL));
    cin.tie(0) -> sync_with_stdio(0);
    cout.tie(0);
    input(global);

    output(solve(global));
    saveStateData(global);
    return 0;
}
