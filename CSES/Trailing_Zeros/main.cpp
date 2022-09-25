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
    //freopen("test_input.txt","r",stdin);
    ll a5=0;
    ll n;
    cin>>n;
    //n=374960399;//ok 93740092
    while(n>0)
    {
        n=n/5;
        a5+=n;
    }
    cout<<a5;
    cout.flush();
    return 0;
}
