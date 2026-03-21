#include <bits/stdc++.h>
using namespace std;


constexpr int N=1e5+2;
int n,k,m,c;
int a[N];
vector<vector<int>> sbj;
set<vector<int>> sbjOption;

bool check(const vector<int>& op,int q){
    for(const auto& d:sbj[q]){
        for(const auto& idx:op){
            if(idx==q) return true;
        }
    }
    return false;
}

long long solve(const vector<int> &op){
    long long ans=0;
    vector<int> questions;

    for(int i=0;i<n;++i) if(check(op,i)) questions.push_back(i);
    return LONG_LONG_MAX;
}

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>k>>m>>c;
    for(int i=0;i<n;++i) cin>>a[i];


    for(int i=0,d;i<n;++i) {
        cin>>d;
        for(int j=0;j<d;++j) cin>>sbj[i][j];
        // 构造可选集合
        if(c==1){
            for(int j=0;j<d;++j) sbjOption.insert({sbj[i][j]});
        }
        if(c<=2){
            for(int j=0;j<d;++j){
                for(int k=j+1;k<d;++k){
                    vector<int> v({sbj[i][j],sbj[i][k]});
                    sort(v.begin(),v.end());
                    sbjOption.insert(v);
                }
            }
        }
        if(c<=3){
            for(int j=0;j<d;++j){
                for(int k=j+1;k<d;++k){
                    for(int l=k+1;l<d;++l){
                        vector<int> v({sbj[i][j],sbj[i][k],sbj[i][l]});
                        sort(v.begin(),v.end());
                        sbjOption.insert(v);
                    }
                }
            }
        }
    }

    long long ans=LONG_LONG_MAX;
    for(auto& op:sbjOption){
        ans=min(ans,solve(op));
    }

    if(ans<LONG_LONG_MAX) cout<<ans<<"\n";
    else cout<<-1<<"\n";
}