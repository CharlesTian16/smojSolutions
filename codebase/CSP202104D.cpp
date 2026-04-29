#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int mod=1e9+7;
constexpr int N=1e5+5;
int n;
int a[N];
int dp[N];
vector<ll> d[N];
// bool数组就好，没必要用set
bool vis[N];

ll method(int j,int i){
    ll ans=0;
    int dif=a[i]-a[j];
    vis[dif]=1;
    for(ll l=0;l<d[dif].size();++l){
        if(!vis[d[dif][l]]){
            vis[d[dif][l]]=1;
            ans++;
        }
    }
    return ans;
}

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }

    // 类似埃筛预处理约数
    for(ll i=1;i<=a[n]/2;++i){
        for(ll j=2*i;j<=a[n];j+=i){
            d[j].push_back(i);
        }
    }

    // 区间dp，(j,i)路段不设中间拦截
    // 从j-1开始，积累存在障碍的距离，不允许放置
    dp[1]=1;
    for(int i=2;i<=n;++i){
        memset(vis,0,sizeof(vis));
        for(int j=i-1;j>=1;--j){
            dp[i]=(dp[i]+dp[j]*method(j,i)%mod)%mod;
        }
    }

    cout<<dp[n]<<endl;
}