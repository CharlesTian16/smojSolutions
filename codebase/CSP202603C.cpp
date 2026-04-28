/*重载()运算符，自定义比较器*/
#include <bits/stdc++.h>
using namespace std;
#define uint long long

struct Que{
    uint l;
    uint len;
    uint write_head;
    Que(){
        write_head=0;
    };
    Que(uint l,uint len):l(l),len(len){
        write_head=0;
    }
};

struct process{
    vector<Que> interface;

    void send(){
        uint sum=0;
        for(auto& q:interface){
            sum+=q.l+q.write_head;
            if(q.write_head==q.len-1) q.write_head=0;
            else q.write_head++;
        }
        cout<<sum<<endl;
    }
};

struct node{
    uint start;
    uint length;
    node(){};
    node(uint start,uint length):start(start),length(length){};
};

struct AllocCmp {
    bool operator()(const node& a, const node& b) const {
        if(a.length != b.length) return a.length < b.length;
        return a.start < b.start;
    }
};

struct AddrCmp {
    bool operator()(const node& a, const node& b) const {
        if(a.start != b.start) return a.start < b.start;
        return a.length < b.length;
    }
};

set<node,AllocCmp> mem4alloc;
set<node,AddrCmp> mem4addr;
process pro[105];
int n,q;

void allocate(uint p,uint l){
    auto it=mem4alloc.lower_bound({0,l});
    if(it!=mem4alloc.end()){
        cout<<(*it).start<<endl;
        pro[p].interface.push_back(Que((*it).start,l));
        if((*it).length>l){
            uint left=(*it).length-l;
            uint begin=(*it).start+l;
            mem4addr.erase({(*it).start,(*it).length});
            mem4addr.insert({begin,left});

            mem4alloc.erase(it);
            mem4alloc.insert({begin,left});
        }else{
            mem4addr.erase({(*it).start,(*it).length});
            mem4alloc.erase(it);
        }
    }
}

void dele(uint p,uint idx){
    auto in=pro[p].interface.begin()+idx-1;
    auto tar=(*in);

    uint begin=tar.l;
    uint len=tar.len;

    //先向右合并
    auto right_node=mem4addr.lower_bound({tar.l+1,tar.len});
    if(right_node!=mem4addr.end()){
        if((*right_node).start==tar.l+tar.len){
            len+=(*right_node).length;
            mem4alloc.erase({(*right_node).start,(*right_node).length});
            mem4addr.erase(right_node);
        }
    }

    //向左合并
    auto cur=mem4addr.lower_bound({tar.l,tar.len});
    if(cur!=mem4addr.begin()){
        auto left_node=prev(cur);
        if(tar.l==(*left_node).start+(*left_node).length){
            begin=(*left_node).start;
            len+=(*left_node).length;
            mem4alloc.erase({(*left_node).start,(*left_node).length});
            mem4addr.erase(left_node);
        }
    }

    mem4alloc.insert({begin,len});
    mem4addr.insert({begin,len});
    pro[p].interface.erase(in);
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin>>n>>q;
    mem4alloc.insert({0,LONG_LONG_MAX});
    mem4addr.insert({0,LONG_LONG_MAX});

    for(int i=0;i<q;++i){
        string op;
        cin>>op;
        if(op=="new"){
            uint p,l;
            cin>>p>>l;
            allocate(p-1,l);
        }else if(op=="send"){
            uint p;
            cin>>p;
            pro[p-1].send();
        }else{
            uint p,idx;
            cin>>p>>idx;
            dele(p-1,idx);
        }
    }
}