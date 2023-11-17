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
    ll N;
    vl tree,lzy;
    LSegmentTree(vl& A, ll n){
        N=n;
        tree.resize(4*n);
        lzy.resize(4*n);
        init(A,0,n-1,1);
    }
    ll init(vl& A, ll l, ll r, ll node){
        if(l==r) return tree[node]=A[l];
        ll mid=(l+r)/2;
        ll lsum=init(A,l,mid,2*node);
        ll rsum=init(A,mid+1,r,2*node+1);
        return tree[node]=lsum+rsum;
    }
    void relax(ll l, ll r, ll node){
        if (lzy[node]==0) return;
        if (l<r){
            ll mid=(l+r)/2;
            tree[2*node]+=(mid-l+1)*lzy[node];
            lzy[2*node]+=lzy[node];
            tree[2*node+1]+=(r-mid) * lzy[node];
            lzy[2*node+1]+=lzy[node];
        }
        lzy[node] = 0;
    }
    ll qry(ll ql, ll qr, ll l, ll r,ll node){
        if (r<ql||qr<l) return 0;
        if (ql<=l&&r<=qr) return tree[node];
        relax(l, r, node);
        ll mid=(l+r)/2;
        return qry(ql,qr,l,mid,2*node)+qry(ql,qr,mid+1,r,2*node+1);
    }
    ll qry(ll ql,ll qr) {return qry(ql,qr,0,N-1,1);}
    void upd(ll ql, ll qr, ll val, ll l, ll r,ll node){
        if (r<ql||qr<l) return;
        if (ql<=l&&r<=qr){
            tree[node]+=(r-l+1)*val;
            lzy[node]+=val;
            return;
        }
        relax(l, r, node);
        ll mid=(l+r)/2;
        upd(ql,qr,val,l,mid,2*node);
        upd(ql,qr,val,mid+1,r,2*node+1);
        tree[node]=tree[2*node]+tree[2*node+1];
        return;
    }
    void upd(ll ql, ll qr, ll val) {upd(ql,qr,val,0,N-1,1);}
};

struct PSegmentTree{
    int cap;    
    vector<vector<tuple<ll,ll,ll>>> tree;
    PSegmentTree(vl& A, ll n){
        cap=1; while(cap<n) cap*=2;
        tree.resize(2*cap);
        for(int i=0;i<n;i++) tree[cap+i].emplace_back(A[i],0,0);
        for(int i=n;i<cap;i++) tree[cap+i].emplace_back(0,0,0);
        for(int i=cap-1;i>0;i--){
            tree[i].emplace_back(get<0>(tree[i*2][0])+get<0>(tree[i*2+1][0]),0,0);
        }
    }
    void upd(int idx,ll val){
        idx+=cap;
        tree[idx].emplace_back(val,0,0);
        for(idx = idx / 2; idx > 0; idx/=2){
            tree[idx].emplace_back(get<0>(tree[idx*2].back())+get<0>(tree[idx*2+1].back()),tree[idx*2].size()-1,tree[idx*2+1].size()-1);
        }
    }
    ll qry(int t,int l,int r,int N,int L,int R){
        if(l>R||L>r)return 0;
        if(l<=L&&R<=r)return get<0>(tree[N][t]);
        int M=(L+R)>>1;
        return qry(get<1>(tree[N][t]),l,r,N*2,L,M)+qry(get<2>(tree[N][t]),l,r,N*2+1,M+1,R);
    }
    ll qry(int t,int l,int r){
        return qry(t,l,r,1,0,cap-1);
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

const ll MAXN=1e6;
const ll sqrtN=1000;

struct Query{
	ll idx,s,e;
    bool operator<(Query &x) const {
		if(s/sqrtN != x.s/sqrtN) return s/sqrtN < x.s/sqrtN;
		return e < x.e;
	}
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

    //Mo's Algorithm
    ll q; cin>>q;
    vector<Query> Q(q);
    for(ll i=0;i<q;i++){
		cin>>Q[i].s>>Q[i].e;
        Q[i].s--; Q[i].e--;
		Q[i].idx=i;
	}
    sort(Q.begin(), Q.end());
    vector<int> A(q);
    ll s = Q[0].s, e = Q[0].e;
    ll res=0;
	for(ll i=s; i<=e; i++){
        
	}
	A[Q[0].idx] = res;
	for(ll i=1; i<q; i++){
		while(s < Q[i].s) ;
		while(s > Q[i].s) ;
		while(e < Q[i].e) ;
		while(e > Q[i].e) ;
		A[Q[i].idx] = res;
	}

    return 0;
}