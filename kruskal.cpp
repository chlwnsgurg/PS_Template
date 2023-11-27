/*kruskal algorithm*/
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

struct DisjointSet{
    vl par;
    DisjointSet(ll n){
        par.resize(n,-1);
    }
    ll fin(ll a){
        if(par[a]<0) return a;
        else return par[a]=fin(par[a]); // path compression
    };
    void uni(ll a,ll b){
        a=fin(a); b=fin(b);
        if(a!=b){
            if(-par[a]<-par[b]) swap(a,b); // union by size
            par[a]+=par[b];
            par[b]=a;
        }
    };

};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll n,m;cin>>n>>m;
    vector<vector<pll>> adj(n);
    for(ll i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        u--; v--;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<pair<ll,pll>> E;
    for(ll i=0;i<n;i++){
        for(ll j=0;j<adj[i].size();j++){
            E.push_back({adj[i][j].second,{i,adj[i][j].first}});
        }
    }
    sort(all(E));
    DisjointSet DS(n);
    ll ans=0;
    for(ll i=0;i<E.size();i++){
        ll u=E[i].second.first,v=E[i].second.second,w=E[i].first;
        if(DS.fin(u)==DS.fin(v)) continue;
        ans+=w;
        DS.uni(u,v);
    }
    cout<<ans<<endl;
    return 0;
}