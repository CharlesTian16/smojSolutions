#include <bits/stdc++.h>
using namespace std;

int n;
int a[45],b[45],c[45],d[45];
int f[2][402][402];

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i]>>b[i]>>c[i]>>d[i];
    }

    memset(f,0x3f,sizeof(f));
    //f[i][j][k]:完成前i个任务时，cpu1/2使用j/k时间，f为gpu最小使用时间(均为可再次使用时)
    //另一种f值为bool，表示能否成立，会多出一个维度表示gpu(nm规模)
    //这里能够替代是因为gpu维度具有单调性，使用bool会有很多冗余信息
    /*可以把规模较大的信息作为值，从而减少空间占用*/
    f[0][0][0]=0;
    for(int i=1;i<=n;i++){
        int ii=i&1;//位运算trick:i%2,滚动数组定位
        int ni=ii^1;//异或找到另外一行
        for(int j=0;j<=400;++j){
            for(int k=0,p;k<=400;++k){ 
                /*
                 *采用拉(Pull)的方式，好处是不需要手动进行复杂的初始化
                 *推需要把第0层手动初始化
                 *内层两个循环倒序正序无所谓
                */
                f[ii][j][k]=1e9;//滚动数组清除旧值
                if(j>=a[i]) f[ii][j][k]=min(f[ii][j][k],f[ni][j-a[i]][k]);
                if(k>=a[i]) f[ii][j][k]=min(f[ii][j][k],f[ni][j][k-a[i]]);
                /*这里根据表层语义来看有点迷惑，画图后再从语义上理解：
                *占用两个CPU时GPU也相当于被占用所以要加上去
                *样例:
                *3
                *10 10 2 10
                *10 10 3 10
                *10 1 10 10
                *输出:
                *6
                */
                if(j>=b[i]&&k>=b[i]) f[ii][j][k]=min(f[ii][j][k],f[ni][j-b[i]][k-b[i]]+b[i]);
                if(j>=c[i]) f[ii][j][k]=min(f[ii][j][k],f[ni][j-c[i]][k]+c[i]);
                if(k>=c[i]) f[ii][j][k]=min(f[ii][j][k],f[ni][j][k-c[i]]+c[i]);
                if(j>=d[i]&&k>=d[i]) f[ii][j][k]=min(f[ii][j][k],f[ni][j-d[i]][k-d[i]]+d[i]);
            }
        }
    }

    int ans=INT_MAX;
    for(int i=0;i<=400;++i){
        for(int j=0;j<=400;++j){
            ans=min(ans,max(f[n&1][i][j],max(i,j)));
        }
    }
    cout<<ans<<"\n";
}