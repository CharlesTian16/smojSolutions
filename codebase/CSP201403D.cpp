#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;

int n,m,k,r;
pii nds[205];// 使用pair记录点坐标

/*
 * dis[i][j]表示从nds[0]添加了j个路由器时，到nds[i]经过的中转路由器个数
 * 这样设计可以把点用nds中的编号表示，既可以防止点坐标混乱，也可以省出来一维来表示信息
*/ 
int dis[205][102]; 
bool vis[205][102];

bool check(pii a,pii b){
    return 1LL*(a.first-b.first)*(a.first-b.first)+1LL*(a.second-b.second)*(a.second-b.second)<=1LL*r*r;
}

void bfs(){
    memset(dis,0x3f,sizeof(dis));
    queue<pii> q;
    q.push({0,0});
    vis[0][0]=1,dis[0][0]=-1;
    while(!q.empty()){
        auto u=q.front();q.pop();
        // 优化:可以预先建图来减少计算
        for(int i=0;i<n+m;++i){
            if(!check(nds[u.first],nds[i])) continue;
            // 单源最短路径从单点出发不断松弛即可
            if(dis[i][u.second+(i>=n)]>dis[u.first][u.second]+1){
                dis[i][u.second+(i>=n)]=dis[u.first][u.second]+1;
                if(!vis[i][u.second+(i>=n)]){
                    q.push({i,u.second+(i>=n)});
                    vis[i][u.second+(i>=n)]=1;
                }
            }
        }
    }
}

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>m>>k>>r;
    for(int i=0;i<n;++i){
        cin>>nds[i].first>>nds[i].second;
    }
    for(int i=0;i<m;++i){
        cin>>nds[i+n].first>>nds[i+n].second;
    }

    bfs();

    int ans=INT_MAX;
    for(int i=0;i<=k;i++){
        ans=min(ans,dis[1][i]);
    }

    cout<<ans<<"\n";
}