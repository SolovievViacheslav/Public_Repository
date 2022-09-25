#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int f(vector<vector<int>> matrix,int target)
{

    uint64_t cntr=0;
    int64_t sum=0;
    map<int,int64_t> sc;
    map<int,int64_t> sr;
    int rc=0,cc=0;
    rc=matrix.size();
    cc=matrix[0].size();
    if(rc!=cc)return 0;

    for(int r=0;r<rc;r++)
    {
        for(int c=0;c<cc;c++)
        {
            if(matrix[r][c]==target)cntr++;
            sr[r]+=matrix[r][c];

        }
        sum+=sr[r];
    }

    if(sum==target)cntr++;

    for(int c=0;c<cc;c++)
    {
        for(int r=0;r<rc;r++)
        {
            sc[c]+=matrix[r][c];
        }
    }

    //------del row-----------------
    for(int i=0;i<rc;i++)
    {
        if((sum-sr[i])==target)cntr++;
    }

    //------del clmn-----------------
    for(int i=0;i<cc;i++)
    {
        if((sum-sc[i])==target)cntr++;
    }

    //------del row and clmn-----------------
    for(int r=0;r<rc;r++)
    {
        for(int c=0;c<cc;c++)
        {
            int mrc=matrix[r][c];
            int res=sum-sr[r]-sc[c]+mrc;
            if(res==target)
            {
                cntr++;
                for(int r1=0;r1<rc;r1++)
                    for(int c1=0;c1<cc;c1++)
                    if(res==matrix[r1][c1])
                    {
                        cntr--;r1=rc;break;
                    }
            }
        }
    }
    if(rc==cc)
        if(rc==1)cntr-=3;
    return cntr;

}

int main()
{
    f({{0,1,0},{1,1,1},{0,1,0}},0);
    //f({{1,-1},{-1,1}},0);
    //f({{1,-1}},0);
    f({{904}},0);
    cout << "Hello World!" << endl;
    return 0;
}
