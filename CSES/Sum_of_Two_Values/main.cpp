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
// time -07 -10 -11
int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,n1;
    ll sum;
    ll f=0;
    ll a,b,ia,ib;

    //freopen("test_input.txt","r",stdin);
    cin>>n;
    cin>>sum;
    vector<ll>nums;
    map<ll,ll> nums2;
    ll indx=0;
    while(indx<n)
    {
        ll t;
        cin>>t;
        nums.push_back(t);
        nums2[t]=indx;
        indx++;
    }
    for(ll i=0;i<n-1;i++)
    {
        a=nums[i];
        b=sum-a;
        if(nums2.find(b)!=nums2.end())
        {
            if(nums2[b]!=i)
            {
                ia=i+1;
                ib=nums2[b]+1;
                f=1;
                break;
            }
        }
    }

    if(f)
    {
        cout<<ia<<" "<<ib<<"\r";
    }
    else
        cout<<"IMPOSSIBLE"<<"\r";

    cout.flush();
    return 0;
}
