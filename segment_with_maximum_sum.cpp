#include<bits/stdc++.h>
using namespace std;

#define fast() ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
#define int long long 

struct Data 
{
    int sum,pre,suf,ans;
};

Data makeData(int val){
    Data res; 
    res.sum=val;
    res.ans=res.pre=res.suf=max(0LL,val);
    return res;
}

Data Merge(Data l,Data r){
    Data res;

    res.sum=l.sum+r.sum;
    res.pre=max(l.pre,l.sum+r.pre);
    res.suf=max(r.suf,r.sum+l.suf);
    res.ans=max({l.ans,r.ans,l.suf+r.pre});

    return res;
}
void build(int v,int tl,int tr,int *a,Data *t){
    if(tl==tr){
        t[v]=makeData(a[tl]);
    }
    else {
        int tm=(tl+tr)/2;
        build(2*v,tl,tm,a,t);
        build(2*v+1,tm+1,tr,a,t);
        t[v]=Merge(t[2*v],t[2*v+1]);
    }
}
Data get(int v,int tl,int tr,int l,int r,Data *t){
    if(l>r)return makeData(0);
    if(l==tl and r==tr){
        return t[v];
    }
    int tm=(tl+tr)/2;
    return Merge(get(2*v,tl,tm,l,min(r,tm),t),get(2*v+1,tm+1,tr,max(l,tm+1),r,t));
}
void update(int v,int tl,int tr,int pos,int val,Data *t) {
    if(tl==tr){
        t[v]=makeData(val);
    }
    else {
        int tm=(tl+tr)/2;
        if(pos<=tm){
            update(v*2,tl,tm,pos,val,t);
        }
        else {
            update(v*2+1,tm+1,tr,pos,val,t);
        }
        t[v]=Merge(t[v*2],t[v*2+1]);
    }
}

signed main()
{
    fast();

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n,q;
    cin>>n>>q;

    int a[n];
    for(auto& i:a){
        cin>>i;
    }
    Data *t=new Data[4*n+4];
    build(1,0,n-1,a,t);
    
    int i,v;
    cout<<get(1,0,n-1,0,n-1,t).ans<<endl;
    while(q--)
    {
        cin>>i>>v;
        update(1,0,n-1,i,v,t);
        cout<<get(1,0,n-1,0,n-1,t).ans<<endl;
    }
    return 0;
}