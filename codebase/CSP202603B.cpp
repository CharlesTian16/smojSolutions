#include <bits/stdc++.h>
using namespace std;

struct rob{
    int o,t,a,b;
    rob(int o,int t,int a,int b):o(o),t(t),a(a),b(b){};
    rob(){};
};
constexpr int MAX_MX=1005;
rob rs[205];
int n,m;
int mx;
int sumTime;
double maxDec;

vector<pair<int,int>> candp;
vector<pair<int,int>> greedy;
int dp[MAX_MX];
bool visited[MAX_MX];

void predp(){
    memset(dp,0xcf,sizeof(dp));
    dp[0]=0;
    visited[0]=true;

    for(auto const& [cost,value]:candp){
        for(int i=min(mx,m);i>=cost;--i){
            if(visited[i-cost]){
                visited[i]=true;
                dp[i]=max(dp[i],dp[i-cost]+value);
            }
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;++i) {
        cin>>rs[i].o>>rs[i].t>>rs[i].a>>rs[i].b;
        sumTime+=rs[i].t;
        if(rs[i].o){
            candp.push_back({rs[i].a,rs[i].b});
            mx+=rs[i].a;
        }else{
            greedy.push_back({rs[i].a,rs[i].b});
        }
    }

    predp();
    sort(greedy.begin(),greedy.end(),[](const pair<int,int>& x,const pair<int,int>& y){
        return (long long)x.second*y.first>(long long)y.second*x.first;
    });

    for(int i=0;i<=min(m,mx);++i){
        if(visited[i]){
            double decTime=dp[i];
            int leftCoffee=m-i;
            for(auto const& [cost,value]:greedy){
                int consume=min(leftCoffee,cost);
                decTime+=(double)consume/cost*value;
                if(!(leftCoffee-=consume)) break;
            }
            if(decTime>maxDec) maxDec=decTime;
        }
    }

    cout << fixed << setprecision(6) << sumTime - maxDec << endl;
}