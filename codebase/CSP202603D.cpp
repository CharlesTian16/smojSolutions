#include <bits/stdc++.h>
#define ll __int128_t
using namespace std;

constexpr int length=13;
int n,m,k;
vector<long long> a;

ll k_xor(ll a,ll b){
    ll res=0,p=1;
    for(int i=0;i<15;++i){
        res+=(((a%k)+(b%k))%k)*p;
        a/=k;b/=k;p*=k;
    }
    return res;
}

ll add(ll a,ll b){
    return (a-k+b>=0)?a-k+b:a+b;
}

struct Node{
    ll sz=0;
    ll H[length];
    ll rH[length];
    ll sum_r2=0,sum_r=0;

    Node(){
        memset(H,0,sizeof(H));
        memset(rH,0,sizeof(rH));
    }

    Node(ll a){
        sz=1;
        memset(H,0,sizeof(H));
        memset(rH,0,sizeof(rH));
        ll l=a%k; sum_r=l; sum_r2=(l*l)%k;
        a-=l; int idx=0;
        a/=k;
        while(a>0){
            H[idx]=a%k;
            rH[idx]=(H[idx]*l)%k;
            a/=k;
            ++idx;        
        }
    }

    Node operator+(Node const& other) const{
        if(this->sz==0) return other;
        if(other.sz==0) return *this;
        Node res;
        for(int i=0;i<length;++i){
            res.H[i]=add((this->H[i])%k,(other.H[i])%k);
            res.rH[i]=add((this->rH[i])%k,(other.rH[i])%k);
        }
        res.sz=this->sz+other.sz;
        res.sum_r2=this->sum_r2+other.sum_r2;
        res.sum_r=this->sum_r+other.sum_r;
        return res;
    }
};

long long get_f_from_node(const Node& u) {
    ll inv2 = (k + 1) / 2; // 2逆元
    ll res = (u.sum_r2 + u.sum_r) % k * inv2 % k;

    ll p_pow = k;
    for (int i = 0; i < length; ++i) {
        ll digit_sum = (u.rH[i] + u.H[i]) % k;
        res += digit_sum * p_pow;
        p_pow *= k;
    }
    return (long long)res;
}

class SegTreeLazyRangeSet {
    vector<Node> tree;
    vector<ll> lazy;
    int n;
  
    void apply(int p,ll v){
      ll vr=v%k;
      ll vh=v/k;
      ll vh_digits[length];
      for(int i=0;i<length;++i){
        vh_digits[i]=vh%k;
        vh/=k;
      }

      // r相关
      ll sz=tree[p].sz%k;
      ll old_r=tree[p].sum_r%k;
      ll old_r2=tree[p].sum_r2%k;
      tree[p].sum_r=(old_r+sz*vr)%k;
      tree[p].sum_r2=(old_r2+2LL*vr*old_r+sz*(vr*vr%k))%k;

      // h相关
      for(int i=0;i<length;++i){
        ll dh=vh_digits[i];
        ll old_h=tree[p].H[i]%k;
        ll old_rh=tree[p].rH[i]%k;
        tree[p].H[i]=(old_h+sz*dh)%k;
        tree[p].rH[i]=(old_rh+(old_r*dh)%k+(vr*old_h)%k+(sz*(vr*dh%k))%k)%k;
      }

      // lazy累积
      lazy[p]=k_xor(lazy[p],v);
    }
  
    void pushdown(int p){
      if(lazy[p]!=0){
        apply(p<<1,lazy[p]);
        apply(p<<1|1,lazy[p]);
        lazy[p]=0;
      }
    }
  
    void pushup(int p){
      // 更新tree[p]，使用重载+运算
      tree[p] = tree[p<<1] + tree[p<<1|1];
    }
  
   public:
    SegTreeLazyRangeSet(vector<long long> const& v):n(v.size()){
      tree.resize(4*n);
      lazy.assign(4*n, 0);
      build(v,0, n-1, 1);
    }
  
    void build(vector<long long> const& v,int s, int t, int p) {
      if (s == t) {
        tree[p] = Node(v[s]);
        return;
      }
      int m = s + (t - s) / 2;
      build(v,s, m, p<<1);
      build(v,m + 1, t, p<<1|1);
      pushup(p);
    }
  
    void update(ll v,int l,int r,int cl,int cr,int p){
      if(l<=cl&&cr<=r) {apply(p,v); return;}
      pushdown(p);
      int cm=cl+((cr-cl)>>1);
      if(l<=cm) update(v,l,r,cl,cm,p<<1);
      if(cm<r) update(v,l,r,cm+1,cr,p<<1|1);
      pushup(p);
    }
  
    Node query(int l,int r,int cl,int cr,int p){
      if(l<=cl&&cr<=r) return tree[p];
      pushdown(p);
      int cm=cl+((cr-cl)>>1);
      if(r<=cm) return query(l,r,cl,cm,p<<1);
      if(cm<l) return query(l,r,cm+1,cr,p<<1|1);
      // 仍然使用重载的+运算
      return query(l,r,cl,cm,p<<1)+query(l,r,cm+1,cr,p<<1|1);
    }
  };

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>m>>k;
    a.resize(n);
    for(int i=0;i<n;++i) cin>>a[i];

    SegTreeLazyRangeSet ftree(a);

    int op,l,r;
    while(m--){
        cin>>op;
        if(op==1){
            long long v;
            cin>>l>>r>>v;
            ftree.update(v,l-1,r-1,0,n-1,1);
        }else{
            cin>>l>>r;
            Node ans=ftree.query(l-1,r-1,0,n-1,1);
            cout<<get_f_from_node(ans)<<endl;
        }
    }
}