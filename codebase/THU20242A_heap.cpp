#include <bits/stdc++.h>
#define ll long long
#define N 5005
using namespace std;

int n,k;
pair<int,int> bags[N];

ll solve(){
    ll ans=-LLONG_MAX;
    if(n==k){
        ans=0;
        ans+=bags[0].second-bags[n-1].second;
        for(auto const& bag:bags){
            ans+=bag.first;
        }
        return ans;
    }

    for(int i=0;i<n-k;++i){
        priority_queue<ll,vector<ll>,greater<ll>> pq;
        ll sum=0;
        for(int j=i+1;j<n;j++){
            if(j-i+1>=k){
                ans=max(ans,sum-bags[j].second+bags[i].first+bags[j].first+bags[i].second);
            }
            pq.push(bags[j].first);
            sum+=bags[j].first;
            if(pq.size()>k-2){
                ll q=pq.top(); pq.pop();
                sum-=q;
            }
        }
    }
    return ans;
}

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>k;
    for(int i=0;i<n;++i){
        cin>>bags[i].first>>bags[i].second;
    }

    sort(bags,bags+n,[](pair<int,int> const& a,pair<int,int> const&b){
        return a.second<b.second;
    });

    cout<<solve()<<endl;
}