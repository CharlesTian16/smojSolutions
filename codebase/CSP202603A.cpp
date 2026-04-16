#include <bits/stdc++.h>
using namespace std;

int n;
int a[105];
int ans;

bool check(int a){
    int count=0;
    int p=-1;
    int mx=-1;
    while(a){
        p++;
        if(a&1){
            count++;
            mx=p;
        }
        a>>=1;
    }
    return mx+1-count==count;
}

int main(){
    cin>>n;
    for(int i=0;i<n;++i) {
        cin>>a[i];
        if(check(a[i])) ans++;
    }

    cout<<ans<<"\n";
}