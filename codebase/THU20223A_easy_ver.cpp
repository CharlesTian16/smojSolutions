/*
 * 该题目还有另一个hard ver，需要快速傅里叶变换、快速数论变换，我还不会，后续学一下
 * 该题目要注意的点是负数取模的处理，需要先把负数转正然后再取模
*/


/*
* 我的做法是类似桶排序，找到有多少小于/大于a_i的，计算其符号，一共有n个
* 另一种做法是排序+前缀和，需要进行一步推导
* 考虑排序后对角线为0的上三角矩阵
* 去掉绝对值符号并且j要小于i，ai-aj，然后把内层求和放进去，得到(i-1)a[i]-sum[i-1]这样的形式
* 也就是还需要前缀和
* 
* 以下是copy的Mario佬的标答：
* #include <stdio.h>
* #include <algorithm>
* using namespace std;
* typedef long long i64;
* int n, k;
* i64 a[100010];
* int main()
* {
*    scanf("%d%d", &n, &k);
*    for (int i = 1; i <= n; ++i)
*        scanf("%lld", &a[i]);
*    sort(a + 1, a + n + 1);
*    i64 sum = a[1], ans = 0;
*    for (int i = 2; i <= n; ++i)
*        ans += (i - 1) * a[i] - sum, sum += a[i];
*    printf("%lld", (ans * 2) % 998244353);
*}
*/
#include <bits/stdc++.h>
using namespace std;

int n,k;
constexpr int N=1e5+5;
constexpr int mod=998244353;
int a[N];
int cnt[N],s[N];
long long ans;

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>k;
    int maxx=-INT_MAX;
    for(int i=0;i<n;++i) {
        cin>>a[i];
        maxx=max(a[i],maxx);
        cnt[a[i]]++;
    }

    for(int i=1;i<=maxx;i++){
        s[i]=s[i-1]+cnt[i-1];
    }

    for(int i = 0; i < n; ++i) {
        long long coef = 1LL * s[a[i]] - (n - s[a[i]] - cnt[a[i]]);
        long long safe_coef = (coef % mod + mod) % mod; // 负数取模需要回正再取
        long long term = (safe_coef * (a[i] % mod)) % mod;
        ans = (ans + term) % mod;
    }
    
    cout << (ans * 2) % mod << "\n";
}