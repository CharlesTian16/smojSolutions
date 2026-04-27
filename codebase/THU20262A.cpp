#include <bits/stdc++.h>
using namespace std;

int a[102];
int n,m;
int l,r,c,t;

long long getDirect(int i,int j) {
    return abs(a[i]-a[j]);
}

long long getTrans(int i,int j){
    //i to t to j
    if(a[i]>=l&&a[i]<=r) return (long long)c+abs(a[j]-t);
    else if (a[i]<l) return (long long)l-a[i]+c+abs(a[j]-t);
    else return (long long)a[i]-r+c+abs(a[j]-t); 
}

int main(){
    cin>>n;
    for(int i=1;i<=n;++i) {
        cin>>a[i];
    }

    cin>>m;
    if(m){
        cin>>l>>r>>c>>t;
        for(int i=1;i<=n;++i){
            for(int j=i+1;j<=n;++j){
                cout<<min(getDirect(i,j),getTrans(i,j))<<" ";
            }
            cout<<endl;
        }
    }else{
        for(int i=1;i<=n;++i){
            for(int j=i+1;j<=n;++j){
                cout<<getDirect(i,j)<<" ";
            }
            cout<<endl;
        }
    }
}