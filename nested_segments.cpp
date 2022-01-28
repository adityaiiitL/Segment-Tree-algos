#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #define int long long
typedef long double ld;

using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define os_find(k) find_by_order(k)
#define os_order(k) order_of_key(k)

#define debug(x)                \
    for (auto element : x)      \
        cout << element << " "; \
    cout << endl;
#define debugp(x)          \
    for (auto element : x) \
    cout << element.first << " " << element.second << endl
#define db(x) cout << #x << "=" << x << '\n'

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<long long int>(x, y)(rng)

/* Definitions */
#define fast_io ios_base::sync_with_stdio(false),cin.tie(NULL)
#define f(i, k, n) for (int i = k; i < n; i++)
#define fr(i, k, n) for (int i = k; i >= n; i--)
#define gsort(x) sort(all(x), greater<int>())
#define cntpop(x) __builtin_popcount(x)
#define cntzeroes(x) __builtin_ctzll(x)
#define nah cout << "NO" << endl
#define yeah cout << "YES" << endl
#define all(a) a.begin(), a.end()
#define mp(a, b) make_pair(a, b)
#define pb(k) push_back(k)
#define br cout << endl
#define endl '\n'
#define gcd __gcd
#define fo return

typedef vector<int> vec;
typedef vector<pair<int, int>> vp;
typedef vector<string> vs;
typedef vector<char> vc;
typedef pair<int, int> pii;
typedef map<int, int> mi;
typedef map<char, int> mc;
typedef map<string, int> ms;
const int intmax = 2147483647;
const int intmin = -2147483648;
const int mod = 1000000007; //998244353;
const double pi = 3.141592653589;

long long binpow(long long a, long long b, long long modulo) {
    a %= modulo;
    long long prod = 1;
    while (b > 0) {
        if (b & 1) {
            prod = prod * a % modulo;
        }
        a = a * a % modulo;
        b >>= 1;
    }
    return prod;
}
int modInv(int i,int mod) {return binpow(i,mod-2,mod);}
int fact[300000];
int ncr(int n,int r) {return (n>=r?(fact[n]*modInv(fact[r],mod))%mod*modInv(fact[n-r],mod)%mod:0);}
int lcm(int a, int b) { return (a * b) / gcd(a, b); }
void in(vec &v) { f(i, 0, v.size()) cin >> v[i]; }
void in1(vec &v, int n){ f(i, 0, n) {int h;cin >> h;v.pb(h);}}
void out(vec v){f(i, 0, v.size()) cout << v[i] << ' ';cout << endl;}

void build(int v,int tl,int tr,int *a,int *t){
    if(tl==tr){
        t[v]=0;
    }
    else {
        int tm=(tl+tr)/2;
        build(2*v,tl,tm,a,t);
        build(2*v+1,tm+1,tr,a,t);
        t[v]=t[2*v]+t[2*v+1];
    }
}
int get(int v,int tl,int tr,int l,int r,int *t){
    if(l>r)return 0;
    if(l==tl and r==tr){
        return t[v];
    }
    int tm=(tl+tr)/2;
    return get(2*v,tl,tm,l,min(r,tm),t)+get(2*v+1,tm+1,tr,max(l,tm+1),r,t);
}
void update(int v,int tl,int tr,int pos,int val,int *t) {
    if(tl==tr){
        t[v]=val;
    }
    else {
        int tm=(tl+tr)/2;
        if(pos<=tm){
            update(v*2,tl,tm,pos,val,t);
        }
        else {
            update(v*2+1,tm+1,tr,pos,val,t);
        }
        t[v]=t[v*2]+t[v*2+1];
    }
}
void solve()
{
    int n;
    cin>>n;
    int sz=2*n;
    int a[sz];
    for(auto& i:a){
        cin>>i;
    }
    int *t=new int[4*sz];
    build(1,0,sz-1,a,t);

    vector<int> hsh(n+1),pos(n+1);
    int ans[n];
    f(i,0,2*n){
        hsh[a[i]]++;
        if(hsh[a[i]]==1){
            pos[a[i]]=i;
        }
        else {
            ans[a[i]-1]=get(1,0,sz-1,pos[a[i]],i,t);
            update(1,0,sz-1,pos[a[i]],1,t);
        }
    }
    for(auto i:ans)cout<<i<<" ";
}

signed main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    fast_io;

    int t=1;
    // cin>>t;
    f(i,1,t+1){
        //cout<<"Case #"<<i<<": ";
        solve();
    }
    #ifndef ONLINE_JUDGE
        cerr<<"Time elapsed: "<<1000*clock()/CLOCKS_PER_SEC<<"ms"<<endl;
    #endif
}