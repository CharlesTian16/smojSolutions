#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n,k;
ll dp[2][5005];
int pre=1,cur=0;
// ll中的较小(负)/较大值，用这个量级
constexpr ll INF=(1LL<<60);

void roll(){
    pre^=1;
    cur^=1;
}

pair<int,int> bags[5005];

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>bags[i].first>>bags[i].second;
    }

    sort(bags+1,bags+1+n,[](pair<int,int> const&a,pair<int,int> const&b){
        return a.second<b.second;
    });

    for(int i=1;i<=n;++i){
        dp[pre][i]=bags[i].first+bags[i].second;
    }

    for(int i=2;i<=k;++i){ // 转移k-1轮
        ll mx=dp[pre][1];
        dp[cur][1]=-INF;
        for(int j=2;j<=n;++j){ // 转移时顺便维护最大值
            if(j>=i) dp[cur][j]=mx+bags[j].first;
            else dp[cur][j]=-INF;
            mx=max(mx,dp[pre][j]);
        }
        roll();
    }

    ll ans=-INF;
    for(int i=1;i<=n;++i){
        // 如果取无意义值为-LLONG_MAX,这里会发生溢出
        ans=max(ans,dp[pre][i]-bags[i].second);
    }
    cout<<ans<<"\n";
}