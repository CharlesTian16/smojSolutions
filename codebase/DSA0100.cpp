/*
 * 邓书 线性递归版本
*/
#include <bits/stdc++.h>
using namespace std;

int n;
constexpr int mod=1e9+7;

int add(int a,int b){
    return (a-mod+b>=0)?a-mod+b:a+b;
}

int solve(const int& p,int& prev){
    if(p==0){
        prev=1;
        return p;
    } 
    int preprev;
    prev=solve(p-1,preprev);
    return add(prev,preprev);
}

int main(){
    scanf("%d",&n);
    int prev;
    printf("%d\n",solve(n,prev));
}