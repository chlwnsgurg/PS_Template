/*Manacher's algorithm*/
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
    string inp; cin>>inp;
    ll n=2*inp.length()-1; string s;
    each(x,inp){
        s.push_back(x);
        s.push_back('#');
    }
    vl P(n);
    ll r=-1,mid=-1;
    for(ll i=0;i<n;i++){
        if(i<=r) P[i]=min(r-i,P[2*mid-i]);
        while(i-P[i]-1>=0&&i+P[i]+1<n&&s[i-P[i]-1]==s[i+P[i]+1]) P[i]++;
        if(r<i+P[i]){
            r=i+P[i];
            mid=i;
        }
    }
    ll ans=0;
    for(ll i=0;i<n;i++){
        if(i%2) ans=max(ans,2*((P[i]+1)/2));
        else ans=max(ans,2*((P[i])/2)+1);
    }
    cout<<ans;
    return 0;
}