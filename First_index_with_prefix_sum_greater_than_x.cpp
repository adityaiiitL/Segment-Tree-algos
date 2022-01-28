#include<bits/stdc++.h>
using namespace std;

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
int get(int v,int tl,int tr,int x,int *t){
    if(t[v]<x){
        return -1;
    }
    if(tl==tr){
        return tl;
    }
    int tm=(tl+tr)/2;
    if(t[2*v]>=x){
        return get(2*v,tl,tm,x,t);
    }
    else return get(2*v+1,tm+1,tr,x-t[2*v],t);
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

int main()
{
    
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
    int t[4*n+4];
    build(1,0,n-1,a,t);

    int c,x,i,v;
    while(q--)
    {
        cin>>c;
        if(c==1){
            cin>>x;
            cout<<get(1,0,n-1,x,t)+1<<endl;
        }
        else {
            cin>>i>>v;
            update(1,0,n-1,i,v,t);
        }
    }
    return 0;
}