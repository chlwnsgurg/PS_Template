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

// segment tree for range minimum query
struct SegmentTree{
    vector<pll> tree;
    ll cap;
    SegmentTree(vl& A, ll n){
        cap=1; while(cap<n) cap*=2;
        tree.resize(2*cap);
        for(ll i=0;i<n;i++) tree[cap+i]={A[i],i};
        for(ll i=n;i<cap;i++) tree[cap+i]={INF,-1};
        for(ll i=cap-1;i>0;i--){
            if(tree[2*i].F<=tree[2*i+1].F) tree[i]=tree[2*i];
            else tree[i]=tree[2*i+1];
        }
    }
    void upd(ll idx, ll val){
        idx+=cap;
        tree[idx].F=val;
        for(idx = idx / 2; idx > 0; idx/=2){
            if(tree[2*idx].F<=tree[2*idx+1].F) tree[idx]=tree[2*idx];
            else tree[idx]=tree[2*idx+1];
        }

    }
    pll qry(ll l, ll r){
        l+=cap; r+=cap;
        pll ret={INF,-1};
        while(l<=r){
            if(l%2==1){
                if(ret.F>=tree[l].F){
                    ret.F=tree[l].F;
                    ret.S=tree[l].S;
                }
                l++;
            }
            if(r%2==0){
                if(ret.F>=tree[r].F){
                    ret.F=tree[r].F;
                    ret.S=tree[r].S;
                }
                r--;
            }
            l/=2; r/=2;
        }
        return ret;
    }
};

// segment tree with lazy propagation for range sum query
struct LSegmentTree{
    ll cap;
    vl tree,lzy;
    LSegmentTree(vl& A, ll n){
        cap=1; while(cap<n) cap*=2;
        tree.resize(2*cap);
        lzy.resize(2*cap);
        for(ll i=0;i<n;i++) tree[cap+i]=A[i];
        for(ll i=n;i<cap;i++) tree[cap+i]=0;
        for(ll i=cap-1;i>0;i--){
            tree[i]=tree[2*i]+tree[2*i+1];
        }
    }
    void relax(ll L, ll R, ll N){
        if (lzy[N]==0) return;
        if (L<R){
            ll M=(L+R)/2;
            tree[2*N]+=(M-L+1)*lzy[N];
            lzy[2*N]+=lzy[N];
            tree[2*N+1]+=(R-M)*lzy[N];
            lzy[2*N+1]+=lzy[N];
        }
        lzy[N] = 0;
    }
    ll qry(ll l, ll r, ll L, ll R,ll N){
        if (R<l||r<L) return 0;
        if (l<=L&&R<=r) return tree[N];
        relax(L, R, N);
        ll M=(L+R)/2;
        return qry(l,r,L,M,2*N)+qry(l,r,M+1,R,2*N+1);
    }
    ll qry(ll l,ll r) {return qry(l,r,0,cap-1,1);}
    void upd(ll l, ll r, ll val, ll L, ll R,ll N){
        if (R<l||r<L) return;
        if (l<=L&&R<=r){
            tree[N]+=(R-L+1)*val;
            lzy[N]+=val;
            return;
        }
        relax(L,R,N);
        ll M=(L+R)/2;
        upd(l,r,val,L,M,2*N);
        upd(l,r,val,M+1,R,2*N+1);
        tree[N]=tree[2*N]+tree[2*N+1];
        return;
    }
    void upd(ll l, ll r, ll val) {upd(l,r,val,0,cap-1,1);}
};

// persistent segment tree for range sum query
struct PSegmentTree{
    ll cap;    
    vector<vector<tuple<ll,ll,ll>>> tree;
    PSegmentTree(vl& A, ll n){
        cap=1; while(cap<n) cap*=2;
        tree.resize(2*cap);
        for(ll i=0;i<n;i++) tree[cap+i].emplace_back(A[i],0,0);
        for(ll i=n;i<cap;i++) tree[cap+i].emplace_back(0,0,0);
        for(ll i=cap-1;i>0;i--){
            tree[i].emplace_back(get<0>(tree[i*2][0])+get<0>(tree[i*2+1][0]),0,0);
        }
    }
    void upd(ll idx,ll val){
        idx+=cap;
        tree[idx].emplace_back(val,0,0);
        for(idx = idx / 2; idx > 0; idx/=2){
            tree[idx].emplace_back(get<0>(tree[idx*2].back())+get<0>(tree[idx*2+1].back()),tree[idx*2].size()-1,tree[idx*2+1].size()-1);
        }
    }
    ll qry(ll t,ll l,ll r,ll L,ll R,ll N){
        if(l>R||L>r)return 0;
        if(l<=L&&R<=r)return get<0>(tree[N][t]);
        ll M=(L+R)/2;
        return qry(get<1>(tree[N][t]),l,r,L,M,N*2)+qry(get<2>(tree[N][t]),l,r,M+1,R,N*2+1);
    }
    ll qry(ll t,ll l,ll r){
        return qry(t,l,r,0,cap-1,1);
    }
};

struct MergeSortTree{
    vector<vl> tree;
    ll cap;
    MergeSortTree(vl& A, ll n){
        cap=1; while(cap<n) cap*=2;
        tree.resize(2*cap);
        for(ll i=0;i<n;i++) tree[cap+i].push_back(A[i]);
        for(ll i=cap-1;i>0;i--){
            ll l=0,r=0;
            while(l<tree[2*i].size() && r<tree[2*i+1].size()){
                if(tree[2*i][l]<=tree[2*i+1][r]){
                    tree[i].push_back(tree[2*i][l++]);
                }
                else{
                    tree[i].push_back(tree[2*i+1][r++]);
                }
            }
            while(l<tree[2*i].size()){
                tree[i].push_back(tree[2*i][l++]);
            }
            while( r<tree[2*i+1].size()) {
                tree[i].push_back(tree[2 * i + 1][r++]);
            }
        }
    }
    // count the numbers smaller than or equal to k in range from array index l to r
    ll qry(ll l, ll r,ll k){
        l+=cap; r+=cap;
        ll ret=0;
        while(l<=r){
            if(l%2==1){
                ret+=upper_bound(all(tree[l]),k)-tree[l].begin();
                l++;
            }
            if(r%2==0){
                ret+=upper_bound(all(tree[r]),k)-tree[r].begin();
                r--;
            }
            l/=2; r/=2;
        }
        return ret;
    }
};

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
    
    ll n; cin>>n;
    vl A(n); each(x,A) cin>>x;
    SegmentTree ST(A,n);
    ll q; cin>>q;
    while(q--){
        ll op; cin>>op;
        if(op==1){
            ll i,v; cin>>i>>v;
            i--;
            A[i]=v;
            ST.upd(i,v);
        }
        if(op==2){
            ll i,j; cin>>i>>j;
            i--; j--;
            cout<<ST.qry(i,j).S<<endl;
        }
    }
    
    ll n; cin>>n;
    DisjointSet DS(n);
    while(q--){
        ll op; cin>>op;
        if(op==0){
            ll a,b; cin>>a>>b;
            DS.uni(a,b);
        }
        if(op==1){
            ll a,b; cin>>a>>b;
            if(DS.fin(a)==DS.fin(b)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    
    return 0;
}