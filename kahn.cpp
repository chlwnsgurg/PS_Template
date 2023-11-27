/*kahn’s algorithm for topological sorting*/
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
    ll n,m; cin>>n>>m;
    vector<vl> adj(n);
    rep(i,m){
        ll u,v; cin>>u>>v;
        u--; v--;
        adj[u].pb(v);
    }
    vl indegree(n+1);
    for(ll i=0;i<n;i++){
        for(ll j=0;j<adj[i].size();j++){
            ll there=adj[i][j];
            indegree[there]++;
        }
    }
    vector<bool> disc(n,false);
    queue<ll> Q;
    for(ll i=0;i<n;i++){
        if(indegree[i]==0){
            Q.push(i);
            disc[i]=true;
        }
    }
    vector<ll> ans;
    while(!Q.empty()){
        ll here=Q.front();
        ans.push_back(here);
        Q.pop();
        for(ll i=0;i<adj[here].size();i++){
            ll there=adj[here][i];
            indegree[there]--;
            if(indegree[there]==0){
                Q.push(there);
                disc[there]=true;
            }
        }
    }
    each(x,ans) cout<<x+1<<' ';
    return 0;
}