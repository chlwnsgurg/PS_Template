/*prim's algorithm*/
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef __int128_t LL;
typedef __uint128_t ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
#define F first 
#define S second
#define pb(x) push_back(x) 
#define all(x) (x).begin(), (x).end()
#define each(x,a) for (auto &x : a)
#define rep(i,n) for (auto i = 0; i < (n); i++)
#define endl '\n'
const ll INF=INT64_MAX;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll v,e;cin>>v>>e;
    vector<vector<pll>> adj(v);
    for(ll i=0;i<e;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        a--; b--;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    ll ans=0;
    vector<bool> inMST(v,false);
    priority_queue<pll> pq;
    pq.push({0,0});
    while(!pq.empty()){
        ll cur=pq.top().second;
        ll wgt=-pq.top().first;
        pq.pop();
        if(inMST[cur]) continue;
        ans+=wgt;
        inMST[cur]=true;
        for(ll i=0;i<adj[cur].size();i++){
            ll nxt=adj[cur][i].first;
            ll nwgt=adj[cur][i].second;
            if(!inMST[nxt]){
                pq.push({-nwgt,nxt});
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}