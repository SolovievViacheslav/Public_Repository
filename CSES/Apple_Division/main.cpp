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
vector<int> f1()
{
    vector<int> r;
    r.resize(200);
    return r;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> v=f1();
    //freopen("test_input.txt","r",stdin);
    //cin>>n;
    ll sz=8;
    ll i=-1;
    i=20%7;
    for(int k=0;k<100;k++)
        i=(i+1)%(sz);

    int t=7/2;
//  cout<<a5;
    cout.flush();
    return 0;
}
