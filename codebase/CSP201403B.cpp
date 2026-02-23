#include <iostream>
#include <vector>
using namespace std;

int n,m;
int cpri;
struct window{
    int lx,ly,rx,ry,pri;
    window(int a,int b,int c,int d):lx(a),ly(b),rx(c),ry(d){
        pri=++cpri;   
    }
    void update(){
        pri=++cpri;
    }
};
vector<window> wins;

bool in(int x,int y,window w){
    return x>=w.lx&&x<=w.rx&&y>=w.ly&&y<=w.ry;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;

    wins.reserve(12);
    for(int i=0,a,b,c,d;i<n;i++){
        cin>>a>>b>>c>>d;
        wins.emplace_back(a,b,c,d);
    }

    for(int i=0,j,x,y,maxx,cl,flag;i<m;i++){
        cin>>x>>y;
        flag=0;
        maxx = -1;
        cl=-1;
        for(j=n-1;j>=0;j--){
            if(in(x,y,wins[j])&&wins[j].pri>maxx) {
                flag=1;
                maxx = wins[j].pri;
                cl=j;
            }
        }
        if(!flag) cout<<"IGNORED"<<"\n";
        else {
            wins[cl].update();
            cout<<(cl+1)<<"\n";
        }
    }
    return 0;
}