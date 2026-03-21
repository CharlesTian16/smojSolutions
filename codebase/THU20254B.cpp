#include <bits/stdc++.h>
using namespace std;

int sum(vector<int>& vec,int a,int b){//[a,b]
    auto fi=lower_bound(vec.begin(),vec.end(),a);
    auto la=upper_bound(vec.begin(),vec.end(),b);
    return la-fi;
}

int n,q;
int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(0);

    cin>>n>>q;
    unordered_map<int,vector<int>> hh,vv,pk,nk;
    int x,y;
    while(n--) {
        cin>>x>>y;
        hh[y].push_back(x);
        vv[x].push_back(y);
        pk[y-x].push_back(x);//x算距离即可
        nk[x+y].push_back(x);
    }

    for(auto& [k,v]:hh) sort(v.begin(),v.end());
    for(auto& [k,v]:vv) sort(v.begin(),v.end());
    for(auto& [k,v]:pk) sort(v.begin(),v.end());
    for(auto& [k,v]:nk) sort(v.begin(),v.end());

    int k;
    long long ans;
    while(q--){
        ans=0;
        cin>>x>>y>>k;
        ans+=sum(hh[y],x-k,x+k);
        ans+=sum(vv[x],y-k,y+k);
        ans+=sum(pk[y-x],x-k,x+k);
        ans+=sum(nk[y+x],x-k,x+k);
        cout<<ans<<"\n";
    }
}