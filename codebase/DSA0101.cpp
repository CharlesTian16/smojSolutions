/*
 * 多组输入 单次O(n)会超时，dp并记忆化存储
*/
#include <bits/stdc++.h>
using namespace std;

int n,t;
int fib[1000005];
constexpr int N=1e6+3;
constexpr int mod=1e9+7;

int add(int a,int b){
    return (a-mod+b>=0)?a-mod+b:a+b;
}

void init(){
    fib[0]=0,fib[1]=1;
    for(int i=2;i<=N;++i){
        fib[i]=add(fib[i-1],fib[i-2]);
    }
}

int main(){
    init();
    cin>>t;
    while(t--){
        cin>>n;
        cout<<fib[n]<<"\n";
    }
}