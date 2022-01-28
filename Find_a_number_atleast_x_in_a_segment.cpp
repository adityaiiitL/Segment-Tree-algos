#include<bits/stdc++.h>
using namespace std;

vector<int> Merge(vector<int> &a,vector<int> &b)
{
    vector<int> res;

    int i=0,j=0;
    int n=a.size(),m=b.size();
    while(i<n and j<m){
        if(a[i]<b[j]){
            res.push_back(a[i++]);
        }
        else {
            res.push_back(b[j++]);
        }
    }
    while(i<n)res.push_back(a[i++]);
    while(j<m)res.push_back(b[j++]);
    
    return res;
}
void build(int v,int tl,int tr,int *a,vector<int> *t)
{
    if(tl==tr){
        t[v]={a[tl]};
    }
    else {
        int tm=(tl+tr)/2;

        build(2*v,tl,tm,a,t);
        build(2*v+1,tm+1,tr,a,t);

        t[v]=Merge(t[2*v],t[2*v+1]);
    }
}
int get(int v,int tl,int tr,int l,int r,int x,vector<int> *t)
{
    if(l>r){
        return INT_MAX;
    }
    if(tl==l and tr==r){
        vector<int>::iterator j=lower_bound(t[v].begin(),t[v].end(),x);
        if(j!=t[v].end()){
            return *j;
        }
        return INT_MAX;
    }
    int tm=(tl+tr)/2;
    
    int L=get(2*v,tl,tm,l,min(r,tm),x,t);
    int R=get(2*v+1,tm+1,tr,max(l,tm+1),r,x,t);

    return min(L,R);
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin>>n;
    int a[n];
    for(auto& i:a){
        cin>>i;
    }
    vector<int> t[4*n+4];
    build(1,0,n-1,a,t);

    int q;
    cin>>q;
    while(q--)
    {
        int l,r,x;
        cin>>l>>r>>x;
        cout<<get(1,0,n-1,l-1,r-1,x,t)<<endl;
    }

    return 0;
}