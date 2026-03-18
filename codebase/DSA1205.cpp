// #include "leftify.h"
#include <bits/stdc++.h>
using namespace std;

struct BinNode
{
    BinNode *lc, *rc; // 左儿子和右儿子
    BinNode *parent; // 父亲（对于根节点为 NULL）
};

// 递归过程中把能做的事都做掉
int npl(BinNode* x){
    if(!x) return 0;
    int l=npl(x->lc);int r=npl(x->rc);
    if(l<r) swap(x->lc,x->rc);
    return 1+min(l,r);
}

void leftify(BinNode* x)
{
    npl(x);
    return;
}