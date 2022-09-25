#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int f(string columnTitle)
{
    #define ch2int(ch)({int i123=ch-'0'-16;i123;})
    #define int2ch(iii)({char ch=iii+'0'+16;ch;})

    int res=0;
    int len=columnTitle.length();
    int ovf_cntr=len-1;

    for(int i=0;i<len;i++)
    {
        char c=columnTitle[i];
        int t=ch2int(c);
        int pow_26=1;
        for(int j=0;j<(len-i-1);j++)
            pow_26*=26;
        res+=t*pow_26;
    }

    return res;
}

int main()
{
    string str="Z";
    int r=f(str);
    cout << "Hello World!" << endl;
    return 0;
}
