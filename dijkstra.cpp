/*dijkstra algorithm*/
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
    ll src; cin>>src;
    src--;
    vector<vector<pll>> adj(v);
    for(ll i=0;i<e;i++){
        ll u,v,w; cin>>u>>v>>w;
        u--; v--;
        adj[u].push_back({v,w});
    }
    vl dist(v,INF);
    priority_queue<pll> pq;
    dist[src]=0;
    pq.push({0,src});
    while (!pq.empty()){
        ll cdist = -pq.top().first;
        ll cur = pq.top().second;
        pq.pop();
        if(dist[cur]<cdist) continue;
        for(ll i=0;i<adj[cur].size();i++){
            ll nxt=adj[cur][i].first;
            ll ndist=cdist+adj[cur][i].second;
            if(dist[nxt]>ndist){
                dist[nxt]=ndist;
                pq.push({-ndist,nxt});
            }
        }
    }
    for(ll i=0;i<v;i++){
        if(dist[i]==INF) cout<<"INF"<<'\n';
        else cout<<dist[i]<<'\n';
        
    }
    return 0;
}