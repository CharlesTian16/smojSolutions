/*
 * 该题目我的理解很浅，我认为需要先要得到最小次数是n*m+n+m(势能法)，
 * 然后再去构造实际用例，下面的是ai给出的写法，但是我没有交到oj，不知道对错
 * 后续再仔细理解，自行思考之后再做一遍
*/

/* #include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int total = n * m + n + m;
    vector<int> board(n + m + 2);
    for (int i = 1; i <= n; ++i) board[i] = -1; // 白
    board[n + 1] = 0;                          // 空
    for (int i = n + 2; i <= n + m + 1; ++i) board[i] = 1; // 黑

    int empty = n + 1;
    vector<int> res;
    int last = -1;

    for (int k = 0; k < total; ++k) {
        int target = -1;
        // 优先级顺序：
        // 1. 跳跃（改变2个逆序关系）
        // 2. 平移（改变1个逆序关系）
        int moves[] = {empty - 2, empty + 2, empty - 1, empty + 1};
        
        for (int pos : moves) {
            if (pos < 1 || pos > n + m + 1 || pos == last) continue;
            
            // 策略：白棋(-1)向右移动，黑棋(1)向左移动
            if (board[pos] == -1 && pos < empty) {
                // 如果是跳跃，中间必须是异色棋子，防止堵塞
                if (abs(pos - empty) == 2 && board[(pos + empty) / 2] != 1) continue;
                target = pos; break;
            }
            if (board[pos] == 1 && pos > empty) {
                if (abs(pos - empty) == 2 && board[(pos + empty) / 2] != -1) continue;
                target = pos; break;
            }
        }

        // 收尾处理：如果常规逻辑没找到，说明进入了最后强制平移阶段
        if (target == -1) {
            for (int pos : moves) {
                if (pos < 1 || pos > n + m + 1 || pos == last) continue;
                target = pos; break;
            }
        }

        res.push_back(target);
        swap(board[target], board[empty]);
        last = empty;
        empty = target;
    }

    cout << total << "\n";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << (i == res.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}*/