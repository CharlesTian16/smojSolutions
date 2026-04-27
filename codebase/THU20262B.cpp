// 剪枝的依据在于26个字母很难全部都出现

#include <bits/stdc++.h>
using namespace std;

int n,m;
string s;

// 模板来自OI wiki
template <typename T>
class SegTreeLazyRangeSet {
  vector<T> tree, lazy;
  vector<bool> ifLazy;
  int n, root, n4, end;

  bool zeroTree(){
    return tree[root]==0;
  }
  
  int find_first(int l,int r,int cl,int cr,int p) {
    if(tree[p]==0) return -1;
    if(cl==cr) return cl;
    maintain(cl,cr,p);

    int res=-1;
    int m=cl+(cr-cl)/2;
    if(l<=m) res = find_first(l,r,cl,m,p*2);
    if(res==-1&&r>m) res = find_first(l,r,m+1,cr,p*2+1);
    return res;
  }

  void maintain(int cl, int cr, int p) {
    int cm = cl + (cr - cl) / 2;
    if (cl != cr && ifLazy[p]) {
      lazy[p * 2] = lazy[p], ifLazy[p * 2] = 1;
      lazy[p * 2 + 1] = lazy[p], ifLazy[p * 2 + 1] = 1;
      tree[p * 2] = lazy[p] * (cm - cl + 1);
      tree[p * 2 + 1] = lazy[p] * (cr - cm);
      lazy[p] = 0;
      ifLazy[p] = 0;
    }
  }

  T range_sum(int l, int r, int cl, int cr, int p) {
    if(tree[p]==0) return 0; // 剪枝:不存在该字符时跳过
    if (l <= cl && cr <= r) return tree[p];
    int m = cl + (cr - cl) / 2;
    T sum = 0;
    maintain(cl, cr, p);
    if (l <= m) sum += range_sum(l, r, cl, m, p * 2);
    if (r > m) sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
    return sum;
  }

  void range_set(int l, int r, T val, int cl, int cr, int p) {
    if(val==0&&tree[p]==0) return; // 剪枝:不出现时不去清零
    if(val==1&&tree[p]==cr-cl+1) return; // 剪枝:防止连续两次相同覆盖
    if (l <= cl && cr <= r) {
      lazy[p] = val;
      ifLazy[p] = 1;
      tree[p] = (cr - cl + 1) * val;
      return;
    }
    int m = cl + (cr - cl) / 2;
    maintain(cl, cr, p);
    if (l <= m) range_set(l, r, val, cl, m, p * 2);
    if (r > m) range_set(l, r, val, m + 1, cr, p * 2 + 1);
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
  }

 public:
  explicit SegTreeLazyRangeSet<T>(int size) {
    n = size;
    n4 = n * 4;
    tree = vector<T>(n4, 0);
    lazy = vector<T>(n4, 0);
    ifLazy = vector<bool>(n4, 0);
    end = n - 1;
    root = 1;
  }

  T range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }

  void range_set(int l, int r, T val) { range_set(l, r, val, 0, end, root); }

  int find_first(int l, int r) { return find_first(l, r, 0, end, root); }

  bool empty(){ return zeroTree();}
};

SegTreeLazyRangeSet<int>* trees[26];
int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin>>n>>m>>s;

    for(int i=0;i<26;++i){
        trees[i] = new SegTreeLazyRangeSet<int>(n);
    }

    for(int i=0;i<n;++i){
        trees[s[i]-'A']->range_set(i,i,1);
    }

    int op,l,r;
    while(m--){
        cin>>op>>l>>r;
        if(op==1){
            char c;
            cin>>c;
            int res=trees[c-'A']->find_first(l-1,r-1);
            cout<<((res>=0)?res+1:-1)<<"\n";
        }
        else if(op==2){
            char c;
            cin>>c;
            for(int i=0;i<26;++i){
                trees[i]->range_set(l-1,r-1,(i==c-'A')?1:0);
            }
        }
        else {
            int count[26];
            for(int i=0;i<26;++i){
                count[i]=0;
                if(trees[i]->empty()) continue;
                count[i]=trees[i]->range_sum(l-1,r-1);
                trees[i]->range_set(l-1,r-1,0);
            }

            int pos=l-1;
            for(int i=0;i<26;++i){
                if(count[i]>0){
                    trees[i]->range_set(pos,pos+count[i]-1,1);
                    pos+=count[i];
                }
            }
        }
    }
}