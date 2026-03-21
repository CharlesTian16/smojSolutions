#include <bits/stdc++.h>
using namespace std;

int gcd(int a,int b) {
    int r=0;
    while(!(a&1)&&!(b&1)){
        a>>=1;
        b>>=1;
        ++r;
    }

    while(1){
        while(!(a&1)) a>>=1;
        while(!(b&1)) b>>=1;
        (a>b)?a=a-b:b=b-a;
        if(!a) return b<<r;
        if(!b) return a<<r;
    }
}

int t;

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(0);

    cin>>t;
    int n;
    while(t--){
        cin>>n;
        int a[3];
        map<tuple<int,int,int>,int> c;
        while(n--){
            cin>>a[0]>>a[1]>>a[2];
            int g=gcd(gcd(a[0],a[1]),a[2]);
            for(int i=0;i<3;++i) a[i]/=g;
            sort(a,a+3);
            c[{a[0],a[1],a[2]}]++;
        }
        int ans=0;
        for(auto& [k,v]:c){
            ans+=v*(v-1)/2;
        }
        cout<<ans<<"\n";
    }
}