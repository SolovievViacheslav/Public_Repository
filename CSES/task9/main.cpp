#include <bits/stdc++.h>

#define ul unsigned long long
#define dist(i,i1) ( ( (i)>(i1) )?( (i)-(i1) ):((i1)-(i)) )

using namespace std;

int main()
{
    ul n,r,p,p10;
    cin>>n;
    p=pow(2,n);
    p10=pow(10,9);
    r=(p%p10);
    cout<<fixed<<dec<<r;
    cout.flush();
    return 0;
}
