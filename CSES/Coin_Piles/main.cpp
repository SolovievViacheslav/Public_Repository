#include <iostream>
#include <bits/stdc++.h>

#include <tchar.h>
#include <mbstring.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>

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
    ll n;

   // freopen("test_input.txt","r",stdin);
    cin>>n;

    cout.flush();
    vector<bool>res;
    vector<ll>a;
    vector<ll>b;
    ll indx=0;
    while(indx<n)
    {
        ll t;
        ll a,b;
        cin>>t;
        a=t;
        cin>>t;
        b=t;
       // a=733431661;b=716735123;
        ll tmp;
        tmp=a*2;
        if((a==0)&&(b==0))
            res.push_back(true);
        else if((a==b)&&(a%3==0))
            res.push_back(true);
        else if((a+b)%3)
            res.push_back(false);
        else if(a&&b)
        {
            if((a==b)&&(a%3==0))res.push_back(true);
            else if(dist(a,b)%3==0)res.push_back(true);
            else if(((a+b)%6==0)&&(dist(a,b)&1)==0)res.push_back(true);
            else
               res.push_back(false);
            /*
            {
                ll a1=a,b1=b;
                ll
                /*
                while(a1)
                {
                    b1-=2;
                    a1--;
                }
                if(b1==0)
                    res.push_back(true);
                else
                    res.push_back(false);

            }*/
        }
        else res.push_back(false);
        //b.push_back(t);
        indx++;
    }

    for(ll i=0;i<n;i++)
    {
        if(res[i])
        {
            cout<<"YES"<<"\n";
        }
        else
            cout<<"NO"<<"\n";
    }

    cout.flush();
    return 0;
}
