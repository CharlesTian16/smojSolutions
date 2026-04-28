/*
 * 树的直径
 * 树形DP/两次BFS/两次DFS
 * 其中BFS/DFS无法处理负权边
*/
#include <bits/stdc++.h>
using namespace std;

int n,m;
int parent[10005];

int dp[10005];
int max_dis;

int main(){
    cin>>n>>m;
    parent[1]=1;
    for(int i=2;i<=n;++i){
        cin>>parent[i];
    }

    for(int i=1,sw;i<=m;++i){
        cin>>sw;
        max_dis=1;
        dp[sw]=1;
    }

    for(int i=n;i>1;--i){
        int old=dp[parent[i]];
        dp[parent[i]]=max(dp[parent[i]],dp[i]+1);
        // 注意可能是第二长的路径被更新
        max_dis=max(max_dis,dp[i]+1+old);
    }
    cout<<max_dis<<endl;
}