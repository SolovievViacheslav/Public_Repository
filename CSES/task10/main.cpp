#include <iostream>
#include <bits/stdc++.h>

#define ull unsigned long long
#define ll  long long
using namespace std;

/*
 * 871
 * corr 215
 * 239
 * corr 57
 *
*/

int main()
{
    ull cntrs[3]={0,0,0};
    ull n=0;

    //cin>>n;
    n=25;
    for(ull i=n;i>0;i--)
    {
        if(!(i&1))cntrs[0]++;
        if((i%5)==0)cntrs[1]++;
        //if((i&5==1)||(i&5==5))cntrs[2]++;
    }

    if(cntrs[0]<cntrs[1])
        cout<<cntrs[0]<<"\n";
    else
        cout<<cntrs[1]<<"\n";

    cout.flush();
    return 0;
}
