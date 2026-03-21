#include <bits/stdc++.h>
using namespace std;

int n;
int x[1005],y[1005];
int cnt[4];

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin>>n;
    for(int i=0;i<n;++i){
        cin>>x[i]>>y[i];
    }

    int k,dx,dy;
    for(int i=0;i<n;++i){
        for(int j=0;j<i;++j){
            dx=x[i]-x[j];
            dy=y[i]-y[j];
            for(int p=1;p<4;++p){
                if(dx*p==dy) cnt[p]++;
            }
        }
    }

    for(int i=1;i<4;++i){
        cout<<cnt[i]<<"\n";
    }
}