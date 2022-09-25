#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int f(vector<vector<int>> v)
{
    int sum=0;
    sum=v[0][0];
    int indx=0;

    for(int i=1;i<v.size();i++)
    {
        int val=v[i][indx];
        int val2=v[i][indx+1];

        if(val<val2)
        {
            sum+=val;
        }
        else if(val2<val)
        {
            sum+=val2;
            indx=indx+1;
        }
        else if(val==val2)
        {
            sum+=val;

            if(i<v.size()-1)
            {
                int b1,b2,b3;
                b1=v[i+1][indx];
                b2=v[i+1][indx+1];
                b3=v[i+1][indx+2];

                if((b3<b1)&&(b3<b2))indx=indx+1;
            }
        }
    }

    return sum;

}
/*
int f_rec(vector<int> v)
{
    int s;
    for(int l=0;l<v.size()-1;l++)
        for(int i=0;i<v[i].size();i++)
        {
            f_rec(v[i]);
        }
    int s_tmp,s_tmp2;
    s_tmp=v[l][i]+v[l+1][i];
    s_tmp2=v[l][i]+v[l+1][i+1];
}*/
struct node2
{
    int val;
    struct node2* l;
    struct node2* r;
};

int f2(vector<vector<int>> v)
{
    int sum=v[0][0];
    vector<int> vlow;

    int l=0;
    int v_last_i=v.size()-1;
    int j=0;
    int n=v_last_i-1;

    vlow=v[v_last_i];
    int i1=0;

    vector <int> sums;
    vector <int> tmp_sums;
    int sz=vlow.size();
    int cnt=0;
    int sum2;

    while(n!=-1)
    {
        int sum1=0;
        for(int i=0;i<sz;i++)
        {
            if(i&1)
                sum1=(vlow[i]+v[n][j]);
            else
                sum2=(vlow[i]+v[n][j]);

            cnt++;

            if(cnt==2)
            {
                cnt=0;
                j++;
                if(j<v[n].size())
                    i--;

             tmp_sums.push_back(min(sum1,sum2));
            }

        }
        v[n]=tmp_sums;
        tmp_sums.clear();
        vlow=v[n];
        sz=vlow.size();
        n--;
        i1=0;
        j=0;
    }

    sum=v[0][0];
    return sum;
}

int main()
{
    int b=min(1,7);

    //vector<vector<int>> v={{2},{3,4},{6,5,7},{4,1,8,3}};
   // vector<vector<int>> v={{-10}};
    vector<vector<int>> v{{-1},{2,3},{1,-1,-3}};
    //vector<vector<int>> v{{-1},{2,3}};
    f2(v);
    cout << "Hello World!" << endl;
    return 0;
}
