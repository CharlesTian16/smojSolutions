#include <iostream>
#include <climits>
#include <map>

using namespace std;
int n,ans;
int maxx=-INT_MAX,minn=INT_MAX;
map<int,int> mp;
int main(){
    cin>>n;
    for(int i=0,tmp;i<n;i++){
        cin>>tmp;
        mp[tmp]++;
    }

    for(auto it:mp){
        if(it.first>0&&mp[it.first]){
            ans+=mp[it.first]*mp[-it.first];
        }
    }
    cout<<ans<<endl;
}