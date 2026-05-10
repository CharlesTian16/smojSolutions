/*
* 可以考虑斜率优化，四边形不等式优化，还没学习，学习后补充更强的版本 
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n,k;
int h[505];

int pre=1,cur=0;
ll dp[2][505];
constexpr ll INF=(1LL<<60);

void roll(){
    pre^=1;
    cur^=1;
}

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>h[i];
    }
    sort(h+1,h+1+n);

    for(int i=1;i<=n;++i){
        dp[pre][i]=(h[i]-h[1])*(h[i]-h[1]);
    }

    for(int t=2;t<=k;++t){
        fill(dp[cur],dp[cur]+505,INF);
        for(int i=2;i<=n;++i){
            for(int j=1;j<=i-1;++j){
                dp[cur][i]=min(dp[cur][i],dp[pre][j]+(h[i]-h[j+1])*(h[i]-h[j+1]));
            }
        }
        roll();
    }
    cout<<dp[pre][n]<<endl;
}