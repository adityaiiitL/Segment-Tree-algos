#include <bits/stdc++.h>
using namespace std;

#define int long long 

void build(int v,int tl,int tr,int *a,int *t){
    if(tl==tr){
        t[v]=a[tl];
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

signed main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n,q;
    cin >> n >> q;
    int a[n];
    for (auto &i : a) {
        cin >> i;
    }
    int t[4*n+4];
    build(1,0,n-1,a,t);

    int c,l,r;
    while(q--)
    {
        cin>>c>>l>>r;
        if(c==2){
            r--;
            cout<<get(1,0,n-1,l,r,t)<<endl;
        }
        else update(1,0,n-1,l,r,t);
    }

    return 0;
}