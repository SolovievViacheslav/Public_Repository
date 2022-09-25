#include <iostream>
#include <bits/stdc++.h>
 
#define ul  unsigned long long
#define ll  long long
#define u64 uint64_t
#define i64 int64_t
 
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
 
#define dist(a,b) (max(a,b)-min(a,b))
 
using namespace std;
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> vp;
    vector<ll> vmp;
    vector<ll> vpex;
 
    vector<ll> vres;
 
    ll mp,p;
    ll t;
   // freopen("test_input.txt","r",stdin);
    cin>>p;
    cin>>mp;
    vres.resize(mp);
    for(ll i=0;i<p;i++)
    {
        cin>>t;
        vp.push_back(t);
        vpex.push_back(1);
 
    }
    for(ll i=0;i<mp;i++)
    {
        cin>>t;
        vmp.push_back(t);
 
    }
    sort(vp.begin(),vp.end());
 
    ll vpsz=vp.size();
    ll vmpsz=vmp.size();
    ll vmpi=0;
    ll parts=1000;
    if(parts>=vpsz)parts=1;
    ll partsz=vpsz/parts;
 
   ll price_start_indx=0;
   ll j=0;
   ll vpi=0;
 
    while(vmpsz)
    {
        vres[j]=-1;
        ll t=-1;
        if(vmp[vmpi]>=vp[vpi])
        {
            price_start_indx=vpsz-1;
            ll tmpindx=0;
            ll i;
            for(i=parts-1;i>-1;i--)
            {
                tmpindx=i*partsz+partsz-1;
                if((vmp[vmpi]>=vp[tmpindx])&&(tmpindx<=(vpsz-1)))
                {
                    break;
                }
            }
 
            if((i!=(parts-1)) && (i!=-1))
                price_start_indx=tmpindx+partsz-1;
            if(price_start_indx>vpsz-1)
               price_start_indx=vpsz-1;
            t=price_start_indx;
 
            ll f=1;
            ll k=0;
            while(f)
            {
                while(vmp[vmpi]<vp[t])
                {
                    if(t==0)break;
                    if((vp[t-1]-vmp[vmpi])>=((vp[t]-vmp[vmpi])))
                        break;
 
                    t--;
                }
 
                if(vpex[t])
                {
                    vres[j]=vp[t];
                    vpex[t]=0;
                    if(t==(vpsz-1))
                    {
                        if(vpsz)
                            vpsz--;
 
                    }
                    f=0;
                    //break;
                }
                else{if(t==0)break; t--;}
            }
 
        }//if(vmp[vmpi]>=vp[vpi])
        vmpi++;
        vmpsz--;
        j++;
 
    }
    for(ll i=0;i<vres.size();i++)
    {
        cout<<vres[i]<<"\n";
        if(vres[i]<0)
        {
            int t;
            t++;
        }
    }
    cout.flush();
    return 0;
}