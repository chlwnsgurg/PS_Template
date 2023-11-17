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
const ld PI=acosl(-1);

ll gcd(ll a, ll b){ 
    return b ? gcd(b, a % b) : a; 
}
ll lcm(ll a, ll b){
    if (a && b) return a * (b / gcd(a, b));
    return a + b;
}
pll extended_gcd(ll a, ll b){
    if (b == 0) return {1, 0};
    auto t = extended_gcd(b, a % b);
    return {t.second, t.first - t.second * (a / b)};
}
ll modinverse(ll a, ll m){
    return (extended_gcd(a, m).first % m + m) % m;
}
ll large_mod_add(ll a, ll b, ll m){
    return ll(((LL)a + (LL)b) % m);
}
ll large_mod_mul(ll a, ll b, ll m){
    return ll((LL)a * (LL)b % m);
}
ll modpow(ll n, ll k, ll m){
    ll ret = 1;
    n %= m;
    while (k){
        if (k & 1) ret = large_mod_mul(ret, n, m);
        n = large_mod_mul(n, n, m);
        k>>=1;
    }
    return ret;
}
bool test_witness(ull a, ull n, ull s){
    if (a >= n) a %= n;
    if (a <= 1) return true;
    ull d = n >> s;
    ull x = modpow(a, d, n);
    if (x == 1 || x == n - 1) return true;
    while (s-- > 1){
        x = large_mod_mul(x, x, n);
        if (x == 1) return false;
        if (x == n - 1) return true;
    }
    return false;
}
bool is_prime(ull n){
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    ull d = n >> 1, s = 1;
    for (; (d & 1) == 0; s++) d >>= 1;
#define T(a) test_witness(a##ull, n, s)
    if (n < 4759123141ull) return T(2) && T(7) && T(61);
    return T(2) && T(325) && T(9375) && T(28178) && T(450775) && T(9780504) && T(1795265022);
#undef T
}
ll pollard_rho(ll n){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<ll> dis(1, n - 1);
    ll x = dis(gen);
    ll y = x;
    ll c = dis(gen);
    ll g = 1;
    while (g == 1){
        x = (large_mod_mul(x, x, n) + c) % n;
        y = (large_mod_mul(y, y, n) + c) % n;
        y = (large_mod_mul(y, y, n) + c) % n;
        g = gcd(abs(x - y), n);
    }
    return g;
}
void factorize(ll n, map<ll, ll> &fl){
    if (n == 1) return;
    if (n % 2 == 0){
        fl[2]++;
        factorize(n / 2, fl);
    }
    else if (is_prime(n)){
        fl[n]++;
    }
    else{
        ll f = pollard_rho(n);
        factorize(f, fl);
        factorize(n / f, fl);
    }
}
void seive(ll n,vl& P){
    vector<bool> IP;
	IP.resize(n+1,true);
    for (ll i=2;i*i<=n;i++){
        if (!IP[i]) continue;
        for (ll j=i*i;j<=n;j+=i) IP[j]=0;
    }
    for (ll i=2;i<=n;i++) if(IP[i]) P.push_back(i);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    ll n; cin>>n;
    map <ll,ll> f;
    factorize(n,f);
    /*
    Regarding the number of divisors, a useful thing for programming contests is to search OEIS for "Maximal number of divisors",
    The number is 1344 for integers up to 1e9
    */

    ll n; cin>>n;
    vl P;
    seive(n,P);
    /*
    Regarding 𝜋(𝑛), the  number of primes less than n, it is conjectured to be approximately n/ln(n)
    */
    
    return 0;
}