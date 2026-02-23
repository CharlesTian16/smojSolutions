#include <iostream>
#define ll long long
using namespace std;

constexpr int N = 1e7+2;
int n,x,y;
ll ans[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> x >> y;
    for(int i=1;i<=n;++i){
        if(i&1==1){
            ans[i] = min(ans[i-1]+x,ans[(i+1)/2]+y+x);
        } else {
            ans[i] = min(ans[i-1]+x,ans[i/2]+y);
        }
    }

    cout<<ans[n]<<"\n";
}