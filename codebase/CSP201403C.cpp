#include <iostream>
#include <string>
#include <map>
using namespace std;

string s;
int n;
int rules[26];

// getToken分割字符串
string getToken(int& begin,const string& cmd){
    while(begin<cmd.length()&&isblank(cmd[begin])){
        ++begin;
    }
    if (begin >= cmd.length()) return "";
    int p1 = begin;
    while(begin<cmd.length()&&!isblank(cmd[begin])){
        ++begin;
    }
    int p2 = begin;
    return cmd.substr(p1,p2-p1);
}

bool isPara(const string& token){
    return token.length()==2&&token[0]=='-'&&isalpha(token[1]);
}

bool isArg(const string& token){
    bool res = true;
    for(const auto& c:token){
        if(!(isalpha(c)||isdigit(c)||c=='-')) {
            res = false;
            break;
        }
    }
    return res;
}

void print(int i,map<char,string> res){
    cout<<"Case "<<i<<":";
    for(const auto& [k,v]:res){
        cout<<" -"<<k;
        if(!v.empty())cout<<" "<<v;
    }
    cout<<"\n";
}

void solve(int i,string cmd){
    map<char,string> res;
    int begin = 0;
    getToken(begin,cmd);

    while(begin<cmd.length()){
        string token = getToken(begin,cmd);
        if(isPara(token)){
            char key=token[1];
            if(rules[key-'a']==0){
                break;
            } else if(rules[key-'a']==1){
                res[key]="";
            } else {
                string arg=getToken(begin,cmd);
                if(isArg(arg)){
                    res[key]=arg;
                } else break;
            }
        }else{
            break;
        }
    }
    print(i,res);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // cin遇到空白即停止，空白仍在缓冲区中
    cin>>s>>n;
    for (int i=0;i<26;++i) rules[i] = 0;
    for (int i=0;i<s.length();++i) {
        if (i+1<s.length()&&s[i+1]==':') {
            rules[s[i]-'a']=2;
            ++i;
        } else {
            rules[s[i]-'a']=1;
        }
    }

    // 1.getline遇到'\n'才会停止，遇到空格等其他空白不停止
    // 2.getline会把'\n'拿出缓冲区，但是不放入字符串中
    string dummy;
    getline(cin,dummy);

    for(int i=1;i<=n;++i){
        string cmd;
        getline(cin,cmd);
        solve(i,cmd);
    }
}