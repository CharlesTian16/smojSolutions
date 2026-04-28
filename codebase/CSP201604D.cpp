#include <bits/stdc++.h>
using namespace std;

constexpr int tmax=1e4+5;
const pair<int,int> dirs[4]={{-1,0},{1,0},{0,-1},{0,1}};
int n,m,t;
// int dp[105][105];

struct Span{
    int a=-1,b=-1;
    Span(){}
    Span(int a,int b):a(a),b(b){}
}; 

struct Node{
    int r,c,t;
    Node(int r,int c,int t):r(r),c(c),t(t){}
};

Span danger[105][105];
bool vis[105][105][300];

bool valid(Node const& cur,pair<int,int> const& dir){
    return 1<=cur.r+dir.first&&cur.r+dir.first<=n&&
        1<=cur.c+dir.second&&cur.c+dir.second<=m;
}

int main(){
    cin>>n>>m>>t;

    for(int i=0;i<t;++i){
        int r,c,a,b;
        cin>>r>>c>>a>>b;
        danger[r][c]={a,b};
    }

    queue<Node> q;
    q.push({1,1,0});
    while(!q.empty()){
        // cout<<1<<endl;
        Node cur= q.front();q.pop();
        for(auto const& dir:dirs){
            int nxt_r=cur.r+dir.first;
            int nxt_c=cur.c+dir.second;

            if(cur.t+1>=300) return 0;
            
            if(valid(cur,dir)){
                if(!vis[nxt_r][nxt_c][cur.t+1]&&(cur.t+1<danger[nxt_r][nxt_c].a||cur.t+1>danger[nxt_r][nxt_c].b)){
                    vis[nxt_r][nxt_c][cur.t+1]=1;
                    if(nxt_r==n&&nxt_c==m){
                        cout<<cur.t+1<<endl;
                        return 0;
                    }
                    q.push({nxt_r,nxt_c,cur.t+1});
                }
            }
        }
    }
}