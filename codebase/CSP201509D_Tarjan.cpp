/*Tarjan算法求SCC+链式前向星(便于遍历出边)*/
#include <cstdio>
#include <vector>
#define N 10005
#define M 100005
using namespace std;

int n,m;
int head[N],ver[M],nxt[M];
int cnt=1;
int scnt,scc[N];

bool instack[N];
int t,dfn[N],low[N];
vector<int> st;
void add(int a,int b){
    ver[++cnt] = b;      // cnt号边指向b
    nxt[cnt] = head[a];  // cnt号边下一条边为head[a]
    head[a] = cnt;       // head[a]表示从a出发的第一条边，第cnt号 
}

void tarjan(int u){
    dfn[u] = low[u] = ++t;
    instack[u]= true;
    st.push_back(u);
    for(int i=head[u];i!=0;i=nxt[i]){
        int v = ver[i];
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        } else if(instack[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        while(1) {
            int tp = st.back();
            st.pop_back();
            instack[tp] = false;
            scc[scnt]++;
            if(tp==u){
                scnt++;
                break;
            }
        }
    }
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0,a,b;i<m;i++){
        scanf("%d %d",&a,&b);
        add(a,b);
    }

    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }

    long long ans=0;
    for(int i=0;i<scnt;i++){
        ans+=scc[i]*(scc[i]-1)/2;
    }
    printf("%lld",ans);
}