//#include "heapify.h"
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;


constexpr int N=1e6+2;
vector<int> nums;

struct BinNode
{
    int data; // 关键码
    BinNode *lc, *rc; // 左儿子和右儿子
    BinNode *parent; // 父亲（对于根节点为 NULL）
};

// 利用模板和lamda匿名函数在bfs中执行不同的操作
template<typename Action>
void bfs(BinNode* x,Action act){
    queue<BinNode*> q;
    q.push(x);
    act(x);
    
    while(!q.empty()){
        BinNode* u = q.front(); q.pop();
        if(u->lc){
            act(u->lc);
            q.push(u->lc);
        }
        if(u->rc){
            act(u->rc);
            q.push(u->rc);
        }
    }
}

// 不一定是完全二叉树，直接递归然后下沉最坏会O(n^2)
void heapify(BinNode* x){
    bfs(x,[&](BinNode* x){
        nums.push_back(x->data);
    });
    sort(nums.begin(),nums.end(),greater<int>());
    int index=0;
    bfs(x,[&](BinNode* x){
        x->data=nums[index++];
    });
}