#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define os_find(k) find_by_order(k)
#define os_order(k) order_of_key(k)

#define endl '\n'
// #define int long long
#define fast_IO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)

void file_IO(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}

const int mod = 1e9 + 7;
const int INF = INT_MAX;

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

const int N = 1e5+1;

void build(int v,int tl,int tr,int *a,int *t){
    if(tl==tr){
        t[v]=0;
    }
    else {
        int tm=(tl+tr)/2;
        build(2*v,tl,tm,a,t);
        build(2*v+1,tm+1,tr,a,t);
        t[v]=max(t[2*v],t[2*v+1]);
    }
}
int get(int v,int tl,int tr,int l,int r,int *t){
    if(l>r)return INT_MIN;
    if(l==tl and r==tr){
        return t[v];
    }
    int tm=(tl+tr)/2;
    return max(get(2*v,tl,tm,l,min(r,tm),t),get(2*v+1,tm+1,tr,max(l,tm+1),r,t));
}
void update(int v,int tl,int tr,int pos,int val,int* a,int *t) {
    if(tl==tr){
        a[pos]=val;
        t[v]=val;
    }
    else {
        int tm=(tl+tr)/2;
        if(pos<=tm){
            update(v*2,tl,tm,pos,val,a,t);
        }
        else {
            update(v*2+1,tm+1,tr,pos,val,a,t);
        }
        t[v]=max(t[v*2],t[v*2+1]);
    }
}
void solve()
{
    int n;
    cin>>n;

    int a[n];
    for(auto& i:a)
    {
        cin>>i;
    }
    int arr[N]={0};
    int t[4*N];
    build(1,0,N,arr,t);

    int lis=0;
    for(auto i:a)
    {
        int len=get(1,0,N,0,i-1,t);
        update(1,0,N,i,len+1,arr,t);
        lis=max(lis,len+1);
    }
    cout<<lis<<endl;
}

signed main()
{
    fast_IO;
    file_IO();

    solve();
}