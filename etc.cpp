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
#define each(x, a) for (auto &x : a)
#define rep(i, n) for (auto i = 0; i < (n); i++)
#define endl '\n'

const ll INF=INT64_MAX;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    /*coordinate compression*/
    ll n; cin>>n;
    vl A(n); each(x,A) cin>>x;
    vl T(A);
    // remove duplicates
    sort(T.begin(),T.end());
    T.erase(unique(T.begin(),T.end()),T.end());
    for(ll i=0;i<n;i++){
		A[i] = lower_bound(T.begin(), T.end(), A[i]) - T.begin();
	}

    /*union-find*/
    vector<ll> par(n);
    for(ll i=0;i<n;i++) par[i]=-1;

    function<ll(ll)> fin=[&](ll v)->ll {
        if(par[v]<0) return v;
        else return par[v]=fin(par[v]);
    };

    function<void(ll,ll)> uni=[&](ll a,ll b){
        a=fin(a); b=fin(b);
        if(a!=b){
            if(-par[a]<-par[b]) swap(a,b);
            par[a]+=par[b];
            par[b]=a;

        }
    };


    return 0;
}